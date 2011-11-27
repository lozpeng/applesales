#include <owPlugins/ReaderWriterEarthFile/MapOptions.h>

using namespace owPlugins;

void MapOptions::fromConfig( const Config& conf )
{
	conf.getIfSet( "name", _name );

}

Config
MapOptions::getConfig() const
{

	return _conf;
}
