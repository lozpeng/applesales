#ifndef owUtil_WMS_H
#define owUtil_WMS_H 1

#include <owUtil/export.h>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <osgDB/ReaderWriter>
#include <osg/Version>
#if OSG_MIN_VERSION_REQUIRED(2,9,5)
#include <osgDB/Options>
#endif


#include <string>
#include <vector>

namespace owUtil
{
    /**
    * A WMS Style
    */
    class OWUTIL_EXPORT WMSStyle : public osg::Referenced
    {
    public:
        WMSStyle();
        WMSStyle(const std::string& name, const std::string &title);

        /**
        *Gets the name of the style
        */
        const std::string& getName() {return _name;}

        /**
        *Sets the name of the style
        */
        void setName(const std::string &name) {_name = name;}

        /**
        *Gets the title of the style
        */
        const std::string& getTitle() {return _title;}

        /**
        *Sets the title of the style
        */
        void setTitle(const std::string &title) {_title = title;}
        
    protected:
        std::string _name;
        std::string _title;
    };

    /**
    *A WMS layer
    */
    class OWUTIL_EXPORT WMSLayer : public osg::Referenced
    {
    public:
        WMSLayer();

        /**
        *Gets the name of the layer
        */
        const std::string& getName() {return _name;}

        /**
        *Sets the name of the layer
        */
        void setName(const std::string &name) {_name = name;}

        /**
        *Gets the title of the layer
        */
        const std::string& getTitle() {return _title;}

        /**
        *Sets the title of the layer
        */
        void setTitle(const std::string &title) {_title = title;}

        /**
        *Gets the abstract of the layer
        */
        const std::string& getAbstract() {return _abstract;}

        /**
        *Sets the abstract of the layer
        */
        void setAbstract(const std::string &abstract) {_abstract = abstract;}

        /**
        *Gets the lat lon extents of the layer
        */
        void getLatLonExtents(double &minLon, double &minLat, double &maxLon, double &maxLat);

        /**
        *Sets the lat lon extents of the layer
        */
        void setLatLonExtents(double minLon, double minLat, double maxLon, double maxLat);

        /**
        *Gets the extents of the layer
        */
        void getExtents(double &minX, double &minY, double &maxX, double &maxY);

        /**
        *Sets the extents of the layer
        */
        void setExtents(double minX, double minY, double maxX, double maxY);


        /**A list of Styles*/
        typedef std::vector<WMSStyle> StyleList;

        /**
        *Gets this Layer's list of defined Styles
        */
        StyleList& getStyles() {return _styles;}

        /**A list of spatial references*/
        typedef std::vector<std::string> SRSList;

        /**
        *Gets this Layer's list of spatial references
        */
        SRSList& getSpatialReferences() {return _spatialReferences;}

        /**A list of Layers*/
        typedef std::vector< osg::ref_ptr<WMSLayer> > LayerList;

        /**
        *Gets this Layer's list of child Layers
        */
        LayerList& getLayers() {return _layers;}

        /**
        *Gets this Layer's parent layer
        */
        WMSLayer* getParentLayer() {return _parentLayer;}

        /**
        *Sets this Layer's parent layer
        */
        void setParentLayer( WMSLayer* layer ) {_parentLayer = layer;}

        /**
        *Finds the child Layer with the given name.
        *@returns
        *       The Layer with the given name or NULL if not found.
        */
        WMSLayer* getLayerByName(const std::string &name);
    protected:
        std::string _name;
        std::string _title;
        std::string _abstract;
        double _minLon, _minLat, _maxLon, _maxLat;
        double _minX, _minY, _maxX, _maxY;
        StyleList _styles;
        SRSList _spatialReferences;

        LayerList _layers;
        WMSLayer* _parentLayer;
    };

    /**
    *WMS Capabilities
    */
    class OWUTIL_EXPORT WMSCapabilities : public osg::Referenced
    {
    public:
        WMSCapabilities();

        /**
        *Gets the WMS capabilities version
        */
        const std::string& getVersion() {return _version;}

        /**
        *Sets the WMS capabilities version
        */
        void setVersion(const std::string& version) {_version = version;}

        /**A list of supported formats*/
        typedef std::vector<std::string> FormatList;

        /**
        *Gets the list of supported formats
        */
        FormatList& getFormats() {return _formats;}

        /**
        *Gets the Layer's for the Capabilities.
        */
        WMSLayer::LayerList& getLayers() {return _layers;}

        /**
        *Suggests an extension to use for WMS layers defined for the service.
        *This function will analyze the list of formats contained in the Capabilities request
        *and recommend the first format that has an OpenSceneGraph ReaderWriter that can support
        *it's extension.
        *@returns
        *       The suggested extension.
        */
        std::string suggestExtension();

        /**
        *Finds the child Layer with the given name.
        *@returns
        *       The Layer with the given name or NULL if not found.
        */
        WMSLayer* getLayerByName(const std::string &name);

    protected:
        FormatList _formats;
        WMSLayer::LayerList _layers;
        std::string _version;
    };

    /*
    * Reads Capabilities from a URL or file
    */
    class OWUTIL_EXPORT WMSCapabilitiesReader
    {
    public:
        static WMSCapabilities* read( const std::string &location, const osgDB::ReaderWriter::Options *options );
        static WMSCapabilities* read( std::istream &in );
    private:
        WMSCapabilitiesReader(){}
        WMSCapabilitiesReader(const WMSCapabilitiesReader &cr){}
    };

} // namespace owUtil

#endif //owUtil_WMS_H
