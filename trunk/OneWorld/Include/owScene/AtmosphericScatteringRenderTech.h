#ifndef OWSCENE_ATMOSPHERICRENDERTECH_H_
#define OWSCENE_ATMOSPHERICRENDERTECH_H_

#include <owScene/export.h>
#include <owScene/TerrainRenderTech.h>
#include <osgGA/CameraManipulator>
#include <osgViewer/Viewer>

namespace owScene
{
	/** 地形渲染技术，地形的表现，采用shader技术*/
	class OWSCENE_EXPORT  AtmosphericScatteringRenderTech: public TerrainRenderTech
	{	
	public:
		AtmosphericScatteringRenderTech(osgViewer::Viewer* viewer);

		//META_Object(gvTerrain, AtmosphericScatteringRenderTech);

		//返回一个外大气层的节点
		virtual osg::Node* GetOSGNode(){return/* NULL;*/_atmosphereNode.get();}

		virtual void apply(TerrainTile* tile);
		virtual void unapply(TerrainTile* tile);


	private:

		AtmosphericScatteringRenderTech(const AtmosphericScatteringRenderTech& tech, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

		void initScattieringParameter();

		//生成外面的一个大气层球体mAtmosphereNode
		void createOutterAtmosphere();
		osg::Geode* createRealPlanet( float radius, const std::string& name, const osg::Vec4& color , const std::string& textureName,bool isClockWise);

		//给mAtmosphereNode添加shader
		void addOutterShader();
		void addInnerShader();

		bool loadShaderSource( osg::Shader* shader, const std::string& fileName );

	private:
		osg::ref_ptr<osg::Node> _atmosphereNode;
		osgViewer::Viewer* _viewer;
		osg::Vec3                 _lightPos;
		osg::Vec3				  _vLightDirection;

		int _nSamples;

		// Rayleigh scattering constant
		float _Kr, _Kr4PI;

		// Mie scattering constant
		float _Km, _Km4PI;

		// Sun brightness constant
		float _ESun;

		// The Mie phase asymmetry factor
		float _g;
		float _fExposure;

		float _fInnerRadius;
		float _fOuterRadius;
		float _fScale;
		//[0] 650 nm for red，//[1] 570 nm for green，//[2] 475 nm for blue
		float _fWavelength[3];
		float _fWavelength4[3];

		float _fRayleighScaleDepth;
		float _fMieScaleDepth;
	};
}
#endif//OWSCENE_ATMOSPHERICRENDERTECH_H_