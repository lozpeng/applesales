#include <owScene/TileKey.h>
#include <sstream>
using namespace owScene;

TileKey TileKey::sub(unsigned int i) const
{
	TileKey result;
	unsigned int lod = _level + 1;
	unsigned int x = _x * 2;
	unsigned int y = _y * 2;
	switch (i)
	{
	case 0:
		{
			result.set(lod,x,y);
			break;
		}
	case 1:
		{
			x+=1;
			result.set(lod,x,y);
			break;
		}
	case 2:
		{
			y+=1;
			result.set(lod,x,y);
			break;
		}
	case 3:
		{
			x+=1;
			y+=1;
			result.set(lod,x,y);
			break;
		}
	default:
		break;
	}
	return result;
}

std::string TileKey::tostring() const
{
	std::ostringstream os;
	os<<_level<<"_"<<_x<<"_"<<_y;
	return os.str();
}

TileKey TileKey::neighbor(NEIGHBORS nb)
{
	TileKey key;
	switch (nb)
	{
	case TOP:
		{
			key.set(_level,_x,_y-1);
			break;
		}
	case 	BOTTOM:
		{
			key.set(_level,_x,_y+1);
			break;
		}
	case 	LEFT:
		{
			key.set(_level,_x-1,_y);
			break;
		}
	case 	RIGHT:
		{
			key.set(_level,_x+1,_y);
			break;
		}
	case 	LEFTTOP:
		{
			key.set(_level,_x-1,_y-1);
			break;
		}
	case 	RIGHTTOP:
		{
			key.set(_level,_x+1,_y-1);
			break;
		}
	case LEFTBOTTOM:
		{
			key.set(_level,_x-1,_y+1);
			break;
		}
	case 	RIGHTBOTTOM:
		{
			key.set(_level,_x+1,_y+1);
			break;
		}
	default:
		break;
	}

	return key;
}

TileKey TileKey::parent()
{
	TileKey parent;

	if (_level == 0) return parent;

	int level = _level-1;
	int x = _x/2;
	int y = _y/2;

	return TileKey(level,x,y);
}