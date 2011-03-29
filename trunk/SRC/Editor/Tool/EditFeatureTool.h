#ifndef _EDIT_FEATURE_TOOL_H_
#define _EDIT_FEATURE_TOOL_H_

#include "ITool.h"
#include <geometry/geom/Geometry.h>
#include "ILayer.h"
namespace Editor
{

	class   CEditFeatureTool : public Framework::ITool
	{
	public:
		CEditFeatureTool();
		~CEditFeatureTool();
	public:

		enum Status 
		{
			On_None,
			On_Selection,
			On_ShapeMove,
			On_Inside,
			On_Vertex,    //����ڽڵ���
			On_Line,      //���������
			On_VertexMove,  //�ڵ��ƶ�
			On_SelectMoreShape, //ѡ���˶��ͼ��
			On_MoveMoreShape   //�ƶ����ͼ��
		};
	public:
		//��ʼ��

		void Initialize(Framework::IUIObject *pTargetControl);
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

	
		void ClearMoveGeometrys();
private:
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
		GEOMETRY::geom::Coordinate m_curVertex;

		//��ǰ�����ϵĵ�
		GEOMETRY::geom::Coordinate m_insertPt;

		//�ƶ���ͼ������
		std::vector<GEOMETRY::geom::Geometry*> m_moveGeometrys;

		Status m_nStatus;
		HCURSOR cursorOnVertix ;
		HCURSOR cursorOnLine ;
		HCURSOR cursorModifyShape ;
		HCURSOR cursorSizeAll ;

		std::vector<long> m_shpIds;
		std::vector<Carto::ILayer*> m_layers;
	};

}


#endif