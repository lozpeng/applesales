#include <owScene/SunModel.h>
#include <owUtil/ephemeris.h>
#include <osg/LightSource>
#include <osg/Vec4>

using namespace owScene;
using namespace owUtil;

SunModel::SunModel(const SunModel& fn,const osg::CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(fn,copyop)
{

}

void SunModel::Init(int year, int month, int day, int hour, int min, int sec, double lon)
{
	if(_sunls.get())
		return;

	//Ì«Ñô¹âÔ´Î»ÖÃ
	osg::Vec3d pos;
	double alt,az;

	_date.year = year; _date.month = month; _date.day = day;
	_date.hour = hour; _date.min = min; _date.sec = sec;

	double _mjd= Ephemeris::GetMJD(year, month, day, hour, min, sec, lon);
	Ephemeris::GetSunPos2(_mjd, pos.x(), pos.y(), pos.z());

	//
	_sunls = new osg::LightSource;
	_sunls->getLight()->setPosition(osg::Vec4(pos,0.0));
	_sunls->getLight()->setAmbient(osg::Vec4(0.3,0.3,0.3,1.0));
	_sunls->getLight()->setDiffuse(osg::Vec4(0.8,0.8,0.8,1.0));
	_sunls->getLight()->setSpecular(osg::Vec4(0.8,0.8,0.8,1.0));

	addChild(_sunls.get());


}
