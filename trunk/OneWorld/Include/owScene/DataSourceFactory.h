#ifndef OWSCENE_DATASOURCEFACTORY_H_
#define OWSCENE_DATASOURCEFACTORY_H_

#include <owScene/export.h>
#include <owScene/RasterSource.h>
#include <owScene/FeatureSource.h>
#include <osg/Referenced>
#include <OpenThreads/Mutex>

using namespace owUtil;
using namespace owScene;

namespace owScene
{
	class OWSCENE_EXPORT DataSourceFactory : public osg::Referenced
	{
	public:
		static DataSourceFactory& Instance();

		/** 数据源管理，程序加载时首先要读取所有数据源，然后保存到数据源工厂中
		 * 在层中使用的数据源将不记载数据源的配置项(Config)，采用记载数据源在数
		 * 据源管理中的名称。注意：此处的name不能重复*/
		void registryDataSource(const std::string& name,DataSource* source);
		void unregistryDataSource(const std::string& name);
		DataSource* getRegistryDataSource(const std::string& name);


		/** 根据给定参数创建矢量数据源，会调用加载相应插件*/
		FeatureSource* createFeatureSource(const Config& config);

		/** 根据给定参数创建块数据源，会调用加载相应插件*/
		RasterSource* createRasterSource(const Config& config);

	protected:

		DataSourceFactory();
		~DataSourceFactory();

	private:

		typedef std::map<std::string,osg::ref_ptr<DataSource>> mapDataSource;
		mapDataSource _datasources;
	};
}

#endif //OWSCENE_DATASOURCEFACTORY_H_