#ifndef owUtil_CAPABILITIES_H
#define owUtil_CAPABILITIES_H 1

#include <owUtil/export.h>
#include <osg/Referenced>
#include <string>

namespace owUtil
{
	class OWUTIL_EXPORT Capabilities : public osg::Referenced
	{
	public:

		static Capabilities& Instance();

		/** maximum # of texture units exposed in the fixed-function pipeline */
		int getMaxFFPTextureUnits() const { return _maxFFPTextureUnits; }

		/** maximum # of texture image units exposed in a GPU fragment shader */
		int getMaxGPUTextureUnits() const { return _maxGPUTextureUnits; }

		/** maximum # of texture coordinate sets available in a GPU fragment shader */
		int getMaxGPUTextureCoordSets() const { return _maxGPUTextureCoordSets; }

		/** maximum supported size (in pixels) of a texture */
		int getMaxTextureSize() const { return _maxTextureSize; }

		/** maximum number of openGL lights */
		int getMaxLights() const { return _maxLights; }

		/** whether the GPU supports shaders */
		bool supportsGLSL(float minimumVersion =1.0f) const { 
			return _supportsGLSL && _GLSLversion >= minimumVersion; }

		/** the GLSL version */
		float getGLSLVersion() const { return _GLSLversion; }

		/** whether the GPU supports texture arrays */
		bool supportsTextureArrays() const { return _supportsTextureArrays; }

		/** whether the GPU supports OpenGL 3D textures */
		bool supportsTexture3D() const { return _supportsTexture3D; }

		/** whether the GPU supports OpenGL multi-texturing */
		bool supportsMultiTexture() const { return _supportsMultiTexture; }

		/** whether the GPU supports OpenGL stencil wrapping extensions */
		bool supportsStencilWrap() const { return _supportsStencilWrap; }

		/** whether the GPU supports OpenGL the two-sided stenciling extension */
		bool supportsTwoSidedStencil() const { return _supportsTwoSidedStencil; }

		/** whether the GPU support the texture2dLod() function */
		bool supportsTexture2DLod() const { return _supportsTexture2DLod; }

		/** whether the GPU properly supports updating an existing texture with a new mipmapped image */
		bool supportsMipmappedTextureUpdates() const { return _supportsMipmappedTextureUpdates; }

	private:
		Capabilities();

	private:
		int  _maxFFPTextureUnits;
		int  _maxGPUTextureUnits;
		int  _maxGPUTextureCoordSets;
		int  _maxTextureSize;
		int  _maxLights;
		bool _supportsGLSL;
		float _GLSLversion;
		bool _supportsTextureArrays;
		bool _supportsTexture3D;
		bool _supportsMultiTexture;
		bool _supportsStencilWrap;
		bool _supportsTwoSidedStencil;
		bool _supportsTexture2DLod;
		bool _supportsMipmappedTextureUpdates;
		std::string _vendor;
		std::string _renderer;
		std::string _version;
	};
}

#endif //owUtil_CAPABILITIES_H
