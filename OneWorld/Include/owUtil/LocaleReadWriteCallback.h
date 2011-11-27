#ifndef _owUtil_LOCALE_READWRITECALLBACK_H
#define _owUtil_LOCALE_READWRITECALLBACK_H

#include <osgDB/Registry>

namespace owUtil
{

	class ReadChsFileCallBack : public osgDB::Registry::ReadFileCallback
	{
	public:
		virtual osgDB::ReaderWriter::ReadResult openArchive(const std::string& filename,osgDB::ReaderWriter::ArchiveStatus status, unsigned int indexBlockSizeHint, const osgDB::ReaderWriter::Options* useObjectCache)
		{
			setlocale(LC_ALL,"chs");
			if(filename.empty())
				return osgDB::ReaderWriter::ReadResult::FILE_NOT_FOUND;
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::ReadFileCallback::openArchive(filename,status,indexBlockSizeHint,useObjectCache);
			setlocale(LC_ALL,"C");
			return rr;
		}

		virtual osgDB::ReaderWriter::ReadResult readObject(const std::string& filename, const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			if(filename.empty())
				return osgDB::ReaderWriter::ReadResult::FILE_NOT_FOUND;
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::ReadFileCallback::readObject(filename, options);
			setlocale(LC_ALL,"C");
			return rr;
		}

		virtual osgDB::ReaderWriter::ReadResult readImage(const std::string& filename, const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			//std::cout<<"read image from "<<filename<<std::endl;
			if(filename.empty())
				return osgDB::ReaderWriter::ReadResult::FILE_NOT_FOUND;
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::ReadFileCallback::readImage(filename,options);
			//if(rr.success())
			//	std::cout<<"read image from "<<filename<<"success"<<std::endl;
			//else
			//	std::cout<<"read image from "<<filename<<"failed"<<std::endl;
			setlocale(LC_ALL,"C");
			return rr;
		}

		virtual osgDB::ReaderWriter::ReadResult readHeightField(const std::string& filename, const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			if(filename.empty())
				return osgDB::ReaderWriter::ReadResult::FILE_NOT_FOUND;
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::ReadFileCallback::readHeightField(filename,options);
			setlocale(LC_ALL,"C");
			return rr;
		}

		virtual osgDB::ReaderWriter::ReadResult readNode(const std::string& filename, const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			if(filename.empty())
				return osgDB::ReaderWriter::ReadResult::FILE_NOT_FOUND;
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::ReadFileCallback::readNode(filename, options);
			setlocale(LC_ALL,"C");
			return rr;
		}

		virtual osgDB::ReaderWriter::ReadResult readShader(const std::string& filename, const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			if(filename.empty())
				return osgDB::ReaderWriter::ReadResult::FILE_NOT_FOUND;
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::ReadFileCallback::readShader(filename,options);
			setlocale(LC_ALL,"C");
			return rr;
		}

	protected:
		virtual ~ReadChsFileCallBack() {}

	};

	class WriteChsFileCallback : public osgDB::Registry::WriteFileCallback
	{
	public:
		virtual osgDB::ReaderWriter::WriteResult writeObject(const osg::Object& obj, const std::string& fileName,const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			osgDB::ReaderWriter::WriteResult wr = osgDB::Registry::WriteFileCallback::writeObject(obj,fileName,options);
			setlocale(LC_ALL,"C");
			return wr;
		}

		virtual osgDB::ReaderWriter::WriteResult writeImage(const osg::Image& obj, const std::string& fileName,const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			osgDB::ReaderWriter::WriteResult wr = osgDB::Registry::WriteFileCallback::writeImage(obj,fileName,options);
			setlocale(LC_ALL,"C");
			return wr;
		}

		virtual osgDB::ReaderWriter::WriteResult writeHeightField(const osg::HeightField& obj, const std::string& fileName,const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			osgDB::ReaderWriter::WriteResult wr = osgDB::Registry::WriteFileCallback::writeHeightField(obj,fileName,options);
			setlocale(LC_ALL,"C");
			return wr;
		}

		virtual osgDB::ReaderWriter::WriteResult writeNode(const osg::Node& obj, const std::string& fileName,const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			osgDB::ReaderWriter::WriteResult wr = osgDB::Registry::WriteFileCallback::writeNode(obj,fileName,options);
			setlocale(LC_ALL,"C");
			return wr;
		}

		virtual osgDB::ReaderWriter::WriteResult writeShader(const osg::Shader& obj, const std::string& fileName,const osgDB::ReaderWriter::Options* options)
		{
			setlocale(LC_ALL,"chs");
			osgDB::ReaderWriter::WriteResult wr = osgDB::Registry::WriteFileCallback::writeShader(obj,fileName,options);
			setlocale(LC_ALL,"C");
			return wr;
		}

	protected:
		virtual ~WriteChsFileCallback() {}

	};

}

#endif