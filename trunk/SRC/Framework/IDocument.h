//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  champion
// 时间：  2010.12
// 描述：  文档管理基类，用于管理地图数据
//////////////////////////////////////////////////////////////////////
#ifndef _IDOCUMENT_H
#define _IDOCUMENT_H

#include "IUIObject.h"
#include "Map.h"
#include "IDisplay.h"


namespace Framework
{

class IMapCtrl;

class FRAMEWORK_DLL IDocument : public IUIObject
{
public:
	IDocument();
	virtual ~IDocument();

public:

	//得到地图数量
	long GetMapCount() const;

	//设置活动地图
	virtual void SetActiveMap(Carto::CMapPtr pMap);

	//得到活动地图
	virtual Carto::CMapPtr GetActiveMap();

	//添加新的地图
	virtual long AddNewMap();

	virtual void AddMap(Carto::CMapPtr pMap);

	// 删除地图
	virtual void DeleteMap(long index);


	//通过ID号得到地图对象
	Carto::CMapPtr GetMap(long index);

	void SetLinkMapCtrl(IMapCtrl *pMapCtrl);

	IMapCtrl *GetLinkMapCtrl();

protected:
    
	std::vector<Carto::CMapPtr> m_pMaps;

	//文档关联的地图控件
    IMapCtrl *m_linkMapCtrl;

    Carto::CMapPtr m_pActiveMap;

	int m_index;





};

}
#endif