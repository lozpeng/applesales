#ifndef owUtil_HTTP_CLIENT_H
#define owUtil_HTTP_CLIENT_H 1

#include <OpenThreads/Thread>
#include <owUtil/config.h>
#include <osg/ref_ptr>
#include <osg/Referenced>
#include <osgDB/ReaderWriter>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <owUtil/ProgressBase.h>

namespace owUtil
{
    /**
     * Proxy server configuration.
     */
    class OWUTIL_EXPORT ProxySettings
    {
    public:
        ProxySettings( const Config& conf =Config() );
        ProxySettings( const std::string& host, int port );

        std::string& hostName() { return _hostName; }
        const std::string& hostName() const { return _hostName; }

        int& port() { return _port; }
        const int& port() const { return _port; }

		std::string& userName() { return _userName; }
        const std::string& userName() const { return _userName; }

		std::string& password() { return _password; }
        const std::string& password() const { return _password; }

    public:
        virtual Config getConfig() const;
        virtual void mergeConfig( const Config& conf );

    protected:
        std::string _hostName;
        int _port;
		std::string _userName;
		std::string _password;
    };


    /**
     * An HTTP request for use with the HTTPClient class.
     */
    class OWUTIL_EXPORT HTTPRequest
    {
    public:
        /** Constructs a new HTTP request that will acces the specified base URL. */
        HTTPRequest( const std::string& url );

        /** copy constructor. */
        HTTPRequest( const HTTPRequest& rhs );

        /** Adds an HTTP parameter to the request query string. */
        void addParameter( const std::string& name, const std::string& value );
        void addParameter( const std::string& name, int value );
        void addParameter( const std::string& name, double value );
        
        typedef std::map<std::string,std::string> Parameters;

        /** Ready-only access to the parameter list (as built with addParameter) */
        const Parameters& getParameters() const;

        /** Gets a copy of the complete URL (base URL + query string) for this request */
        std::string getURL() const;
        
    private:
        Parameters _parameters;
        std::string _url;
    };

    /**
     * An HTTP response object for use with the HTTPClient class - supports
     * multi-part mime responses.
     */
    class OWUTIL_EXPORT HTTPResponse
    {
    public:
        enum Code {
            NONE         = 0,
            OK           = 200,
            NOT_FOUND    = 404,
            SERVER_ERROR = 500
        };

    public:
        /** Constructs a response with the specified HTTP response code */
        HTTPResponse( long code =0L );

        /** Copy constructor */
        HTTPResponse( const HTTPResponse& rhs );

        /** Gets the HTTP response code (Code) in this response */
        long getCode() const;

        /** True is the HTTP response code is OK (200) */
        bool isOK() const;

        /** True if the request associated with this response was cancelled before it completed */
        bool isCancelled() const;

        /** Gets the number of parts in a (possibly multipart mime) response */
        unsigned int getNumParts() const;

        /** Gets the input stream for the nth part in the response */
        std::istream& getPartStream( unsigned int n ) const;

        /** Gets the nth response part as a string */
        std::string getPartAsString( unsigned int n ) const;

        /** Gets the length of the nth response part */
        unsigned int getPartSize( unsigned int n ) const;
        
        /** Gets the HTTP header associated with the nth multipart/mime response part */
        const std::string& getPartHeader( unsigned int n, const std::string& name ) const;

        /** Gets the master mime-type returned by the request */
        const std::string& getMimeType() const;

    private:
        struct Part : public osg::Referenced
        {
            Part() : _size(0) { }
            typedef std::map<std::string,std::string> Headers;
            Headers _headers;
            unsigned int _size;
            std::stringstream _stream;
        };
        typedef std::vector< osg::ref_ptr<Part> > Parts;
        Parts _parts;
        long _response_code;
        std::string _mimeType;
        bool _cancelled;

        friend class HTTPClient;
    };

    /**
     * Utility class for making HTTP requests.
     *
     * TODO: This class will actually read data from disk as well, and therefore should
     * probably be renamed. It analyzes the URI and decides whether to make an  HTTP request
     * or to read from disk.
     */
    class OWUTIL_EXPORT HTTPClient : public osg::Referenced
    {
    public:
        enum ResultCode {
            RESULT_OK,
            RESULT_CANCELED,
            RESULT_NOT_FOUND,
            RESULT_SERVER_ERROR,
            RESULT_TIMEOUT,
            RESULT_NO_READER,
            RESULT_READER_ERROR,
            RESULT_UNKNOWN_ERROR
        };

