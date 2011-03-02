#ifndef _ACTION_EDIT_FEATURE_H_
#define _ACTION_EDIT_FEATURE_H_

#include "IAction.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

class  EDITOR_DLL CActionEditFeature : public otFramework::IAction
{
public:
	CActionEditFeature();
	~CActionEditFeature();
public:

	enum Status 
	{
		On_None,
		On_Selection,
		On_ShapeMove,
		On_Vertex,    //����ڽڵ���
		On_Line,      //���������
		On_VertexMove,  //�ڵ��ƶ�
		On_SelectMoreShape, //ѡ���˶��ͼ��
		On_MoveMoreShape   //�ƶ����ͼ��
	};
public:
	void Triger();
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

	void LButtonDblClkEvent (UINT nFlags, CPoint point);

	void RButtonDownEvent (UINT nFlags, CPoint point);

	//����ڵ�
	void InsertVertex();
	//ɾ���ڵ�
	void DelVertex();
	//�ƶ��ڵ�
	void MoveVertex();
	//��ʾ����
	void ShowAttribute();

private:
	void ClearMoveGeometrys();

	//��ȡ�༭ͼ����ѡ�е�ͼ��
	BOOL GetSelectGeometrys();

	BOOL InstanceEditObject();

	//�����ƶ���ͼ��
	void DrawMovedGeometrys();

private:
	//�ϴ�Ҫ���ƶ�ʱ�ĵ�
	CPoint m_lastmovePt;

	//���
	double m_dTolerance;

	long   m_curPart;

	long   m_curVertexIndex;
	bool   m_bMoved;

	bool   m_bContain;

	//��ǰ�ڵ������
	TT_GEOMETRY::geom::Coordinate m_curVertex;

	//��ǰ�����ϵĵ�
	TT_GEOMETRY::geom::Coordinate m_insertPt;

	//�ƶ���ͼ������
	std::vector<TT_GEOMETRY::geom::Geometry*> m_moveGeometrys;

	std::vector<long> m_shpIds;
	std::vector<otCarto::ILayer*> m_layers;
};

}


#endif