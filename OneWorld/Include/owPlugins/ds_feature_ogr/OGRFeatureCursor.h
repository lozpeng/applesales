#ifndef OWPLUGIN_OGRFEATURECURSOR_H_
#define OWPLUGIN_OGRFEATURECURSOR_H_

#include <owScene/FeatureCursor.h>

using namespace owScene;

class OGRFeature;

namespace owPlugins
{
	typedef std::vector<OGRFeature*> OGRFeaturePtrList;

	class OGRFeatureCursor : public FeatureCursor
	{
	public:

		OGRFeatureCursor();
		~OGRFeatureCursor();

	public:

		virtual void reset();

		virtual bool hasNext();

		virtual Feature* next();

		OGRFeaturePtrList& GetFeatures() {return _features;}

	private:

		//��������Ҫ�صĻ���
		OGRFeaturePtrList _features;
		long _pos;

	};
}

#endif //OWPLUGIN_OGRFEATURECURSOR_H_