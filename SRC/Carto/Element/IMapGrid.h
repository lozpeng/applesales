//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  ��ͼҪ�ء�����ͼ����  ���������Ļ���
//////////////////////////////////////////////////////////////////////

#ifndef IMAP_GRID_H
#define IMAP_GRID_H

#include "IGrid.h"

namespace Element{

class CMapFrame;
class CARTO_DLL IMapGrid :public IGrid
{
public:
	IMapGrid();
	IMapGrid(CMapFrame* pMapFrame);
	~IMapGrid(void);

	virtual void serialization(SYSTEM::IArchive &ar)=0;  


	CMapFrame* GetMapFrame();
	void SetMapFrame(CMapFrame* mapFrame);

protected:
	CMapFrame* m_pMapFrame;

};

typedef SYSTEM::CSmartPtr<IMapGrid> IMapGridPtr;
}
#endif
