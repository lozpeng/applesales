#include <owScene/ImageLayersRenderTech.h>
#include <owUtil/Capabilities.h>

using namespace owScene;

ImageLayersRenderTech::ImageLayersRenderTech(const ImageLayersRenderTech::Type type):_type(type)
{
	if (_type == ImageLayersRenderTech::TEXTURE2DARRAY)
	{
		init();
	}
	else if(_type == ImageLayersRenderTech::TEXTURE2D)
	{
		init2D();
	}
	else
	{
		if (owUtil::Capabilities::Instance().supportsTextureArrays())//判断opengl是否支持texture2DArray
		{
			init();
		}
		else
		{
			init2D();
		}
	}
}

ImageLayersRenderTech::ImageLayersRenderTech(const ImageLayersRenderTech& tech,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
:TerrainRenderTech(tech,copyop)
{

}

osg::Texture2D* ImageLayersRenderTech::createTexture2D(osg::ref_ptr<osg::Image>& img)
{
	osg::Texture2D* txt = new osg::Texture2D;
	txt->setDataVariance(osg::Object::DYNAMIC);

	osg::Image* image = img;
	image->setInternalTextureFormat(GL_RGBA);
	txt->setImage(image);
	txt->setName(image->getName());

	txt->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	txt->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	txt->setWrap( osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_EDGE );
	txt->setWrap( osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_EDGE );
	txt->setWrap( osg::Texture2D::WRAP_R, osg::Texture2D::CLAMP_TO_EDGE );

	return txt;
}
osg::Texture2DArray* ImageLayersRenderTech::createTexture2DArray(std::vector<osg::ref_ptr<osg::Image>>& imglist)
{
	osg::Texture2DArray* t2d = new osg::Texture2DArray ;
	t2d->setDataVariance(osg::Object::DYNAMIC);

	t2d->setTextureDepth(imglist.size());

	for (unsigned int i=0;i<imglist.size();i++)
	{
		osg::Image* image = imglist[i];
		image->setInternalTextureFormat(GL_RGBA);
		t2d->setImage(i, imglist[i].get());
	}

	t2d->setFilter(osg::Texture2DArray::MIN_FILTER, osg::Texture2DArray::LINEAR);
	t2d->setFilter(osg::Texture2DArray::MAG_FILTER, osg::Texture2DArray::LINEAR);
	t2d->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	t2d->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
	t2d->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

	return t2d;
}

void ImageLayersRenderTech::applyTexture(osg::Geometry* geometry, 
										 std::vector<osg::ref_ptr<osg::Image>>& imglist)
{
	if (_type == ImageLayersRenderTech::TEXTURE2DARRAY)
	{
		geometry->getOrCreateStateSet()->setTextureAttribute(0, 
			createTexture2DArray(imglist), osg::StateAttribute::ON);
	}
	else if (_type == ImageLayersRenderTech::TEXTURE2D)
	{
		for (unsigned int i=0;i<imglist.size();i++)
		{
			geometry->getOrCreateStateSet()->setTextureAttributeAndModes(i,
				createTexture2D(imglist[i]),osg::StateAttribute::ON);
		}
	}
	else
	{
		if (owUtil::Capabilities::Instance().supportsTextureArrays())//判断opengl是否支持texture2DArray
		{
			geometry->getOrCreateStateSet()->setTextureAttribute(0, 
				createTexture2DArray(imglist), osg::StateAttribute::ON);
		}
		else
		{
			for (unsigned int i=0;i<imglist.size();i++)
			{
				geometry->getOrCreateStateSet()->setTextureAttributeAndModes(i,
					createTexture2D(imglist[i]),osg::StateAttribute::ON);
			}
		}
	}
}

void ImageLayersRenderTech::init()
{
	//osg::Shader* fShader = new osg::Shader(osg::Shader::FRAGMENT);

	//std::stringstream buf;
	//buf<<"#extension GL_EXT_gpu_shader4 : enable"<<std::endl;

	//buf<<"uniform sampler2DArray tex;"<<std::endl;

	//buf<<"void main()"<<std::endl;
	//buf<<"{"<<std::endl;
	//buf<<"		vec4 texCoord = (vec4(gl_TexCoord[0].st, floor(gl_TexCoord[0].r), gl_TexCoord[0].q));"<<std::endl;
	//buf<<"		vec4 mixcolor = gl_Color;"<<std::endl;

	//buf<<"		vec4 color7 = texture2DArray(tex, vec3(texCoord.st, 7));"<<std::endl;
	//buf<<"		vec3 tcolor3_7 = mix(mixcolor.rgb,color7.rgb,color7.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_7,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color6 = texture2DArray(tex, vec3(texCoord.st, 6));"<<std::endl;
	//buf<<"		vec3 tcolor3_6 = mix(mixcolor.rgb,color6.rgb,color6.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_6,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color5 = texture2DArray(tex, vec3(texCoord.st, 5));"<<std::endl;
	//buf<<"		vec3 tcolor3_5 = mix(mixcolor.rgb,color5.rgb,color5.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_5,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color4 = texture2DArray(tex, vec3(texCoord.st, 4));"<<std::endl;
	//buf<<"		vec3 tcolor3_4 = mix(mixcolor.rgb,color4.rgb,color4.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_4,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color3 = texture2DArray(tex, vec3(texCoord.st, 3));"<<std::endl;
	//buf<<"		vec3 tcolor3_3 = mix(mixcolor.rgb,color3.rgb,color3.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_3,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color2 = texture2DArray(tex, vec3(texCoord.st, 2));"<<std::endl;
	//buf<<"		vec3 tcolor3_2 = mix(mixcolor.rgb,color2.rgb,color2.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_2,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color1 = texture2DArray(tex, vec3(texCoord.st, 1));"<<std::endl;
	//buf<<"		vec3 tcolor3_1 = mix(mixcolor.rgb,color1.rgb,color1.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_1,mixcolor.a);"<<std::endl;

	//buf<<"		vec4 color0 = texture2DArray(tex, vec3(texCoord.st, 0));"<<std::endl;
	//buf<<"		vec3 tcolor3_0 = mix(mixcolor.rgb,color0.rgb,color0.a);"<<std::endl;
	//buf<<"		mixcolor = vec4(tcolor3_0,mixcolor.a);"<<std::endl;

	//buf<<"		gl_FragColor=mixcolor;"<<std::endl;
	//buf<<"	}"<<std::endl;

	//std::string source = buf.str();

	//fShader->setShaderSource(source);

	//_program->addShader(fShader);

	//osg::Uniform* u = new osg::Uniform(osg::Uniform::SAMPLER_2D_ARRAY, "tex");

	//_uniforms.push_back(u);

	osg::Shader* fShader = new osg::Shader(osg::Shader::FRAGMENT);
	osg::Shader* vShader = new osg::Shader(osg::Shader::VERTEX);

	std::stringstream buf;
	std::stringstream v_buf;

	buf<<"#extension GL_EXT_gpu_shader4 : enable"<<std::endl;
	buf<<"uniform sampler2DArray tex;"<<std::endl;
	buf<<"varying float LightIntensity;"<<std::endl;

	buf<<"void main()"<<std::endl;
	buf<<"{"<<std::endl;
	buf<<"		vec4 texCoord = (vec4(gl_TexCoord[0].st, floor(gl_TexCoord[0].r), gl_TexCoord[0].q));"<<std::endl;
	buf<<"		vec4 mixcolor = gl_Color;"<<std::endl;

	buf<<"		vec4 color7 = texture2DArray(tex, vec3(texCoord.st, 7));"<<std::endl;
	buf<<"		vec3 tcolor3_7 = mix(mixcolor.rgb,color7.rgb*LightIntensity,color7.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_7,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color6 = texture2DArray(tex, vec3(texCoord.st, 6));"<<std::endl;
	buf<<"		vec3 tcolor3_6 = mix(mixcolor.rgb,color6.rgb*LightIntensity,color6.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_6,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color5 = texture2DArray(tex, vec3(texCoord.st, 5));"<<std::endl;
	buf<<"		vec3 tcolor3_5 = mix(mixcolor.rgb,color5.rgb*LightIntensity,color5.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_5,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color4 = texture2DArray(tex, vec3(texCoord.st, 4));"<<std::endl;
	buf<<"		vec3 tcolor3_4 = mix(mixcolor.rgb,color4.rgb*LightIntensity,color4.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_4,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color3 = texture2DArray(tex, vec3(texCoord.st, 3));"<<std::endl;
	buf<<"		vec3 tcolor3_3 = mix(mixcolor.rgb,color3.rgb*LightIntensity,color3.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_3,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color2 = texture2DArray(tex, vec3(texCoord.st, 2));"<<std::endl;
	buf<<"		vec3 tcolor3_2 = mix(mixcolor.rgb,color2.rgb*LightIntensity,color2.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_2,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color1 = texture2DArray(tex, vec3(texCoord.st, 1));"<<std::endl;
	buf<<"		vec3 tcolor3_1 = mix(mixcolor.rgb,color1.rgb*LightIntensity,color1.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_1,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color0 = texture2DArray(tex, vec3(texCoord.st, 0));"<<std::endl;
	buf<<"		vec3 tcolor3_0 = mix(mixcolor.rgb,color0.rgb*LightIntensity,color0.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_0,mixcolor.a);"<<std::endl;

	buf<<"		gl_FragColor=mixcolor;"<<std::endl;
	buf<<"	}"<<std::endl;

	//------------------------------------------------------------
	v_buf<<"#extension GL_EXT_gpu_shader4 : enable"<<std::endl;
	v_buf<<"varying float LightIntensity;"<<std::endl;
	v_buf<<"void main()"<<std::endl;
	v_buf<<"  {"<<std::endl;
	v_buf<<"       vec3 normal = normalize(gl_NormalMatrix * gl_Normal);"<<std::endl;
	v_buf<<"       vec3 lightDir = normalize(vec3(gl_LightSource[0].position));"<<std::endl;
	v_buf<<"       vec3 halfVector = normalize(gl_LightSource[0].halfVector.xyz);"<<std::endl;
	v_buf<<"       float NdotL = max(dot(lightDir, normal), 0.0);"<<std::endl;
	v_buf<<"       LightIntensity = gl_LightSource[0].diffuse*NdotL + gl_LightSource[0].ambient;"<<std::endl;
	v_buf<<"	   gl_TexCoord[0]     = gl_MultiTexCoord0;"<<std::endl;
	v_buf<<"	   gl_Position     = ftransform();"<<std::endl;
	v_buf<<"	}"<<std::endl;


	std::string source = buf.str();
	std::string v_source = v_buf.str();

	fShader->setShaderSource(source);
	vShader->setShaderSource(v_source);

	_program->addShader(fShader);
	_program->addShader(vShader);


	osg::Uniform* u = new osg::Uniform(osg::Uniform::SAMPLER_2D_ARRAY, "tex");
	_uniforms.push_back(u);


}

void ImageLayersRenderTech::init2D()
{
	osg::Shader* fShader = new osg::Shader(osg::Shader::FRAGMENT);

	osg::Shader* vShader = new osg::Shader(osg::Shader::VERTEX);

	std::stringstream buf;
	std::stringstream v_buf;

	buf<<"#extension GL_EXT_gpu_shader4 : enable"<<std::endl;

	buf<<"uniform sampler2D tex;"<<std::endl;
	buf<<"uniform sampler2D tex1;"<<std::endl;
	buf<<"uniform sampler2D tex2;"<<std::endl;
	buf<<"uniform sampler2D tex3;"<<std::endl;
	buf<<"uniform sampler2D tex4;"<<std::endl;
	buf<<"uniform sampler2D tex5;"<<std::endl;
	buf<<"uniform sampler2D tex6;"<<std::endl;
	buf<<"uniform sampler2D tex7;"<<std::endl;
	buf<<"varying float LightIntensity;"<<std::endl;

	buf<<"void main()"<<std::endl;
	buf<<"{"<<std::endl;
	buf<<"		vec4 texCoord = (vec4(gl_TexCoord[0].st, floor(gl_TexCoord[0].r), gl_TexCoord[0].q));"<<std::endl;
	buf<<"		vec4 mixcolor = gl_Color;"<<std::endl;

	buf<<"		vec4 color0 = texture2D(tex, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_0 = mix(mixcolor.rgb,color0.rgb,color0.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_0,mixcolor.a);"<<std::endl;
	
	buf<<"		vec4 color1 = texture2D(tex1, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_1 = mix(mixcolor.rgb,color1.rgb,color1.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_1,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color2 = texture2D(tex2, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_2 = mix(mixcolor.rgb,color2.rgb,color2.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_2,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color3 = texture2D(tex3, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_3 = mix(mixcolor.rgb,color3.rgb,color3.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_3,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color4 = texture2D(tex4, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_4 = mix(mixcolor.rgb,color4.rgb,color4.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_4,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color5 = texture2D(tex5, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_5 = mix(mixcolor.rgb,color5.rgb,color5.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_1,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color6 = texture2D(tex6, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_6 = mix(mixcolor.rgb,color6.rgb,color6.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_6,mixcolor.a);"<<std::endl;

	buf<<"		vec4 color7 = texture2D(tex7, gl_TexCoord[0].xy);"<<std::endl;
	buf<<"		vec3 tcolor3_7 = mix(mixcolor.rgb,color7.rgb,color7.a);"<<std::endl;
	buf<<"		mixcolor = vec4(tcolor3_1,mixcolor.a);"<<std::endl;

	buf<<"		gl_FragColor=mixcolor;"<<std::endl;
	buf<<"	}"<<std::endl;

	//------------------------------------------------------------
	v_buf<<"#extension GL_EXT_gpu_shader4 : enable"<<std::endl;
	v_buf<<"uniform vec3 LightPosition;"<<std::endl;

	v_buf<<"const float SpecularContribution = 0.7;"<<std::endl;
	v_buf<<"const float DiffuseContribution  = 1.0 - SpecularContribution;"<<std::endl;

	v_buf<<"varying float LightIntensity;"<<std::endl;
	v_buf<<"varying vec2  MCposition;"<<std::endl;

	v_buf<<"void main()"<<std::endl;
	v_buf<<"{"<<std::endl;
	v_buf<<"		vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);"<<std::endl;

	v_buf<<"		vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);"<<std::endl;
	v_buf<<"		vec3 lightVec   = normalize(LightPosition - ecPosition);"<<std::endl;
	v_buf<<"		vec3 reflectVec = reflect(-lightVec, tnorm);"<<std::endl;

	v_buf<<"		vec3 viewVec    = normalize(-ecPosition);"<<std::endl;
	v_buf<<"		float diffuse   = max(dot(lightVec, tnorm), 0.0)*5;"<<std::endl;
	v_buf<<"		float spec      = 0.0;"<<std::endl;
	v_buf<<"		if (diffuse > 0.0)"<<std::endl;
	v_buf<<"		{"<<std::endl;
	v_buf<<"		spec = max(dot(reflectVec, viewVec), 0.0)/5;"<<std::endl;
	//v_buf<<"		spec = pow(spec, 8.0);"<<std::endl;
	v_buf<<"		}"<<std::endl;
	v_buf<<"		LightIntensity  = DiffuseContribution * diffuse +"<<std::endl;
	v_buf<<"		SpecularContribution * spec;"<<std::endl;
	v_buf<<"		MCposition      = gl_Vertex.xy;"<<std::endl;

	v_buf<<"		gl_TexCoord[0]     = gl_MultiTexCoord0;"<<std::endl;
	v_buf<<"		gl_Position     = ftransform();"<<std::endl;
	v_buf<<"	}"<<std::endl;

	std::string source = buf.str();
	//std::string v_source = v_buf.str();

	fShader->setShaderSource(source);
	//vShader->setShaderSource(v_source);

	_program->addShader(fShader);
	//_program->addShader(vShader);

	osg::Uniform* u0 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex");
	u0->set(0);
	osg::Uniform* u1 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex1");
	u1->set(1);
	osg::Uniform* u2 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex2");
	u2->set(2);
	osg::Uniform* u3 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex3");
	u3->set(3);
	osg::Uniform* u4 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex4");
	u4->set(4);
	osg::Uniform* u5 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex5");
	u5->set(5);
	osg::Uniform* u6 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex6");
	u6->set(6);
	osg::Uniform* u7 = new osg::Uniform(osg::Uniform::SAMPLER_2D, "tex7");
	u7->set(7);

	osg::Uniform* u = new osg::Uniform("LightPosition",osg::Vec3(7000000,7000000,7000000));

	_uniforms.push_back(u0);
	_uniforms.push_back(u1);
	_uniforms.push_back(u2);
	_uniforms.push_back(u3);
	_uniforms.push_back(u4);
	_uniforms.push_back(u5);
	_uniforms.push_back(u6);
	_uniforms.push_back(u7);
	_uniforms.push_back(u);
}