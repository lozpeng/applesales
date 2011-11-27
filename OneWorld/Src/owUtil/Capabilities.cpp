#include <owUtil/Capabilities.h>
#include <owUtil/Log.h>

#include <osg/FragmentProgram>
#include <osg/GraphicsContext>
#include <osg/GL>
#include <osg/GLExtensions>
#include <osg/GL2Extensions>
#include <osg/Texture>
#include <osgViewer/Version>


using namespace owUtil;

#define LC "[Capabilities] "

// ---------------------------------------------------------------------------
// A custom P-Buffer graphics context that we will use to query for OpenGL 
// extension and hardware support. (Adapted from osgconv in OpenSceneGraph)

struct MyGraphicsContext
{
	MyGraphicsContext()
	{
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		traits->x = 0;
		traits->y = 0;
		traits->width = 1;
		traits->height = 1;
		traits->windowDecoration = false;
		traits->doubleBuffer = false;
		traits->sharedContext = 0;
		traits->pbuffer = false;

		// Intel graphics adapters dont' support pbuffers, and some of their drivers crash when
		// you try to create them. So by default we will only use the unmapped/pbuffer method
		// upon special request.
		if ( getenv( "GS_USE_PBUFFER_TEST" ) )
		{
			traits->pbuffer = true;
			LOG_INFO("Activating pbuffer test for graphics capabilities");
			_gc = osg::GraphicsContext::createGraphicsContext(traits.get());
			if ( !_gc.valid() )
				LOG_WARNING("Failed to create pbuffer");
		}

		if (!_gc.valid())
		{
			// fall back on a mapped window
			traits->pbuffer = false;
			_gc = osg::GraphicsContext::createGraphicsContext(traits.get());
		}

		if (_gc.valid()) 
		{
			_gc->realize();
			_gc->makeCurrent();

			if ( traits->pbuffer == false )
			{
				LOG_DEBUG("Realized graphics window for OpenGL operations.");
			}
			else
			{
				LOG_DEBUG("Realized pbuffer for OpenGL operations.");
			}
		}
		else
		{
			LOG_WARNING( "Failed to create graphic window too." );
		}
	}

	bool valid() const { return _gc.valid() && _gc->isRealized(); }

	osg::ref_ptr<osg::GraphicsContext> _gc;
};

// ---------------------------------------------------------------------------

#define SAYBOOL(X) (X?"yes":"no")

Capabilities& Capabilities::Instance()
{
	static Capabilities cp;
	return cp;
}

