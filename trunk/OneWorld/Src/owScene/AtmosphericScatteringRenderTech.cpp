#include <owScene/atmosphericscatteringRenderTech.h>
#include <osg/Geometry>
#include <osg/FrontFace>

#include <osgDB/FileUtils>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <owScene/TerrainTile.h>



namespace owScene
{
	////look at µÄ·´¾ØÕó
	class ViewMatrixInvCallBack: public osg::Uniform::Callback
	{
	public:
		ViewMatrixInvCallBack(osgViewer::Viewer *viewer) : _viewer(viewer){}

		virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
		{
			if (!_viewer->getCameraManipulator())
				return;
			osg::Matrixf m = _viewer->getCameraManipulator()->getMatrix();
			uniform->set(m);
		}

	private:
		osgViewer::Viewer* _viewer;
	};

	char innerVertexShaderSource[] = 
		"//uniform vec3 v3LightPos;  \n"
		"uniform vec3 v3InvWavelength;  \n"
		"uniform float fKrESun;  \n"
		"uniform float fKmESun;  \n"
		"uniform float fKr4PI;  \n"
		"uniform float fKm4PI;  \n"
		"uniform float fScaleDepth;  \n"
		"varying vec2 baseTexCoord;  \n"
		"uniform mat4 viewMatrixInvert;  \n"

		"const int nSamples = 2;  \n"
		"const float fSamples = 2.0;  \n"

		"float scale(float fCos)  \n"
		"{  \n"
		"	float x = 1.0 - fCos;  \n"
		"	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));  \n"
		"}  \n"

		"void main(void)  \n"
		"{  \n"

		"mat4 ModelViewMatrixInverse = viewMatrixInvert;  \n"
		"vec3 v3CameraPos =  vec3(ModelViewMatrixInverse[3][0], ModelViewMatrixInverse[3][1],ModelViewMatrixInverse[3][2]);  \n"

		"vec4 originPosV4 = viewMatrixInvert*gl_ModelViewMatrix*gl_Vertex;  \n"
		"vec3 v3Pos = vec3(originPosV4.x,originPosV4.y,originPosV4.z);  \n"

		"float fInnerRadius = length(v3Pos);  \n"
		"float fInnerRadius2 = fInnerRadius*fInnerRadius;  \n"
		"float fOuterRadius = fInnerRadius*1.015;  \n"

		"float fOuterRadius2 = fOuterRadius*fOuterRadius;  \n"

		"float fScale = 1.0f / (fOuterRadius - fInnerRadius);  \n"
		"float fScaleOverScaleDepth = fScale/fScaleDepth;  \n"

		"baseTexCoord = gl_MultiTexCoord0.xy;  \n"
		"vec3 v3Ray = v3Pos - v3CameraPos;  \n"
		"float fFar = length(v3Ray);  \n"
		"v3Ray /= fFar;  \n"
		"float fCameraHeight = length(v3CameraPos);  \n"
		"float fCameraHeight2 = fCameraHeight*fCameraHeight;  \n"

		"originPosV4 = viewMatrixInvert*vec4(0.0,0.0,1.0,1.0);  \n"
		"vec3 v3LightPos = vec3(originPosV4.x,originPosV4.y,originPosV4.z);  \n"
		"v3LightPos = normalize(v3LightPos);  \n"

		"vec3 v3Start;  \n"
		"if(fCameraHeight >= fOuterRadius)  \n"
		"{  \n"
		"float B = 2.0 * dot(v3CameraPos, v3Ray);  \n"
		"float C = fCameraHeight2 - fOuterRadius2;  \n"
		"float fDet = max(0.0, B*B - 4.0 * C);  \n"
		"float fNear = 0.5 * (-B - sqrt(fDet));  \n"
		"v3Start = v3CameraPos + v3Ray * fNear;  \n"
		"fFar -= fNear;  \n"
		"}else  \n"
		"{  \n"
		"v3Start = v3CameraPos;  \n"
		"}  \n"
		"float fDepth = exp((fInnerRadius - fOuterRadius) / fScaleDepth);  \n"
		"float fCameraAngle = dot(-v3Ray, (v3Pos/ length(v3Pos)));  \n"
		"float fLightAngle = dot(v3LightPos, (v3Pos/ length(v3Pos)));  \n"
		"float fCameraScale = scale(fCameraAngle);  \n"
		"float fLightScale = scale(fLightAngle);  \n"
		"float fCameraOffset = fDepth*fCameraScale; \n"
		"float fTemp = (fLightScale + fCameraScale); \n"

