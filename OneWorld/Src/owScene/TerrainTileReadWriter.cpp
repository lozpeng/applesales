#include <owScene/Registry.h>
#include <owScene/Terrain.h>
#include <owScene/TerrainTileFactory.h>
#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Registry>

using namespace owScene;

class TerrainTileReadWriter : public osgDB::ReaderWriter
{
public:
	TerrainTileReadWriter()
	{
		;
	}

	virtual const char* className()
	{
		return "Terrain Tile ReaderWriter";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "tile" );
	}

	virtual ReadResult readNode(const std::string& fileName, const Options* options) const
	{
		std::string ext = osgDB::getFileExtension( fileName );
		if ( !acceptsExtension( ext ) )
			return ReadResult::FILE_NOT_HANDLED;

		// 解析获取terrain的id号和块的id号
		unsigned int id, lod, x, y;
		sscanf(osgDB::getNameLessExtension(fileName).c_str(), "%d_%d_%d_%d", &id, &lod, &x, &y);

		Terrain* terrain = owScene::Registry::instance().getRegistTerrain(id);
		if(!terrain)
			return ReadResult::ERROR_IN_READING_FILE;

		TileKey key(lod,x,y);
		osg::Timer::instance()->setStartTick();
		osg::Node* tile = terrain->getTileFactory()->createTile(key);
		double span = osg::Timer::instance()->time_s();
		std::cout<<"End create Tile: "<<lod<<"_"<<x<<"_"<<y<<" used time "<<span<<" second."<<std::endl;
		if(tile)
			return ReadResult(tile);

		return ReadResult::ERROR_IN_READING_FILE;
	}
};

REGISTER_OSGPLUGIN(tile, TerrainTileReadWriter)