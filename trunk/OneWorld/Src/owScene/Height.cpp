#include <owScene/Height.h>

using namespace owScene;

Height::Height() : _rows(0),_columns(0)
{
	;
}

Height::~Height()
{

}

Height::Height(unsigned int rows,unsigned int columns,float defvalue) : _rows(rows),_columns(columns)
{
	allocate(_rows,_columns,defvalue);
}

Height::Height(const Height& height)
{
	allocate(height.getRows(),height.getColumns());
	for(unsigned int j=0;j<_rows;++j)
	{
		for(unsigned int i=0;i<_columns;++i)
		{
			setValue(j,i,height.getValue(j,i));
		}
	}
}

unsigned int Height::getRows() const
{
	return _rows;
}

void Height::allocate(unsigned int rows, unsigned int columns, float defvalue)
{
	if(rows==0 || columns==0)
		return;
	_columns = columns;
	_rows = rows;
	_hg.resize(rows);
	for(unsigned int j=0;j<rows;++j)
	{
		for(unsigned int i=0;i<columns;++i)
		{
			_hg[j].push_back(defvalue);
		}
	}
}

unsigned int Height::getColumns() const
{
	return _columns;
}

void Height::setValue(unsigned int row,unsigned int column,float v)
{
	if(row>=_rows || column>=_columns)
		return;
	_hg[row][column]=v;
}

float Height::getValue(unsigned int row, unsigned int column) const
{
	if(row>=_rows || column>=_columns)
		return 0.f;
	return _hg[row][column];
}


//////////////////////////////////////////////////////////////////////////HeightProxy

HeightProxy::HeightProxy(Height* h) : _height(h)
{
	
}

HeightProxy::HeightProxy()
{

}

HeightProxy::~HeightProxy()
{

}

void HeightProxy::set(Height* h)
{
	_height = h;
}

Height* HeightProxy::get()
{
	return _height.get();
}

bool HeightProxy::valid()
{
	return _height.valid();
}