		"float fSampleLength = fFar / fSamples; \n"
		"float fScaledLength = fSampleLength * fScale; \n"
		"vec3 v3SampleRay = v3Ray * fSampleLength; \n"
		"vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5; \n"

		"vec3 v3FrontColor = vec3(0.0, 0.0, 0.0); \n"
		"vec3 v3Attenuate; \n"
		"for(int i=0; i<nSamples; i++) \n"
		"{ \n"
		"float fHeight = length(v3SamplePoint); \n"
		"float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight)); \n"
		"float fScatter = fDepth*fTemp - fCameraOffset; \n"
		"v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI)); \n"
		"v3FrontColor += v3Attenuate * (fDepth * fScaledLength); \n"
		"v3SamplePoint += v3SampleRay; \n"
		"} \n"

		"gl_FrontColor.rgb = v3FrontColor * (v3InvWavelength * fKrESun + fKmESun); \n"
		"gl_FrontSecondaryColor.rgb = v3Attenuate; \n"
		"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; \n"

		"} \n";

	char innerFragmentShaderSource[] =
		"uniform sampler2D baseTex;  \n"
		"varying vec2 baseTexCoord;  \n"

		"void main (void)  \n"
		"{  \n"
		"vec4 baseTexColor = texture2D(baseTex, baseTexCoord.st);  \n"
		"gl_FragColor = gl_Color + baseTexColor * gl_SecondaryColor;  \n"
		"} \n";

	char outterVertexShaderSource[] =
		"//uniform vec3 v3LightPos;  \n"
		"uniform vec3 v3InvWavelength;  \n"
		"uniform float fCameraHeight;  \n"
		"uniform float fCameraHeight2;  \n"
		"uniform float fOuterRadius;  \n"
		"uniform float fOuterRadius2;  \n"
		"uniform float fInnerRadius;  \n"
		"uniform float fInnerRadius2;  \n"
		"uniform float fKrESun;  \n"
		"uniform float fKmESun;  \n"
		"uniform float fKr4PI;  \n"		
		"uniform float fKm4PI;  \n"		
		"uniform float fScale;  \n"			
		"uniform float fScaleDepth;  \n"
		"uniform float fScaleOverScaleDepth;  \n"
		"uniform mat4 viewMatrixInvert;  \n"

		"const int nSamples = 2;  \n"
		"const float fSamples = 2.0;  \n"

		"varying vec3 v3Direction;  \n"

		"float scale(float fCos)  \n"
		"{  \n"
		"float x = 1.0 - fCos;  \n"
		"return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));  \n"
		"}  \n"

		"void main(void)  \n"
		"{  \n"
		"mat4 ModelViewMatrixInverse = viewMatrixInvert;  \n"
		"vec3 v3CameraPos =  vec3(ModelViewMatrixInverse[3][0], ModelViewMatrixInverse[3][1],ModelViewMatrixInverse[3][2]);  \n"

		"vec4 originPosV4 = viewMatrixInvert*gl_ModelViewMatrix*gl_Vertex;  \n"
		"vec3 v3Pos = vec3(originPosV4.x,originPosV4.y,originPosV4.z);  \n"

		"originPosV4 = viewMatrixInvert*vec4(0.0,0.0,1.0,1.0);  \n"
		"vec3 v3LightPos = vec3(originPosV4.x,originPosV4.y,originPosV4.z);  \n"
		"v3LightPos = normalize(v3LightPos);  \n"

		"vec3 v3Ray = v3Pos - v3CameraPos;  \n"
		"float fFar = length(v3Ray);  \n"
		"v3Ray /= fFar;  \n"

