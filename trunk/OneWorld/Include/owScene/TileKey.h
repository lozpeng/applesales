#ifndef OWSCENE_TILEKEY_H_
#define OWSCENE_TILEKEY_H_

#include <owScene/export.h>
#include <string>

namespace owScene
{
	class OWSCENE_EXPORT TileKey
	{
	public:
		TileKey() : _level(-1),_x(-1),_y(-1){}
		TileKey(int level,int x, int y) : _level(level),_x(x),_y(y){}

		bool operator == (const TileKey& id) const
		{
			return _level==id.level() &&
				_x == id.x() &&
				_y == id.y();
		}

		bool operator != (const TileKey& id) const
		{
			return _level!=id.level() ||
				_x != id.x() ||
				_y != id.y();
		}

		int level() const { return _level; }
		int x() const { return _x; }
		int y() const { return _y; }

		void set(int level, int x, int y) { _level = level; _x=x; _y=y; }

		TileKey sub(unsigned int i) const;

		std::string tostring() const;

		enum NEIGHBORS
		{
			TOP=0,
			BOTTOM,
			LEFT,
			RIGHT,
			LEFTTOP,
			RIGHTTOP,
			LEFTBOTTOM,
			RIGHTBOTTOM
		};

		TileKey neighbor(NEIGHBORS nb);

		TileKey parent();

	private:

		int _level;
		int _x;
		int _y;
	};
}

#endif //OWSCENE_TILEKEY_H_