
#ifndef owUtil_STRING_UTILS_H
#define owUtil_STRING_UTILS_H 1

#include <owUtil/export.h>
#include <osg/Vec4>
#include <osg/Vec4ub>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>

namespace owUtil
{
    typedef std::vector<std::string> StringVector;

    /** Replaces all the instances of "sub" with "other" in "s". */
    static std::string&
    replaceIn( std::string& s, const std::string& sub, const std::string& other)
    {
        if ( sub.empty() ) return s;
        size_t b=0;
        for( ; ; )
        {
            b = s.find( sub, b );
            if ( b == s.npos ) break;
            s.replace( b, sub.size(), other );
            b += other.size();
        }
        return s;
    }

    /**
     * Trims whitespace from the ends of a string.
     * by Rodrigo C F Dias
     * http://www.codeproject.com/KB/stl/stdstringtrim.aspx
     */
    static
    std::string trim( const std::string& in )
    {
        std::string whitespace (" \t\f\v\n\r");
        std::string str = in;
        std::string::size_type pos = str.find_last_not_of( whitespace );
        if(pos != std::string::npos) {
            str.erase(pos + 1);
            pos = str.find_first_not_of( whitespace );
            if(pos != std::string::npos) str.erase(0, pos);
        }
        else str.erase(str.begin(), str.end());
        return str;
    }

    /**
     * True is "ref" starts with "pattern"
     */
    static
    bool startsWith( const std::string& ref, const std::string& pattern )
    {
        return ref.find( pattern ) == 0;
    }

    /**
     * Splits a string up into a vector of strings based on a set of 
     * delimiters, quotes, and rules.
     */
    class OWUTIL_EXPORT StringTokenizer
    {
    public:
        StringTokenizer( const std::string& delims =" \t\r\n", const std::string& quotes ="'\"" );

        void tokenize( const std::string& input, StringVector& output ) const;

        bool& keepEmpties() { return _allowEmpties; }

        bool& trimTokens() { return _trimTokens; }

        void addDelim( char delim, bool keepAsToken =false );

        void addDelims( const std::string& delims, bool keepAsTokens =false );

        void addQuote( char delim, bool keepInToken =false );

        void addQuotes( const std::string& delims, bool keepInTokens =false );
        
    private:
        typedef std::map<char,bool> TokenMap;
        TokenMap _delims;
        TokenMap _quotes;
        bool     _allowEmpties;
        bool     _trimTokens;
    };

#if 0
    static 
    void tokenize( const std::string& input,
                   StringVector& output,
                   const std::string& delims =" \t\n\r", 
                   const std::string& quotes ="'\"",
                   bool allowEmpties =true,
                   bool keepDelims   =false,
                   bool keepQuotes   =false,
                   bool trimTokens   =true )
    {
        std::stringstream buf;
        bool quoted = false;
        for( std::string::const_iterator i = input.begin(); i != input.end(); ++i )
        {
            char c = *i;    
            if ( quoted ) {
                if ( quotes.find(c) != std::string::npos ) {
                    quoted = false;
                    if ( keepQuotes ) 
                        buf << c;
                }
                else {
                    buf << c;
                }
            }
            else {
                if ( quotes.find(c) != std::string::npos ) {
                    quoted = true;
                    if ( keepQuotes )
                        buf << c;
                }
                else if ( delims.find(c) == std::string::npos ) {
                    buf << c;
                }
                else {
                    std::string token = trimTokens ? trim(buf.str()) : buf.str();
                    if ( allowEmpties || !token.empty() )
                        output.push_back( token );
                    
                    if ( keepDelims )
                        output.push_back( std::string(1, c) );

                    buf.str("");
                }
            }       
        }
        std::string last = trimTokens ? trim(buf.str()) : buf.str();
        if ( !last.empty() )
            output.push_back( last );
    }
#endif

#if 0
    /**
     * Tokenizes a string.
     * http://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
     */
    class StringTokenizer 
    {
    public:
        StringTokenizer(const std::string& s)
            : _string(s), _offset(0), _delimiters(" \t\n\r") { }
        StringTokenizer(const std::string& s, const std::string& delimiters)
            : _string(s), _offset(0), _delimiters(delimiters) { }
        bool nextToken() {
            return nextToken( _delimiters ); }
        bool nextToken(const std::string& delimiters) {
            size_t i = _string.find_first_not_of(delimiters, _offset);
            if (std::string::npos == i) {
                _offset = _string.length();
                return false;
            }
            size_t j = _string.find_first_of(delimiters, i);
            if (std::string::npos == j) {
                _token = _string.substr(i);
                _offset = _string.length();
                return true;
            }
            _token = _string.substr(i, j - i);
            _offset = j;
            return true;
        }
        std::string token() const { 
            return trim( _token );
        }
    protected:
        const std::string _string;
        size_t _offset;
        std::string _token;
        std::string _delimiters;
    };
#endif

#if 0
    /**
     * Splits "input" into one or more strings in "output" based on the delimiting character(s) in "delims".
     */
    static
    void split( const std::string& input, const std::string& delims, std::vector<std::string>& output, bool allowEmpties =true )
    {
        StringTokenizer t(input, delims);
        while( t.nextToken() )
            if ( allowEmpties || !t.token().empty() )
                output.push_back( t.token() );
    }
#endif