		"float fCameraHeight = length(v3CameraPos);  \n"
		"float fCameraHeight2 = fCameraHeight * fCameraHeight;  \n"

		"vec3 v3Start;  \n"
		"float fStartOffset;  \n"

		"if(fCameraHeight >= fOuterRadius)  \n"
		"{  \n"
		"float B = 2.0 * dot(v3CameraPos, v3Ray);  \n"
		"float C = fCameraHeight2 - fOuterRadius2;  \n"
		"float fDet = max(0.0, B*B - 4.0 * C);  \n"
		"float fNear = 0.5 * (-B - sqrt(fDet));  \n"
		"v3Start = v3CameraPos + v3Ray * fNear;  \n"
		"fFar -= fNear;  \n"
		"float fStartAngle = dot(v3Ray, (v3Start/length(v3Start)));  \n"
		"float fStartDepth = exp(-1.0 / fScaleDepth);  \n"
		"fStartOffset = fStartDepth*scale(fStartAngle);  \n"
		"}  \n"
		"else  \n"
		"{  \n"
		"v3Start = v3CameraPos;  \n"
		"float fHeight = length(v3Start);  \n"
		"float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));  \n"
		"float fStartAngle = dot(v3Ray, (v3Start/length(v3Start)));  \n"
		"fStartOffset = fDepth*scale(fStartAngle);  \n"
		"}  \n"

		"float fSampleLength = fFar / fSamples;  \n"
		"float fScaledLength = fSampleLength * fScale;  \n"
		"vec3 v3SampleRay = v3Ray * fSampleLength;  \n"
		"vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;  \n"

		"vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);  \n"
		"for(int i=0; i<nSamples;  i++)  \n"
		"{  \n"
		"float fHeight = length(v3SamplePoint);  \n"
		"float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));  \n"
		"float fLightAngle = dot(v3LightPos, (v3SamplePoint/length(v3SamplePoint)));  \n"
		"float fCameraAngle = dot(v3Ray,  (v3SamplePoint/length(v3SamplePoint)));  \n"
		"float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));  \n"
		"vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));  \n"
		"v3FrontColor += v3Attenuate * (fDepth * fScaledLength);  \n"
		"v3SamplePoint += v3SampleRay;  \n"
		"}  \n"

		"gl_FrontSecondaryColor.rgb = v3FrontColor * fKmESun;  \n"
		"gl_FrontColor.rgb = v3FrontColor * (v3InvWavelength * fKrESun);  \n"
		"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  \n"
		"v3Direction = v3CameraPos - v3Pos;  \n"
		"}  \n";
	char outterFragmentShaderSource[] =
		"uniform vec3 v3LightPos;  \n"
		"uniform float g;  \n"
		"uniform float g2;  \n"

		"varying vec3 v3Direction;  \n"

		"void main (void)  \n"
		"{  \n"
		"float fCos = dot(v3LightPos, v3Direction) / length(v3Direction);  \n"
		"float fMiePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos*fCos) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);  \n"
		"float fRayleighPhase = 0.75 + 0.75*fCos*fCos;  \n"
		"gl_FragColor = fRayleighPhase*gl_Color + fMiePhase * gl_SecondaryColor;  \n"
		"gl_FragColor.a = gl_FragColor.b;  \n"
		"}  \n";

	AtmosphericScatteringRenderTech::AtmosphericScatteringRenderTech(osgViewer::Viewer* viewer)
		: TerrainRenderTech()
	{
		_viewer = viewer;
		//osg::Program *program=new osg::Program;

		//_program->addShader(new osg::Shader(osg::Shader::VERTEX, innerVertexShaderSource));
		//_program->addShader(new osg::Shader(osg::Shader::FRAGMENT, innerFragmentShaderSource));

		initScattieringParameter();
		//addInnerShader();
		//SetRenderPrograme(program);

		createOutterAtmosphere();
	}

