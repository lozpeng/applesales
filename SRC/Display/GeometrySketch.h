#ifndef _GEOMETRY_SKETCH_H
#define _GEOMETRY_SKETCH_H

#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace Display
{
/*********************************************************************
*������������һ������ͼ�Σ����Զ�̬����ӵ㣬���ҿ��Խ�ͼ�λ��Ƶ�Display
* ͨ����ʸ���༭������Ҫ��ʱ����һ��ͼ��ʱʹ�� 
*
*********************************************************************/
class DISPLAY_DLL CGeometrySketch
{
public:

	CGeometrySketch(int GeometryType,bool bhasZ =false,bool bhasM=false);

	virtual ~CGeometrySketch(void);

public:
	GEOMETRY::geom::Geometry* GetGeometry() const {return m_pGeometry;}

	void Draw(IDisplayPtr pDisplay);

	//�滻����ǰͼ��,�����»�����Ϣ
	void ReplaceGeometry(GEOMETRY::geom::Geometry* pGeometry,long &curPart,bool &bpartFinish);


	int GetGeometryType() const;

	bool IsMultiPart() const;

	int GetCurPartIndex() const {return m_icurPart;}

	void FinishPart();

	void AddPoint(GEOMETRY::geom::Coordinate &coord);

	//�����ʶ�����գ�һ���ڽ�����ǰͼ�ε�����µ���
	void SetEmpty();

	bool IsEmpty() const;

	bool  IsRightGeometry() const;

	bool  IsCurPartFinish() const{return m_bCurPartFinish;}

	GEOMETRY::geom::Coordinate GetlastPoint() const;

	//�õ���ǰPart�ĵ�һ����
	GEOMETRY::geom::Coordinate GetCurPartFirstPt() const;

	void MouseMove(GEOMETRY::geom::Coordinate &coord);

private:
	void InitSymbol();
public:
	GEOMETRY::geom::Geometry *m_pGeometry;

	//��ǰ���������
	GEOMETRY::geom::Coordinate m_MousePt;

	//��ǰ������ţ�����Ρ���㡢���ߡ�����������ж��Part���
	int m_icurPart;

	bool        m_bCurPartFinish;

	bool        m_bMultiPart;

	//����Ƿ��ƶ�
	bool        m_bMouseMove;

	ISymbolPtr  m_ptSymbol;
	ISymbolPtr  m_lineSymbol;
};

typedef SYSTEM::CSmartPtr<CGeometrySketch> CGeometrySketchPtr;

}

#endif