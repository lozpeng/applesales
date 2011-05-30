#ifndef _IEXTEND_DRAW_H
#define _IEXTEND_DRAW_H

#include "IDisplay.h"

namespace Carto
{

//��չ�������ݵĽӿ�
class CARTO_DLL IOtherDraw
{
public:
	IOtherDraw();
	virtual ~IOtherDraw();

public:

	/**
	* ����
	* @param pDisplay ���ƵĻ���
	*/
	virtual void Draw(Display::IDisplayPtr pDisplay) =0;

	/**
	* �õ��������ݵ�����
	*/
	std::string GetName();

	/**
	* ���û������ݵ�����
	*/
	void SetName(const char *strName);

protected:
	std::string m_name;

};


}


#endif