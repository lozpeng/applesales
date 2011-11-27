#ifndef _SUN_MODEL_H
#define _SUN_MODEL_H

#include <osg/Group>
#include <owScene/export.h>
#include <ctime>
#include <osg/CopyOp>

namespace owScene
{
	struct Date
	{
		int year,month,day,hour,min,sec;
	};

	class OWSCENE_EXPORT SunModel : public osg::Group
	{
	public:
		SunModel() {};

		SunModel(const SunModel&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		META_Node(owUtil,SunModel);

	public:
		void Init(int year, int month, int day, int hour, int min, int sec, double lon);

	protected:
		~SunModel(){}

	private:
		osg::ref_ptr<osg::LightSource> _sunls;
		Date _date;

	};
}

#endif