        /**
         * Returns true is the result code represents a recoverable situation,
         * i.e. one in which retrying might work.
         */
        static bool isRecoverable( ResultCode code )
        {
            return
                code == RESULT_OK ||
                code == RESULT_SERVER_ERROR ||
                code == RESULT_TIMEOUT ||
                code == RESULT_CANCELED;
        }

        static std::string getResultCodeString( ResultCode code )
        {
            return
                code == RESULT_OK ? "OK" :
                code == RESULT_CANCELED ? "Read canceled" :
                code == RESULT_NOT_FOUND ? "Target not found" :
                code == RESULT_SERVER_ERROR ? "Server error" :
                code == RESULT_TIMEOUT ? "Read timed out" :
                code == RESULT_NO_READER ? "No suitable ReaderWriter found" :
                code == RESULT_READER_ERROR ? "ReaderWriter error" :
                "Unknown error";
        }

        /** Gest the user-agent string that all HTTP requests will use.
            TODO: This should probably move into the Registry */
		static const std::string& getUserAgent();

        /** Sets a user-agent string to use in all HTTP requests.
            TODO: This should probably move into the Registry */
		static void setUserAgent(const std::string& userAgent);

        /** Sets up proxy info to use in all HTTP requests.
            TODO: This should probably move into the Registry */
		static void setProxySettings( const ProxySettings &proxySettings );


    public:
        /**
         * Reads an image. Based on the structure of the URI, it will either try to fetch the
         * data using HTTP or simply read the file from disk.
         */
        static ResultCode readImageFile(
            const std::string& uri,
            osg::ref_ptr<osg::Image>& output,
            const osgDB::ReaderWriter::Options* options = 0,
            ProgressBase* callback = 0 );

        /**
         * Reads an osg::Node. Based on the structure of the URI, it will either try to fetch the
         * data using HTTP or simply read the file from disk.
         */
        static ResultCode readNodeFile(
            const std::string& uri,
            osg::ref_ptr<osg::Node>& output,
            const osgDB::ReaderWriter::Options* options = 0,
            ProgressBase* callback = 0 );

        /**
         * Reads a string. Based on the structure of the URI, it will either try to fetch the
         * data using HTTP or simply read the file from disk.
         */
        static ResultCode readString(
            const std::string& uri,
            std::string& output,
            ProgressBase* callback =0);

    public:

        /**
         * Performs an HTTP "GET".
         */
        static HTTPResponse get( const HTTPRequest& request,
                                 const osgDB::ReaderWriter::Options* = 0,
                                 ProgressBase* callback = 0);

        static HTTPResponse get( const std::string& url,
                                 const osgDB::ReaderWriter::Options* options = 0,
                                 ProgressBase* callback = 0);

    private:
        HTTPClient();
        ~HTTPClient();

        void readOptions( const osgDB::ReaderWriter::Options* options, std::string &proxy_host, std::string &proxy_port ) const;

        HTTPResponse doGet( const HTTPRequest& request,
                            const osgDB::ReaderWriter::Options* options = 0,
                            ProgressBase* callback = 0) const;

        HTTPResponse doGet( const std::string& url,
                            const osgDB::ReaderWriter::Options* options = 0,
                            ProgressBase* callback = 0 ) const;

        ResultCode doReadImageFile(
            const std::string& filename,
            osg::ref_ptr<osg::Image>& output,
            const osgDB::ReaderWriter::Options* options = 0,
            ProgressBase *callback = 0);

        ResultCode doReadNodeFile(
            const std::string& filename,
            osg::ref_ptr<osg::Node>& output,
            const osgDB::ReaderWriter::Options* options = 0,
            ProgressBase *callback = 0);

        ResultCode doReadString(
            const std::string& filename,
            std::string& output,
            ProgressBase *callback = 0);


        /**
         * Convenience method for downloading a URL directly to a file
         */
        bool downloadFile(const std::string& url, const std::string& filename);

    private:
        void *_curl_handle;
        std::string _previousPassword;
        long        _previousHttpAuthentication;


        static HTTPClient& getClient();

    private:
        void decodeMultipartStream(
            const std::string&   boundary,
            HTTPResponse::Part*  input,
            HTTPResponse::Parts& output) const;
    };
}

#endif // OSGEARTH_HTTP_CLIENT_H
