//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  leo
// ʱ�䣺  2010.12
// ������  ����������
//////////////////////////////////////////////////////////////////////

#ifndef _IUIObject_h
#define _IUIObject_h

#include <map>

namespace Framework
{

//���������ע��ʱʹ�õ�����
class FRAMEWORK_DLL CommonUIName
{
public:
	//������ĵ�ͼ�ؼ�
	static std::string AppMapControl;

	// �������ĵ�
	static std::string AppDocument;
};

class FRAMEWORK_DLL IUIObject : public SYSTEM::ISerialization
{

public : 
	IUIObject();
	virtual ~IUIObject();

	/**
	* ���л�
	* @param ar �ĵ���
	*/
	virtual void serialization(SYSTEM::IArchive &ar);

	/**
	* �������
	*/
	std::string GetName();

	//
	bool GetAutoDestroy() {return m_bAutoDestroy;}
	void SetAutoDetroy(bool bAutoDestroy) { m_bAutoDestroy = bAutoDestroy;}
public:

	/**
	* ͨ�����ƻ���û��������
	* @param Name �ؼ�����
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static IUIObject* GetUIObjectByName(std::string Name);

	/**
	* ��õ�һ���û��������
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static IUIObject* GetFirstObject();

	/**
	* �����һ���û��������
	* @return �������򷵻ظö���ָ�룬���򷵻�ΪNULL
	*/
	static IUIObject* GetNextObject();



protected:

	/**< ������������*/
	virtual void CreateAss(std::string Name);

	/**< ɾ����������*/
	virtual void DestroyAss();

	//oject name
	std::string m_Name;

	//is AutoDestroy
	bool m_bAutoDestroy;

};

}
#endif