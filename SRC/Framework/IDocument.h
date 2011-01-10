//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  champion
// ʱ�䣺  2010.12
// ������  �ĵ�������࣬���ڹ����ͼ����
//////////////////////////////////////////////////////////////////////
#ifndef _IDOCUMENT_H
#define _IDOCUMENT_H

#include "IUIObject.h"
#include "Map.h"
#include "IDisplay.h"
#include "PageLayout.h"
#include "IMaptreeCtrl.h"

namespace Framework
{

class IMapCtrl;
class ILayoutCtrl;

class FRAMEWORK_DLL IDocument : public IUIObject
{
public:
	IDocument();
	virtual ~IDocument();

public:

	//�õ���ͼ����
	long GetMapCount() const;

	//���û��ͼ
	virtual void SetActiveMap(Carto::CMapPtr pMap);

	//�õ����ͼ
	virtual Carto::CMapPtr GetActiveMap();

	//����µĵ�ͼ
	virtual long AddNewMap();

	virtual void AddMap(Carto::CMapPtr pMap);

	// ɾ����ͼ
	virtual void DeleteMap(long index);


	//ͨ��ID�ŵõ���ͼ����
	Carto::CMapPtr GetMap(long index);

	//����դ���ļ�
    void LoadImageFile(const char *file);

	//����shp�ļ�
	void LoadShpFile(const char *file);


	void SetLinkMapCtrl(IMapCtrl *pMapCtrl);

	IMapCtrl *GetLinkMapCtrl();

	//���layout
	
	void SetLinkLayoutCtrl(ILayoutCtrl *pLayoutCtrl);
	ILayoutCtrl *GetLinkLayoutCtrl();

	//���ù�����TOC�ؼ�
	void SetLinkMapTree(IMaptreeCtrl* pMapTree);
	IMaptreeCtrl *GetLinkMapTree();

protected:
    
	std::vector<Carto::CMapPtr> m_pMaps;

	//�ĵ������ĵ�ͼ�ؼ�
    IMapCtrl *m_linkMapCtrl;

    Carto::CMapPtr m_pActiveMap;

	int m_index;


	//pagelayout
	ILayoutCtrl * m_linkLayoutCtrl;

	IMaptreeCtrl *m_pLinkMapTree;

};

}
#endif