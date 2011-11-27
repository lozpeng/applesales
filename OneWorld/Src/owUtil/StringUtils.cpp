
#include <owUtil/StringUtils.h>

using namespace owUtil;

StringTokenizer::StringTokenizer( const std::string& delims, const std::string& quotes ) :
_allowEmpties( true ),
_trimTokens  ( true )
{
    addDelims( delims );
    addQuotes( quotes );
}

void
StringTokenizer::addDelim( char delim, bool keep )
{
    _delims[delim] = keep;
}

void
StringTokenizer::addDelims( const std::string& delims, bool keep )
{
    for( unsigned i=0; i<delims.size(); ++i )
        addDelim( delims.at(i), keep );
}

void
StringTokenizer::addQuote( char quote, bool keep )
{
    _quotes[quote] = keep;
}

void
StringTokenizer::addQuotes( const std::string& quotes, bool keep )
{
    for( unsigned i=0; i<quotes.size(); ++i )
        addQuote( quotes.at(i), keep );
}

void
StringTokenizer::tokenize( const std::string& input, StringVector& output ) const
{
    std::stringstream buf;
    bool quoted = false;
    for( std::string::const_iterator i = input.begin(); i != input.end(); ++i )
    {
        char c = *i;    

        TokenMap::const_iterator q = _quotes.find( c );

        if ( quoted )
        {
            if ( q != _quotes.end() )
            {
                quoted = false;
                if ( q->second )
                    buf << c;
            }
            else
            {
                buf << c;
            }
        }
        else
        {
            if ( q != _quotes.end() )
            {
                quoted = true;
                if ( q->second )
                    buf << c;
            }
            else
            {
                TokenMap::const_iterator d = _delims.find( c );
                if ( d == _delims.end() )
                {
                    buf << c;
                }
                else
                {
                    std::string token = _trimTokens ? trim(buf.str()) : buf.str();

                    if ( _allowEmpties || !token.empty() )
                        output.push_back( token );

                    if ( d->second == true )
                    {
                        output.push_back( std::string(1, c) );
                    }

                    buf.str("");
                }
            }
        }       
    }

    std::string last = _trimTokens ? trim(buf.str()) : buf.str();
    if ( !last.empty() )
        output.push_back( last );
}

