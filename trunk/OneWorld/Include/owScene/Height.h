#ifndef OWSCENE_HEIGHT_H_
#define OWSCENE_HEIGHT_H_

#include <owScene/export.h>
#include <osg/ref_ptr>
#include <osg/Referenced>
#include <vector>

namespace owScene
{
	/** 高程数据类：包含了一个二维float数据，用于存储高程数据*/
	class OWSCENE_EXPORT Height : public osg::Referenced
	{
	public:
		Height();
		~Height();

		Height(unsigned int rows,unsigned int columns,float defvalue=0.f);

		Height(const Height& height);

	public:

		void allocate(unsigned int rows, unsigned int columns, float defvalue=0.f);

		unsigned int getRows() const;
		unsigned int getColumns() const;

		void setValue(unsigned int row,unsigned int column,float v);
		float getValue(unsigned int row, unsigned int column) const;

	private:

		unsigned int _rows;
		unsigned int _columns;
		typedef std::vector<float> HeightRow;
		typedef std::vector<HeightRow> HeightGrid;
		HeightGrid _hg;
	};

	/** Height代理类，包含了一个Height对象，此对象可能为空*/
	class HeightProxy : public osg::Referenced
	{
	public:
		HeightProxy(Height* h);
		HeightProxy();

		~HeightProxy();

	public:

		void set(Height* h);
		Height* get();

		bool valid();

	private:

		osg::ref_ptr<Height> _height;
	};
}

#endif //OWSCENE_HEIGHT_H_