Capabilities::Capabilities() :
_maxFFPTextureUnits     ( 1 ),
_maxGPUTextureUnits     ( 1 ),
_maxGPUTextureCoordSets ( 1 ),
_maxTextureSize         ( 256 ),
_maxLights              ( 1 ),
_supportsGLSL           ( false ),
_GLSLversion            ( 1.0f ),
_supportsTextureArrays  ( false ),
_supportsMultiTexture   ( false ),
_supportsStencilWrap    ( true ),
_supportsTwoSidedStencil( false ),
_supportsTexture2DLod   ( false ),
_supportsMipmappedTextureUpdates( false )
{
	// little hack to force the osgViewer library to link so we can create a graphics context
	osgViewerGetVersion();

	// check the environment in order to disable ATI workarounds
	bool enableATIworkarounds = true;
	if ( ::getenv( "owUtil_DISABLE_ATI_WORKAROUNDS" ) != 0L )
		enableATIworkarounds = false;

	// create a graphics context so we can query OpenGL support:
	MyGraphicsContext mgc;

	if ( mgc.valid() )
	{
		osg::GraphicsContext* gc = mgc._gc.get();
		unsigned int id = gc->getState()->getContextID();
		const osg::GL2Extensions* GL2 = osg::GL2Extensions::Get( id, true );

		LOG_INFO("Detected hardware capabilities:");

		_vendor = std::string( reinterpret_cast<const char*>(glGetString(GL_VENDOR)) );

		std::ostringstream os;
		os.str()="";
		os<< "  Vendor = " << _vendor;
		LOG_INFO(os.str());

		_renderer = std::string( reinterpret_cast<const char*>(glGetString(GL_RENDERER)) );

		os.str()="";
		os<< "  Renderer = " << _renderer;
		LOG_INFO(os.str());

		_version = std::string( reinterpret_cast<const char*>(glGetString(GL_VERSION)) );

		os.str()="";
		os<< "  Version = " << _version;
		LOG_INFO(os.str());

		glGetIntegerv( GL_MAX_TEXTURE_UNITS, &_maxFFPTextureUnits );

		os.str()="";
		os<< "  Max FFP texture units = " << _maxFFPTextureUnits;
		LOG_INFO(os.str());

		glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &_maxGPUTextureUnits );

		os.str()="";
		os<< "  Max GPU texture units = " << _maxGPUTextureUnits;
		LOG_INFO(os.str());

		glGetIntegerv( GL_MAX_TEXTURE_COORDS_ARB, &_maxGPUTextureCoordSets );

		os.str()="";
		os<< "  Max GPU texture coordinate sets = " << _maxGPUTextureCoordSets;
		LOG_INFO(os.str());

		// Use the texture-proxy method to determine the maximum texture size 
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, &_maxTextureSize );
		for( int s = _maxTextureSize; s > 2; s >>= 1 )
		{
			glTexImage2D( GL_PROXY_TEXTURE_2D, 0, GL_RGBA8, s, s, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0L );
			GLint width = 0;
			glGetTexLevelParameteriv( GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width );
			if ( width == s )
			{
				_maxTextureSize = s;
				break;
			}
		}

		os.str()="";
		os<< "  Max texture size = " << _maxTextureSize;
		LOG_INFO(os.str());

		glGetIntegerv( GL_MAX_LIGHTS, &_maxLights );


		os.str()="";
		os<< "  Max lights = " << _maxLights;
		LOG_INFO(os.str());

		_supportsGLSL = GL2->isGlslSupported();


		os.str()="";
		os<< "  GLSL = " << SAYBOOL(_supportsGLSL) ;
		LOG_INFO(os.str());

		if ( _supportsGLSL )
		{
			_GLSLversion = GL2->getLanguageVersion();
			os.str()="";
			os<< "  GLSL Version = " << _GLSLversion ;
			LOG_INFO(os.str());
		}

		_supportsTextureArrays = 
			_supportsGLSL &&
			osg::getGLVersionNumber() >= 2.0 && // hopefully this will detect Intel cards
			osg::isGLExtensionSupported( id, "GL_EXT_texture_array" );

		os.str()="";
		os<< "  Texture arrays = " << SAYBOOL(_supportsTextureArrays) ;
		LOG_INFO(os.str());

		_supportsTexture3D = osg::isGLExtensionSupported( id, "GL_EXT_texture3D" );

		os.str()="";
		os<< "  3D textures = " << SAYBOOL(_supportsTexture3D);
		LOG_INFO(os.str());

		_supportsMultiTexture = 
			osg::getGLVersionNumber() >= 1.3 ||
			osg::isGLExtensionSupported( id, "GL_ARB_multitexture") ||
			osg::isGLExtensionSupported( id, "GL_EXT_multitexture" );

		os.str()="";
		os<< "  Multitexturing = " << SAYBOOL(_supportsMultiTexture) ;
		LOG_INFO(os.str());

		_supportsStencilWrap = osg::isGLExtensionSupported( id, "GL_EXT_stencil_wrap" );

		os.str()="";
		os<< "  Stencil wrapping = " << SAYBOOL(_supportsStencilWrap) ;
		LOG_INFO(os.str());

		_supportsTwoSidedStencil = osg::isGLExtensionSupported( id, "GL_EXT_stencil_two_side" );

		os.str()="";
		os<< "  2-sided stencils = " << SAYBOOL(_supportsTwoSidedStencil) ;
		LOG_INFO(os.str());

		//_supportsTexture2DLod = osg::isGLExtensionSupported( id, "GL_ARB_shader_texture_lod" );
		//OE_INFO << LC << "  texture2DLod = " << SAYBOOL(_supportsTexture2DLod) << std::endl;

		bool isATI = _vendor.length() >= 4 && ::strncmp(_vendor.c_str(), "ATI ", 4) == 0;

		_supportsMipmappedTextureUpdates = isATI && enableATIworkarounds ? false : true;
	}
}