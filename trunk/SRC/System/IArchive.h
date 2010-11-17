#ifndef _IARCHIVE_H
#define _IARCHIVE_H

#include <string>
#include <comutil.h>	

namespace SYSTEM{


class SYSTEM_DLL IArchive {
public:
	IArchive();

   /**
    * �ж��Ƿ��Ƕ�����
	* @return ���Ƕ������򷵻�true�����򷵻�true 
	*/
	bool IsRead();

   /**
    * �ж��Ƿ񱣴�
	* @return �������򷵻�true�����򷵻�false
	*/
	bool IsSave();

   /**
    * ���ö�������״̬
	*/
	virtual void SetReadState();

   /**
    * ����д������״̬
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
    * ��ȡ�������͵�����
	* @param Data �������͵�����
	* @param len ���ݳ���
	*/
	virtual void Read(void *Data,long len) = 0;

   /**
    * д�������͵�����
	* @param Data �������͵�����
	* @param len ���ݳ���
	*/
	virtual void Write(void *Data,long len) = 0;

   /**
    * ��õ�ǰλ��
	* @return ���ص�ǰλ��
	*/
	virtual unsigned long& GetCurrentPos() = 0;

   /**
    * ������ʼλ��Ϊ��ǰλ��
	*/
	virtual void SetPosToBegin() = 0;

   /**
    * �ж���ǰλ���Ƿ�����ĩβλ��
	* @return ���Ѿ�������ĩβλ���򷵻�true�����򷵻�false
	*/
	virtual bool IsEOF() = 0;

	static void ExportToBinString(void *Data, long DataSize, char *Buffer);

	static bool ImportFromBinString(const char *BinString, void *outData, unsigned long DataSize);

protected:
	bool bRead;
};

/**
 *CBinArchive---��������
 */

class SYSTEM_DLL CBinArchive : public IArchive
{
public:
    // ��ȡ
	CBinArchive(void* BinSource,unsigned long Size,bool bRef = true);

    // ����
	CBinArchive(unsigned long InitalSize = 0);

    ~CBinArchive();

	/**
	* ���ö�������״̬
	*/
	virtual void SetReadState();
	
	/**
	* ����д������״̬
	*/
	virtual void SetWriteState();
	
	/**
	* ��ȡ�������͵�����
	* @param Data �������͵�����
	* @param len ���ݳ���
	*/
	virtual void Read(void *Data, long len);
	
	/**
	* д�������͵�����
	* @param Data �������͵�����
	* @param len ���ݳ���
	*/
	virtual void Write(void *Data, long len);

   /**
    * ��ȡ����
	* @return �����������͵�����
	*/
	void* GetData();

   /**
    * �����������ṩ����磬��һ����������ʽ����
	* @return 
	*/
	_variant_t ExportToVariant();

	// ��������   : ImportVariant(const _variant_t& vt)
	// ����       : ��������ֵд��������
	// ��������   : void 
	// ����        : const _variant_t& vt
	void ImportVariant(const _variant_t& vt);

	// ��������   : GetSize()
	// ����       : ��ȡ���ݸ���
	// ��������   : unsigned long 
	unsigned long GetSize();

   /**
    * ��õ�ǰλ��
	* @return ���ص�ǰλ��
	*/
	virtual unsigned long& GetCurrentPos();

   /**
	* ������ʼλ��Ϊ��ǰλ��
	*/
	virtual void SetPosToBegin();

   /**
    * �ж���ǰλ���Ƿ�����ĩβλ��
	* @return ���Ѿ�������ĩβλ���򷵻�true�����򷵻�false
	*/
	virtual bool IsEOF();
protected:
    bool m_bRef;
	unsigned char *m_Data;
	unsigned long m_Pos,m_Size;
};

/**
 *CStringArchive---�ַ���
 */

class SYSTEM_DLL CStringArchive : public SYSTEM::CBinArchive
{
public:
    // ��ȡ
	CStringArchive(void* StringSource,unsigned long Size,bool bRef = true);

    // ����
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

	// ��������   : ExportToVariant()
	// ����       : �����������ṩ����磬��һ����������ʽ����
	// ��������   : _variant_t 
	_variant_t ExportToVariant();

   /**
    * ��ȡ�������͵�����
	* @param Data �������͵�����
	* @param len ���ݳ���
	*/
	virtual void Read(void *Data,long len);

	/**
	* д�������͵�����
	* @param Data �������͵�����
	* @param len ���ݳ���
	*/
	virtual void Write(void *Data,long len);

protected:
	void ReadStr(char *Data);
	void WriteStr(char *Data);

};

}


#endif //IARCHIVE_H
