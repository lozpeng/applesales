#include "stdafx.h"
#include "RelativePath.h"
#include <boost/tokenizer.hpp>
#include <vector>

namespace SYSTEM{

std::string CRelativePath::BasePath;

typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;

void CRelativePath::SetBasePath(const char* strPath)
{
	BasePath =strPath;
}

bool CRelativePath::IsRelativePath(const char* path)
{
	std::string strPath =path;
	if(strPath.empty())
	{
		return false;
	}
	if(strPath.size()>=2)
	{
		if(strPath[1]==':')
		{
			return false;
		}
	}
	return true;
}

std::string CRelativePath::RelativePath(const char* destpath)
{
	std::string strBase =BasePath;
	std::string strDest =destpath;

	std::string RelPath;
	

	boost::char_separator<char> sep("/\\");

	Tokenizer tok(strBase,sep);

	//将基本路径和目标路径分解
	std::vector<std::string> baseArry,destArry;

	for(Tokenizer::iterator iter =tok.begin();iter!=tok.end();iter++)
	{
		baseArry.push_back(*iter);
	}

	tok.assign(strDest,sep);

	for(Tokenizer::iterator iter =tok.begin();iter!=tok.end();iter++)
	{
		destArry.push_back(*iter);
	}

	//判断基础路径和目标路径的盘符是否相同，如果不同，则返回绝对路径
	if(stricmp(baseArry[0].c_str(),destArry[0].c_str())!=0)
	{
		return strDest;
	}

	int nLevel =(baseArry.size()<destArry.size())?baseArry.size():destArry.size();

	int i =0;
	for(i=0;i<nLevel;i++)
	{
		if(stricmp(baseArry[i].c_str(),destArry[i].c_str())!=0)
		{
			break;
		}

	}

	int breakLevel =i;
	for(;i<baseArry.size();i++)
	{
		RelPath+="..\\";
	}
	for(i=breakLevel;i<destArry.size();i++)
	{
		RelPath+=destArry[i];
		if(i!=destArry.size()-1)
		{
			RelPath+="\\";
		}
	}
	return RelPath;
}

std::string CRelativePath::FullPath(const char *relpath)
{
	std::string strRel =relpath;
	std::string fullpath;

	boost::char_separator<char> sep("/\\");
	Tokenizer tok(BasePath,sep);

	//将基本路径分解
	std::vector<std::string> baseArry,relArray;

	for(Tokenizer::iterator iter =tok.begin();iter!=tok.end();iter++)
	{
		baseArry.push_back(*iter);
	}
    
	tok.assign(strRel,sep);
	//将相对路径分解
	for(Tokenizer::iterator iter =tok.begin();iter!=tok.end();iter++)
	{
		relArray.push_back(*iter);
	}

	int frontCount =0;

	int i=0;
	for(i=0;i<relArray.size();i++)
	{
		if(relArray[i]!="..")
		{
			break;
		}
	}

	frontCount =i;

	for(i=0;i<baseArry.size()-frontCount;i++)
	{
		fullpath+=baseArry[i];
		fullpath+="\\";
	}

	for(i=frontCount;i<relArray.size();i++)
	{
		fullpath+=relArray[i];
		if(i!=relArray.size()-1)
		{
			fullpath+="\\";
		}
	}

	return fullpath;



}

}//namespace otSystem