	AtmosphericScatteringRenderTech::AtmosphericScatteringRenderTech(const AtmosphericScatteringRenderTech& tech, const osg::CopyOp& copyop)
	{
		LOG_ERROR("The Copy Constructor Of AtmosphericScatteringRenderTech Have not Implement");
	}

	void AtmosphericScatteringRenderTech::apply(TerrainTile* tile)
	{
		//if (!mParentTerrain->IsConvertToGeoCenteric()) return;

		TerrainRenderTech::apply(tile);
	}

	void AtmosphericScatteringRenderTech::unapply(TerrainTile* tile)
	{
		//if (!mParentTerrain->IsConvertToGeoCenteric()) return;

		TerrainRenderTech::unapply(tile);
	}

	void AtmosphericScatteringRenderTech::createOutterAtmosphere()
	{
		std::string planetName = "atmosphere";
		std::string texPathName = "";
		osg::Vec4 color = osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f);

		_atmosphereNode = createRealPlanet(_fOuterRadius,planetName,color,texPathName,true);
		if (_atmosphereNode.get())
		{
			addOutterShader();
		}
	}

	void AtmosphericScatteringRenderTech::initScattieringParameter()
	{
		_nSamples = 3;		// Number of sample rays to use in integral equation
		_Kr = 0.0025f;		// Rayleigh scattering constant
		_Kr4PI = _Kr*4.0f*osg::PI;
		_Km = 0.0010f;		// Mie scattering constant
		_Km4PI = _Km*4.0f*osg::PI;
		_ESun = 20.0f;		// Sun brightness constant
		_g = -0.990f;		// The Mie phase asymmetry factor
		_fExposure = 2.0f;

		//_fInnerRadius = 10.0f;
		//_fOuterRadius = _fInnerRadius*1.025;
		//_fOuterRadius = 10.05f;

		float radiusScale = 0.015;
		_fInnerRadius = 6378137.0;//µØÇò°ë¾¶
		//_fInnerRadius = gvUtil::GetGlobalEllipsoidModel().getRadiusEquator();
		_fOuterRadius = _fInnerRadius*(1.0 + radiusScale);

		_fScale = 1 / (_fOuterRadius - _fInnerRadius);

		_fWavelength[0] = 0.650f;		// 650 nm for red
		_fWavelength[1] = 0.570f;		// 570 nm for green
		_fWavelength[2] = 0.475f;		// 475 nm for blue
		_fWavelength4[0] = powf(_fWavelength[0], 4.0f);
		_fWavelength4[1] = powf(_fWavelength[1], 4.0f);
		_fWavelength4[2] = powf(_fWavelength[2], 4.0f);

		_fRayleighScaleDepth = 0.25f;
		_fMieScaleDepth = 0.1f;

		_lightPos = osg::Vec3(0.0,0.0,1000.0);
		_vLightDirection = _lightPos;
		_vLightDirection.normalize();
	}

	osg::Geode* AtmosphericScatteringRenderTech::createRealPlanet( float radius, const std::string& name, const osg::Vec4& color , const std::string& textureName,bool isClockWise)
	{
		// create a container that makes the sphere drawable
		osg::ref_ptr<osg::Geometry> sPlanetSphere = new osg::Geometry();
		osg::ref_ptr<osg::StateSet> ss = sPlanetSphere->getOrCreateStateSet();
		osg::FrontFace::Mode drawMode;
		if (isClockWise)
		{
			drawMode = osg::FrontFace::CLOCKWISE;

		}else drawMode = osg::FrontFace::COUNTER_CLOCKWISE;

		osg::ref_ptr<osg::FrontFace> drawFrontFace = new osg::FrontFace(drawMode);
		ss->setAttributeAndModes(drawFrontFace.get(), osg::StateAttribute::ON);
		//ss->setRenderBinDetails(binNum,"RenderBin");
		ss->setMode(GL_CULL_FACE,osg::StateAttribute::ON);

		// set the single colour so bind overall
		osg::Vec4Array* colours = new osg::Vec4Array(1);
		(*colours)[0] = color;
		sPlanetSphere->setColorArray(colours);
		sPlanetSphere->setColorBinding(osg::Geometry::BIND_OVERALL);

		// now set up the coords, normals and texcoords for geometry 
		unsigned int numX = 100;
		unsigned int numY = 50;
		unsigned int numVertices = numX*numY;

		osg::Vec3Array* coords = new osg::Vec3Array(numVertices);
		osg::Vec3Array* normals = new osg::Vec3Array(numVertices);
		osg::Vec2Array* texcoords = new osg::Vec2Array(numVertices);

		double delta_elevation = osg::PI / (double)(numY-1);
		double delta_azim = 2.0*osg::PI / (double)(numX-1);
		float delta_tx = 1.0 / (float)(numX-1);
		float delta_ty = 1.0 / (float)(numY-1);

		double elevation = -osg::PI*0.5;
		float ty = 0.0;
		unsigned int vert = 0;
		unsigned j;
		for(j=0;j<numY;++j, elevation+=delta_elevation, ty+=delta_ty )
		{
			double azim = 0.0;
			float tx = 0.0;
			for(unsigned int i=0;
				i<numX;
				++i, ++vert, azim+=delta_azim, tx+=delta_tx)
			{
				osg::Vec3 direction(cos(azim)*cos(elevation), sin(azim)*cos(elevation), sin(elevation));
				(*coords)[vert].set(direction*radius);
				(*normals)[vert].set(direction);
				(*texcoords)[vert].set(tx,ty);
			}
		}

		unsigned int numQuats = (numX-1)*(numY-1);
		unsigned int numTrianglesVerts = numQuats*2;
		osg::Vec3Array* trianglesCoords = new osg::Vec3Array(numTrianglesVerts);
		osg::Vec3Array* trianglesNormals = new osg::Vec3Array(numTrianglesVerts);
		osg::Vec2Array* trianglesTexcoords = new osg::Vec2Array(numTrianglesVerts);


		for(j=0;j<numY-1;j++)
		{
			unsigned int curr_row = j*numX;
			unsigned int next_row = curr_row+numX;

			for(unsigned int i=0;i<numX-1;i++)
			{
				//////////////////////////////////////////////////////////////////////////
				trianglesCoords->push_back((*coords)[curr_row + i]);
				trianglesCoords->push_back((*coords)[curr_row + i +1]);
				trianglesCoords->push_back((*coords)[next_row + i]);

				trianglesCoords->push_back((*coords)[next_row + i]);
				trianglesCoords->push_back((*coords)[curr_row + i +1]);
				trianglesCoords->push_back((*coords)[next_row + i +1]);


				//////////////////////////////////////////////////////////////////////////
				trianglesNormals->push_back((*normals)[curr_row + i]);
				trianglesNormals->push_back((*normals)[curr_row + i +1]);
				trianglesNormals->push_back((*normals)[next_row + i]);

				trianglesNormals->push_back((*normals)[next_row + i]);
				trianglesNormals->push_back((*normals)[curr_row + i +1]);
				trianglesNormals->push_back((*normals)[next_row + i +1]);

				//////////////////////////////////////////////////////////////////////////
				trianglesTexcoords->push_back((*texcoords)[curr_row + i]);
				trianglesTexcoords->push_back((*texcoords)[curr_row + i +1]);
				trianglesTexcoords->push_back((*texcoords)[next_row + i]);

				trianglesTexcoords->push_back((*texcoords)[next_row + i]);
				trianglesTexcoords->push_back((*texcoords)[curr_row + i +1]);
				trianglesTexcoords->push_back((*texcoords)[next_row + i +1]);
			}
		}

		sPlanetSphere->setVertexArray(trianglesCoords);
		sPlanetSphere->setNormalArray(trianglesNormals);
		sPlanetSphere->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
		sPlanetSphere->setTexCoordArray(0,trianglesTexcoords);
		sPlanetSphere->setTexCoordArray(1,trianglesTexcoords);

		sPlanetSphere->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,trianglesCoords->size()));

		osg::Geode *geodePlanet = new osg::Geode();
		geodePlanet->setName( name );

		// add our drawable sphere to the geode container
		geodePlanet->addDrawable( sPlanetSphere.get() );

		return( geodePlanet);
	}

	void AtmosphericScatteringRenderTech::addOutterShader()
	{

		osg::StateSet* ss = _atmosphereNode->getOrCreateStateSet();
		osg::Program* SkyShaderProg = new osg::Program;
		ss->setAttributeAndModes(SkyShaderProg, osg::StateAttribute::ON);

		SkyShaderProg->addShader(new osg::Shader(osg::Shader::VERTEX, outterVertexShaderSource));
		SkyShaderProg->addShader(new osg::Shader(osg::Shader::FRAGMENT, outterFragmentShaderSource));

		osg::Uniform* viewMatrixInvertUniform = new osg::Uniform("viewMatrixInvert", osg::Matrixf::identity());
		viewMatrixInvertUniform->setUpdateCallback(new ViewMatrixInvCallBack(_viewer));
		ss->addUniform(viewMatrixInvertUniform);

		ss->addUniform( new osg::Uniform("v3InvWavelength",osg::Vec3(1/_fWavelength4[0],1/_fWavelength4[1],1/_fWavelength4[2])));
		ss->addUniform( new osg::Uniform("fInnerRadius", _fInnerRadius));
		ss->addUniform( new osg::Uniform("fInnerRadius2", _fInnerRadius*_fInnerRadius));
		ss->addUniform( new osg::Uniform("fOuterRadius", _fOuterRadius));
		ss->addUniform( new osg::Uniform("fOuterRadius2", _fOuterRadius*_fOuterRadius));
		ss->addUniform( new osg::Uniform("fKrESun", _Kr*_ESun));
		ss->addUniform( new osg::Uniform("fKmESun", _Km*_ESun));
		ss->addUniform( new osg::Uniform("fKr4PI", _Kr4PI));
		ss->addUniform( new osg::Uniform("fKm4PI", _Km4PI));
		ss->addUniform( new osg::Uniform("fScale", 1.0f / (_fOuterRadius - _fInnerRadius)));
		ss->addUniform( new osg::Uniform("fScaleDepth", _fRayleighScaleDepth));
		ss->addUniform( new osg::Uniform("fScaleOverScaleDepth", (1.0f / (_fOuterRadius - _fInnerRadius)) / _fRayleighScaleDepth));
		ss->addUniform( new osg::Uniform("g", _g));
		ss->addUniform( new osg::Uniform("g2", _g*_g));
	}

	void AtmosphericScatteringRenderTech::addInnerShader()
	{
		osg::Uniform* viewMatrixInvertUniform = new osg::Uniform("viewMatrixInvert", osg::Matrixf::identity());
		viewMatrixInvertUniform->setUpdateCallback(new ViewMatrixInvCallBack(_viewer));
		_uniforms.push_back(viewMatrixInvertUniform);

		_uniforms.push_back( new osg::Uniform("v3InvWavelength",osg::Vec3(1/_fWavelength4[0],1/_fWavelength4[1],1/_fWavelength4[2])));

		_uniforms.push_back( new osg::Uniform("fKrESun", _Kr*_ESun));
		_uniforms.push_back( new osg::Uniform("fKmESun", _Km*_ESun));
		_uniforms.push_back( new osg::Uniform("fKr4PI", _Kr4PI));
		_uniforms.push_back( new osg::Uniform("fKm4PI", _Km4PI));
		_uniforms.push_back( new osg::Uniform("fScaleDepth", _fRayleighScaleDepth));
		_uniforms.push_back( new osg::Uniform("g", _g));
		_uniforms.push_back( new osg::Uniform("g2", _g*_g));
		_uniforms.push_back( new osg::Uniform("baseTex", 0));
	}

	bool AtmosphericScatteringRenderTech::loadShaderSource( osg::Shader* shader, const std::string& fileName )
	{
		std::string fqFileName = osgDB::findDataFile(fileName);
		if( fqFileName.length() != 0 )
		{
			shader->loadShaderSourceFromFile( fqFileName.c_str() );
			return true;		
		}
		return false;
	}
}