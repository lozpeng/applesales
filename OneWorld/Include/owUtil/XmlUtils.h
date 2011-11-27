
#ifndef owUtil_XML_UTILS_H
#define owUtil_XML_UTILS_H

#include <owUtil/export.h>
#include <owUtil/config.h>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <string>
#include <vector>
#include <map>
#include <stack>

// XML support utilites.

namespace owUtil
{
    extern std::string trim( const std::string& in );

    class OWUTIL_EXPORT XmlNode : public osg::Referenced
    {
    public:
        XmlNode();
        
        virtual ~XmlNode() { }

        virtual bool isElement() const =0;

        virtual bool isText() const =0;
    };

    typedef std::vector<osg::ref_ptr<XmlNode> > XmlNodeList;

    typedef std::map<std::string,std::string> XmlAttributes;

    class OWUTIL_EXPORT XmlElement : public XmlNode
    {
    public:
        XmlElement( const std::string& name );
        
        XmlElement( const std::string& name, const XmlAttributes& attrs );

        XmlElement( const Config& conf );
        
        virtual ~XmlElement() { }

        const std::string& getName() const;

        void setName( const std::string& name );

        XmlAttributes& getAttrs();
        
        const XmlAttributes& getAttrs() const;

        const std::string& getAttr( const std::string& key ) const;

        XmlNodeList& getChildren();
        
        const XmlNodeList& getChildren() const;
        
        XmlElement* getSubElement( const std::string& name ) const;
        
        XmlNodeList getSubElements( const std::string& name ) const;
        
        std::string getText() const;
        
        std::string getSubElementText( const std::string& tag ) const;

        void addSubElement(const std::string& tag, const std::string& text);

        void addSubElement(const std::string& tag, const Properties& attrs, const std::string& text);

        Config getConfig() const;

    public: // XmlNode
        virtual bool isElement() const { return true; }

        virtual bool isText() const { return false; }

    private:
        std::string name;
        XmlAttributes attrs;
        XmlNodeList children;        
    };

    typedef std::vector<osg::ref_ptr<XmlElement> > XmlElementList;
    
    typedef std::stack<osg::ref_ptr<XmlElement> > XmlElementStack;
    
    typedef std::stack<XmlElement*> XmlElementNoRefStack;

    class OWUTIL_EXPORT XmlText : public XmlNode
    {
    public:
        XmlText( const std::string& value );
        
        virtual ~XmlText() { }

        const std::string& getValue() const;

    public: // XmlNode
        virtual bool isElement() const { return false; }

        virtual bool isText() const { return true; }
        
    private:
        std::string value;
    };  
    
    class OWUTIL_EXPORT XmlDocument : public XmlElement
    {
    public:
        XmlDocument( const std::string& source_uri ="" );

        XmlDocument( const Config& conf );
        
        virtual ~XmlDocument();
        
        static XmlDocument* load( std::istream& in );
        
        void store( std::ostream& out ) const;

        const std::string& getName() const;

    protected:
        std::string source_uri;
        std::string name;
        osg::ref_ptr<XmlElement> root;
    };
}

#endif // OSGEARTH_XML_UTILS_H