    /** Returns a lower-case version of the input string. */
    static std::string
    toLower( const std::string& input )
    {
        std::string output = input;
        std::transform( output.begin(), output.end(), output.begin(), ::tolower );
        return output;
    }

    /** Parses a color string in the form "255 255 255 255" (r g b a [0..255]) into an OSG color. */
    static osg::Vec4ub
    stringToColor(const std::string& str, osg::Vec4ub default_value)
    {
        osg::Vec4ub color = default_value;
        std::istringstream strin(str);
        int r, g, b, a;
        if (strin >> r && strin >> g && strin >> b && strin >> a)
        {
            color.r() = (unsigned char)r;
            color.g() = (unsigned char)g;
            color.b() = (unsigned char)b;
            color.a() = (unsigned char)a;
        }
        return color;
    }

    /** Creates a string in the form "255 255 255 255" (r g b a [0..255]) from a color */
    static std::string
    colorToString( const osg::Vec4ub& c )
    {
        std::stringstream ss;
        ss << c.r() << " " << c.g() << " " << c.b() << " " << c.a();
        std::string ssStr;
        ssStr = ss.str();
        return ssStr;
    }

    /** Converts a string to a vec3f */
    static osg::Vec3f
    stringToVec3f( const std::string& str, const osg::Vec3f& default_value )
    {
        std::stringstream buf(str);
        osg::Vec3f out = default_value;
        buf >> out.x();
        if ( !buf.eof() ) {
            buf >> out.y() >> out.z();
        }
        else {
            out.y() = out.x();
            out.z() = out.x();
        }
        return out;
    }

    /** Converts a vec3f to a string */
    static std::string
    vec3fToString( const osg::Vec3f& v )
    {
        std::stringstream buf;
        buf << std::setprecision(6)
            << v.x() << " " << v.y() << " " << v.z()
            << std::endl;
        std::string result;
        result = buf.str();
        return result;
    }

    /** Parses an HTML color ("#rrggbb" or "#rrggbbaa") into an OSG color. */
    static osg::Vec4f
    htmlColorToVec4f( const std::string& html )
    {
        std::string t = html;
        std::transform( t.begin(), t.end(), t.begin(), ::tolower );
        osg::Vec4ub c(0,0,0,255);
        if ( t.length() >= 7 ) {
            c.r() |= t[1]<='9' ? (t[1]-'0')<<4 : (10+(t[1]-'a'))<<4;
            c.r() |= t[2]<='9' ? (t[2]-'0')    : (10+(t[2]-'a'));
            c.g() |= t[3]<='9' ? (t[3]-'0')<<4 : (10+(t[3]-'a'))<<4;
            c.g() |= t[4]<='9' ? (t[4]-'0')    : (10+(t[4]-'a'));
            c.b() |= t[5]<='9' ? (t[5]-'0')<<4 : (10+(t[5]-'a'))<<4;
            c.b() |= t[6]<='9' ? (t[6]-'0')    : (10+(t[6]-'a'));
            if ( t.length() == 9 ) {
                c.a() = 0;
                c.a() |= t[7]<='9' ? (t[7]-'0')<<4 : (10+(t[7]-'a'))<<4;
                c.a() |= t[8]<='9' ? (t[8]-'0')    : (10+(t[8]-'a'));
            }
        }
        return osg::Vec4f( ((float)c.r())/255.0f, ((float)c.g())/255.0f, ((float)c.b())/255.0f, ((float)c.a())/255.0f );
    }

