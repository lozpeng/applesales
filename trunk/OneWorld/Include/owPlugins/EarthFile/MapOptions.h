#ifndef _OWPLUGINS_MAPOPTIONS_H
#define _OWPLUGINS_MAPOPTIONS_H

#include <owScene/export.h>
#include <owUtil/config.h>

using namespace owUtil;

namespace owPlugins
{
   /**
     * Configuration for a runtime map.
     */
	class MapOptions : public ConfigOptions // no export (header-only)
    {
    public:
        enum CoordinateSystemType
        {
            CSTYPE_GEOCENTRIC,
            CSTYPE_GEOCENTRIC_CUBE,
            CSTYPE_PROJECTED
        };		

    public:
        MapOptions( const ConfigOptions& options =ConfigOptions() )
            : ConfigOptions( options ),
              _referenceURI("")
        {
            fromConfig(_conf);
        }

        /**
         * Human-readable name of the map.
         */
        optional<std::string> name() { return _name; }
        const optional<std::string> name() const { return _name; }

    public:
        /**
         * A reference location that drivers can use to load data from relative locations.
         * NOTE: this is a runtime-only property and is NOT serialized in the ConfigOptions.
         */
        optional<std::string>& referenceURI() { return _referenceURI; }
        const optional<std::string>& referenceURI() const { return _referenceURI; }
    
    public:
        Config getConfig() const;

        void mergeConfig( const Config& conf ) {
            ConfigOptions::mergeConfig( conf );
            fromConfig( conf );
        }

    private:
        void fromConfig( const Config& conf );

        optional<std::string>          _name;
        optional<std::string>          _referenceURI;
    };
}

#endif