#ifndef OWSCENE_LAYER_H_
#define OWSCENE_LAYER_H_

#include <owScene/export.h>
#include <owUtil/DataSource.h>
#include <owUtil/SpatialProperty.h>
#include <owUtil/ProgressBase.h>
#include <owUtil/config.h>
#include <owScene/Common.h>
#include <osg/Object>

using namespace osg;
using namespace owUtil;

namespace owScene
{
	class Terrain;
	/** 层，基类。子类包括：高程层，影像层和矢量层*/
	class OWSCENE_EXPORT Layer : public osg::Object
	{
	public:
		Layer();
		Layer(const Layer& lyr, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

	public:

		unsigned int getUID() const;

		/** 数据源*/
		void setDataSource(DataSource* datesource);
		DataSource* getDataSource() const;

		/** 有效级别*/
		void setLevel(unsigned int min,unsigned int max);
		unsigned int getMinLevel() const { return _minLevel; }
		unsigned int getMaxLevel() const { return _maxLevel; }

		virtual void setEnable(bool enable) = 0;
		virtual bool getEnable() = 0;

		virtual bool initialize(ProgressBase* base=NULL) = 0;
		virtual bool unInitialize(ProgressBase* base=NULL) = 0;

		bool bValid() const { return _valid; }

		const SpatialProperty* getSP() const;

		void setParentTerrain(Terrain* terrain) { _parentTerrain=terrain; }
		Terrain* getParentTerrain() { return _parentTerrain; }

		//是否是全球的
		bool isGlobe();

	public:

		virtual void read(const Config& config);
		virtual void write(Config& config) const;

	protected:

		void setValid(bool valid) {_valid = valid; }
		void setSP(SpatialProperty* sp) { _sp = sp; }
		virtual ~Layer() {}

	protected:

		osg::ref_ptr<SpatialProperty> _sp;
		bool _valid;
		unsigned int _minLevel;
		unsigned int _maxLevel;
		osg::ref_ptr<DataSource> _datasource;
		unsigned int _uid;

		std::string _layerName;

		Terrain* _parentTerrain;

	};
}
#endif //OWSCENE_LAYER_H_