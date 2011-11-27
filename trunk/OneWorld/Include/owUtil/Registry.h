#ifndef owUtil_REGISTRY_H_
#define owUtil_REGISTRY_H_

#include <owUtil/export.h>
#include <owUtil/Registry.h>
#include <osg/Referenced>
#include <osgDB/ReaderWriter>
#include <OpenThreads/ScopedLock>
#include <OpenThreads/ReentrantMutex>


#define GDAL_SCOPED_LOCK \
	OpenThreads::ScopedLock<OpenThreads::ReentrantMutex> _slock( owUtil::Registry::instance().getGDALMutex() )\

namespace owUtil
{
	class OWUTIL_EXPORT Registry : public osg::Referenced
	{
	public:

		/** 单件类*/
		static Registry& instance();

		/** 针对gdal安全的全局线程安全锁*/
		OpenThreads::ReentrantMutex& getGDALMutex() { return _gdal_mutex; }

        /** Registers a mapping of a mime-type to an extension. A process fetching data
          * over HTTP can use this facility to determine the proper ReaderWriter to use
          * when there is no filename extension to rely upon.
          */
        void addMimeTypeExtensionMapping(const std::string fromMimeType, const std::string toExt);

        /** gets a reader/writer that handles the extension mapped to by one of
          * the registered mime-types. */
        osgDB::ReaderWriter* getReaderWriterForMimeType(const std::string& mimeType);


	protected:

	protected:

		Registry();
		~Registry();

	protected:

		OpenThreads::ReentrantMutex _gdal_mutex;

		typedef std::map< std::string, std::string> MimeTypeExtensionMap;
		// maps mime-types to extensions.
		MimeTypeExtensionMap _mimeTypeExtMap;

	};
}
#endif //owUtil_REGISTRY_H_