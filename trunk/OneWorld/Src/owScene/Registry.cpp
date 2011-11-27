#include <owScene/Registry.h>
#include <owUtil/Log.h>


using namespace owScene;

Registry& Registry::instance()
{
	static Registry s_registry;
	return s_registry;
}

Registry::Registry()
{
	;
}

Registry::~Registry()
{
	_terrainmap.clear();
}

void Registry::registTerrain(Terrain* terrain)
{
	if(!terrain)
		return;
	_terrainmap[terrain->getUID()] = terrain;
}

void Registry::unRegisTerrain(int id)
{
	std::map<int,osg::ref_ptr<Terrain>>::iterator iter 
		= _terrainmap.find(id);
	if(iter!=_terrainmap.end())
		_terrainmap.erase(iter);
	else
	{
		std::ostringstream os;
		os<<"û���ҵ�id��Ϊ"<<id<<"�ĵ��Σ��Ƴ�δ���"<<std::endl;
		LOG_WARNING(os.str());
	}
}

Terrain* Registry::getRegistTerrain(int id)
{
	std::map<int,osg::ref_ptr<Terrain>>::iterator iter 
		= _terrainmap.find(id);
	if(iter!=_terrainmap.end())
		return (*iter).second.get();
	else
	{
		std::ostringstream os;
		os<<"û���ҵ�id��Ϊ"<<id<<"�ĵ��Σ����ؿ�"<<std::endl;
		LOG_WARNING(os.str());
	}
	return NULL;
}