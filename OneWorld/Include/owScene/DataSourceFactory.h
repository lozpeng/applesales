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

		/** ����Դ�����������ʱ����Ҫ��ȡ��������Դ��Ȼ�󱣴浽����Դ������
		 * �ڲ���ʹ�õ�����Դ������������Դ��������(Config)�����ü�������Դ����
		 * ��Դ�����е����ơ�ע�⣺�˴���name�����ظ�*/
		void registryDataSource(const std::string& name,DataSource* source);
		void unregistryDataSource(const std::string& name);
		DataSource* getRegistryDataSource(const std::string& name);


		/** ���ݸ�����������ʸ������Դ������ü�����Ӧ���*/
		FeatureSource* createFeatureSource(const Config& config);

		/** ���ݸ�����������������Դ������ü�����Ӧ���*/
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