    /** Makes an HTML color ("#rrggbb" or "#rrggbbaa") from an OSG color. */
    static std::string
    vec4fToHtmlColor( const osg::Vec4f& c )
    {
        std::stringstream buf;
        buf << "#";
        buf << std::hex << std::setw(2) << std::setfill('0') << (int)(c.r()*255.0f);
        buf << std::hex << std::setw(2) << std::setfill('0') << (int)(c.g()*255.0f);
        buf << std::hex << std::setw(2) << std::setfill('0') << (int)(c.b()*255.0f);
        if ( c.a() < 1.0f )
            buf << std::hex << std::setw(2) << std::setfill('0') << (int)(c.a()*255.0f);
        std::string ssStr = buf.str();
        return ssStr;
    }

    /** MurmurHash 2.0 (http://sites.google.com/site/murmurhash/) */
    static unsigned int
    hashString( const std::string& input )
    {
	    const unsigned int m = 0x5bd1e995;
	    const int r = 24;
        unsigned int len = input.length();
        const char* data = input.c_str();
	    unsigned int h = m ^ len; // using "m" as the seed.

	    while(len >= 4)
	    {
		    unsigned int k = *(unsigned int *)data;
		    k *= m; 
		    k ^= k >> r; 
		    k *= m;     		
		    h *= m; 
		    h ^= k;
		    data += 4;
		    len -= 4;
	    }
    	
	    switch(len)
	    {
	    case 3: h ^= data[2] << 16;
	    case 2: h ^= data[1] << 8;
	    case 1: h ^= data[0];
	            h *= m;
	    };

	    h ^= h >> 13;
	    h *= m;
	    h ^= h >> 15;

	    return h;
    }
    
    //------------------------------------------------------------------------
    // conversion templates

    // converts a string to primitive using serialization
    template<typename T> inline T
    as( const std::string& str, const T& default_value )
    {
        T temp = default_value;
        std::istringstream strin( str );
        if ( !strin.eof() ) strin >> temp;
        return temp;
    }

    // template specialization for a bool
    template<> inline bool
    as<bool>( const std::string& str, const bool& default_value )
    {
        std::string temp = str;
        std::transform( temp.begin(), temp.end(), temp.begin(), ::tolower );
        return
            temp == "true" || temp == "yes" || temp == "on" ? true :
            temp == "false" || temp == "no" || temp == "off" ? false :
            default_value;
    }

    template<> inline osg::Vec3f
    as<osg::Vec3f>( const std::string& str, const osg::Vec3f& default_value )
    {
        return stringToVec3f(str, default_value);
    }

    // template specialization for string
    template<> inline std::string
    as<std::string>( const std::string& str, const std::string& default_value )
    {
		return str.empty() ? default_value : str;
    }

    // converts a primitive to a string
    // TODO: precision??
    template<typename T> inline std::string
    toString(const T& value)
    {
        std::stringstream out;
		out << std::setprecision(20) << std::fixed << value;
        std::string outStr;
        outStr = out.str();
        return outStr;
    }

    // template speciallization for a bool to print out "true" or "false"
    template<> inline std::string
    toString<bool>(const bool& value)
    {
        return value ? "true" : "false";
    }

    template<> inline std::string
    toString<osg::Vec3f>(const osg::Vec3f& value)
    {
        return vec3fToString(value);
    }
}

#endif // OSGEARTH_STRING_UTILS_H

