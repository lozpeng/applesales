#ifndef _IARCHIVE_H
#define _IARCHIVE_H

#include <string>
#include <comutil.h>	

namespace SYSTEM{


class SYSTEM_DLL IArchive {
public:
	IArchive();

   /**
    * 判断是否是读操作
	* @return 若是读操作则返回true，否则返回true 
	*/
	bool IsRead();

   /**
    * 判断是否保存
	* @return 若保存则返回true，否则返回false
	*/
	bool IsSave();

   /**
    * 设置读操作的状态
	*/
	virtual void SetReadState();

   /**
    * 设置写操作的状态
	*/
	virtual void SetWriteState();
	void Archive(void *data , unsigned long sz );
	virtual IArchive& operator &(unsigned long &val);
	virtual IArchive& operator &(unsigned short &val);
	virtual IArchive& operator &(long &val);
	virtual IArchive& operator &(int &val);
	virtual IArchive& operator &(float &val);
	virtual IArchive& operator &(double &val);
	virtual IArchive& operator &(bool &val);
	virtual IArchive& operator &(char &val);
	virtual IArchive& operator &(unsigned char &val);
	virtual IArchive& operator &(std::string &val);
	virtual IArchive& operator &(wchar_t &val);

   /**
    * 读取任意类型的数据
	* @param Data 任意类型的数据
	* @param len 数据长度
	*/
	virtual void Read(void *Data,long len) = 0;

   /**
    * 写任意类型的数据
	* @param Data 任意类型的数据
	* @param len 数据长度
	*/
	virtual void Write(void *Data,long len) = 0;

   /**
    * 获得当前位置
	* @return 返回当前位置
	*/
	virtual unsigned long& GetCurrentPos() = 0;

   /**
    * 设置起始位置为当前位置
	*/
	virtual void SetPosToBegin() = 0;

   /**
    * 判读当前位置是否到了流末尾位置
	* @return 若已经到了流末尾位置则返回true，否则返回false
	*/
	virtual bool IsEOF() = 0;

	static void ExportToBinString(void *Data, long DataSize, char *Buffer);

	static bool ImportFromBinString(const char *BinString, void *outData, unsigned long DataSize);

protected:
	bool bRead;
};

/**
 *CBinArchive---二进制流
 */

class SYSTEM_DLL CBinArchive : public IArchive
{
public:
    // 读取
	CBinArchive(void* BinSource,unsigned long Size,bool bRef = true);

    // 保存
	CBinArchive(unsigned long InitalSize = 0);

    ~CBinArchive();

	/**
	* 设置读操作的状态
	*/
	virtual void SetReadState();
	
	/**
	* 设置写操作的状态
	*/
	virtual void SetWriteState();
	
	/**
	* 读取任意类型的数据
	* @param Data 任意类型的数据
	* @param len 数据长度
	*/
	virtual void Read(void *Data, long len);
	
	/**
	* 写任意类型的数据
	* @param Data 任意类型的数据
	* @param len 数据长度
	*/
	virtual void Write(void *Data, long len);

   /**
    * 获取数据
	* @return 返回任意类型的数据
	*/
	void* GetData();

   /**
    * 把流的内容提供给外界，以一个变量的形式返回
	* @return 
	*/
	_variant_t ExportToVariant();

	// 函数名称   : ImportVariant(const _variant_t& vt)
	// 描述       : 将变量的值写到流里面
	// 返回类型   : void 
	// 参数        : const _variant_t& vt
	void ImportVariant(const _variant_t& vt);

	// 函数名称   : GetSize()
	// 描述       : 获取数据个数
	// 返回类型   : unsigned long 
	unsigned long GetSize();

   /**
    * 获得当前位置
	* @return 返回当前位置
	*/
	virtual unsigned long& GetCurrentPos();

   /**
	* 设置起始位置为当前位置
	*/
	virtual void SetPosToBegin();

   /**
    * 判读当前位置是否到了流末尾位置
	* @return 若已经到了流末尾位置则返回true，否则返回false
	*/
	virtual bool IsEOF();
protected:
    bool m_bRef;
	unsigned char *m_Data;
	unsigned long m_Pos,m_Size;
};

/**
 *CStringArchive---字符流
 */

class SYSTEM_DLL CStringArchive : public SYSTEM::CBinArchive
{
public:
    // 读取
	CStringArchive(void* StringSource,unsigned long Size,bool bRef = true);

    // 保存
	CStringArchive(unsigned long InitalSize = 0);

    ~CStringArchive();

	virtual IArchive& operator &(unsigned long &val);
	virtual IArchive& operator &(unsigned short &val);
	virtual IArchive& operator &(long &val);
	virtual IArchive& operator &(int &val);
	virtual IArchive& operator &(float &val);
	virtual IArchive& operator &(double &val);
	virtual IArchive& operator &(bool &val);
	virtual IArchive& operator &(char &val);
	virtual IArchive& operator &(unsigned char &val);
	virtual IArchive& operator &(std::string &val);

	// 函数名称   : ExportToVariant()
	// 描述       : 把流的内容提供给外界，以一个变量的形式返回
	// 返回类型   : _variant_t 
	_variant_t ExportToVariant();

   /**
    * 读取任意类型的数据
	* @param Data 任意类型的数据
	* @param len 数据长度
	*/
	virtual void Read(void *Data,long len);

	/**
	* 写任意类型的数据
	* @param Data 任意类型的数据
	* @param len 数据长度
	*/
	virtual void Write(void *Data,long len);

protected:
	void ReadStr(char *Data);
	void WriteStr(char *Data);

};

}


#endif //IARCHIVE_H
