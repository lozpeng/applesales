#include <owScene/TilePagedLod.h>
#include <owUtil/FindNode.h>

using namespace owScene;
using namespace owUtil;

TilePagedLod::TilePagedLod(Terrain* terrain) : _terrain(terrain)
{

}

TilePagedLod::TilePagedLod() : _terrain(NULL)
{

}

TilePagedLod::TilePagedLod(const TilePagedLod& tlod,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
	: osg::PagedLOD(tlod,copyop)
{
	_terrain = tlod._terrain;
}

TilePagedLod::~TilePagedLod()
{
	owUtil::FindAllNodesOfTypeVisitor<TerrainTile> f;
	this->accept(f);
	std::vector<osg::ref_ptr<TerrainTile>>& find = f._foundNodes;
	std::vector<osg::ref_ptr<TerrainTile>>::iterator f_iter = find.begin();
	for(f_iter;f_iter!=find.end();++f_iter)
	{
		_terrain->unregisTerrainTile(*f_iter);
	}
}