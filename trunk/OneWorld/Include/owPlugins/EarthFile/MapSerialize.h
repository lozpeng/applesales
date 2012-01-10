#ifndef _OWPLUGINS_MAPSERIALIZE_H
#define _OWPLUGINS_MAPSERIALIZE_H

#include <owUtil/XmlUtils.h>
#include <owScene/Terrain.h>
#include <owScene/Scene.h>

namespace owPlugins
{
	class MapSerialize
	{
	public:
		owScene::Scene* deserialize( const Config& conf, const std::string& referenceURI );

	};
}

#endif