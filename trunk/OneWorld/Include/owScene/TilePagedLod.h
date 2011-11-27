#ifndef OWSCENE_TILEPAGEDLOD_H_
#define OWSCENE_TILEPAGEDLOD_H_

#include <owScene/export.h>
#include <owScene/Terrain.h>

#include <osg/PagedLOD>

namespace owScene
{
	/** TilePagedLod：在析构中移除Terrain对象中tile缓冲的相应tile*/
	class TilePagedLod : public osg::PagedLOD
	{
	public:
		TilePagedLod(Terrain* terrain);

		TilePagedLod(const TilePagedLod&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(gs, TilePagedLod);

	protected:
		TilePagedLod();
		~TilePagedLod();

	private:

		osg::ref_ptr<Terrain> _terrain;
	};
}

#endif //OWSCENE_TILEPAGEDLOD_H_