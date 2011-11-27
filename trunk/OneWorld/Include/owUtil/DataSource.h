#ifndef _GSTERRAIN_DATASOURCE_H_
#define _GSTERRAIN_DATASOURCE_H_

#include <owUtil/export.h>
#include <owUtil/config.h>
#include <owUtil/ProgressBase.h>
#include <owUtil/SpatialProperty.h>
#include <osg/Object>

namespace owUtil
{
	class OWUTIL_EXPORT DataSource : public osg::Object
	{
	public:

		bool bValid() { return _bValid; }

		const SpatialProperty* getSP() const { return _sp; }
		SpatialProperty* getSP() {return _sp;}

		virtual bool Connect(owUtil::ProgressBase* p =NULL) = 0;
		virtual bool disConnect(owUtil::ProgressBase* p = NULL) = 0;
		virtual std::string		getUrl(){return "";}
	protected:

		DataSource() : _bValid(false) { }
		virtual ~DataSource(){;}

		virtual void read(const Config& config) {}
		virtual void write(Config& config) const {}

		void setValid(bool b) { _bValid = b; }
		void setSP(SpatialProperty* sp) { _sp=sp; }

	private:

		osg::ref_ptr<SpatialProperty> _sp;
		bool _bValid;
	};
}

#endif //_GSTERRAIN_DATASOURCE_H_