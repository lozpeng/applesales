#ifndef OWSCENE_FEATURECURSOR_H_
#define OWSCENE_FEATURECURSOR_H_

#include <owScene/export.h>
#include <owScene/Feature.h>
#include <osg/Referenced>

namespace owScene
{
	class OWSCENE_EXPORT FeatureCursor : public osg::Referenced
	{
	public:
		FeatureCursor(){}

		virtual void reset() = 0;

		virtual bool hasNext() = 0;

		virtual Feature* next() = 0;

	protected:

		virtual ~FeatureCursor() {}
	};
}

#endif //OWSCENE_FEATURECURSOR_H_