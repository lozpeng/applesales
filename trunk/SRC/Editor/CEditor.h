#ifndef  _EDITOR_H_
#define  _EDITOR_H_

#include "IEditor.h"
#include "GeometrySketch.h"
//#include "Shape.hxx"
#include "ILayer.h"
#include "Map.h"
#include "Feature.h"
#include <vector>
#include "SmartPtr.h"
using namespace std;

namespace Editor
{

	class IEditTask;

	class CSnapAgent;

	typedef struct st_Circle
	{
		std::vector<Carto::ILayer*> layers;

	}STCircle;

	//�ڴ���Geometry���˵Ľṹ�壬�����һЩ��Ҫ��Ϣ
	struct STMemUndoCycle
	{
		~STMemUndoCycle() {delete pGeometry;}

		GEOMETRY::geom::Geometry* pGeometry;

		long lcurPart; //��ǰ��Geometry��һ����
		bool bcurPartFinish; //��ǰ�����Ƿ����


	};

	class EDITOR_DLL CEditor : public Carto::IEditor
	{
	public:

		CEditor(Carto::CMap *pMap);

		virtual ~CEditor();
	public:

		/**
		* ��ʼ�༭
		*/
		void StartEdit();

		/**
		* �����༭
		* @param bSave �Ƿ񱣴��޸�
		*/
		void StopEdit(bool bSave);

		/**
		* ����༭
		*/
		void SaveEdit();

		/**
		* �Ƿ��ڱ༭
		*/
		bool IsEditing();

		/**
		* ��������
		*/
		void Undo();

		/**
		* ��������
		*/
		void Redo();

		/**
		* �Ƿ���Գ���
		*/
		bool CanUndo();

		/**
		* �Ƿ��������
		*/
		bool CanRedo();

		/**
		* ���Ʊ༭���������ڴ�����ͼ�Σ��༭��ͼ�ε�
		*/
		void DrawEdit(Display::IDisplayPtr pDisplay);
	public:

		/**
		* ɾ��Ҫ��
		*/
		void DeleteFeature();

		/**
		* ����Ҫ��
		*/
		void CopyFeature();

		/**
		* ճ��Ҫ��
		*/
		void PasteFeature();

		/**
		* ����Ҫ��
		*/
		void CutFeature();

		/**
		* ��ͼ�μ��뵽��ǰͼ����
		*/
		void AppendGeometry(GEOMETRY::geom::Geometry *pGeometry);


		/**
		* ��ʾ�༭���ԶԻ���
		*/
		void EditAttribute();

		/**
		* �õ��༭��ͼ������
		*/
		void GetEditLayers(std::vector<Carto::ILayer*> &layers);

		/**
		* ������Ҫ�༭��ͼ��
		*/
		bool SearchEditGeometry();

		/**
		* �ύ�༭�ռ�༭��ͼ��
		*/
		void CommitModifyShape();

		/**
		* �ύҪ�޸ĵ�Ҫ��,�����ӹ�Geometryָ��Ŀ���
		*/
		void CommitModifyShapes(std::vector<GEOMETRY::geom::Geometry*> &vecShp,std::vector<long> &vecShapeId, std::vector<Carto::ILayer*> &vecLayers);

		void DrawEditShape(Display::IDisplayPtr &pDisplay,GEOMETRY::geom::Geometry* pGeometry);

	public:

		/****************************************************************************************
		*������صĺ���
		*****************************************************************************************/

		/**
		* ������������ͼ����뵽�����б�
		*/
		void AddToCircle(std::vector<Carto::ILayer*> &layers);

		/**
		* �ڵ����
		*/
		void VertexUndo();
		/**
		* �ڵ�����
		*/
		void VertexRedo();

		bool VertexCanUndo();
		bool VertexCanRedo();

		//��Geometryѹ��ع���ջ
		void PushGeometry2Undo(GEOMETRY::geom::Geometry* pGeometry,long lcurPart=0,bool bpartFinish=false);

		//��սڵ�ع���ջ
		void ClearMemUndo();

		/****************************************************************************************
		*������صĺ���
		*****************************************************************************************/

		void CreateEditSketch(Carto::ILayer *pLayer);

		//��ӻ����еĵ�
		void AddSketchPoint(GEOMETRY::geom::Coordinate &point,double dz =0.0,double dm =0.0);

		//��������
		void FinishSketch();
		//���������е�һ����
		void FinishSketchPart();

		void SetSketchEmpty();

		GEOMETRY::geom::Geometry* GetSketchGeometry() const;


		void SetMousePt(GEOMETRY::geom::Coordinate &pt){m_curMousePt =pt; }

		void SetbSketch(bool bSketch){m_bSketch =bSketch;};

		void SetbEditFeature(bool b){m_bEditFeature =b;};

		void SetbEditVertex(bool b) {m_bInVertexEdit =b;}

		/****************************************************************************************
		*����Ϊ��׽��صĺ���
		*****************************************************************************************/

		/**
		* ��׽
		* @param inPoint  ����ĵ�
		* @param outPoint ��׽���ĵ� 
		*/
		void Snap(GEOMETRY::geom::Coordinate inPoint,GEOMETRY::geom::Coordinate &outPoint);

		//���úͻ�ȡ��׽����
		double GetSnapTolerance();

		void  SetSnapTolerance(double d);

		void ShowSnapDlg();
		void AddSnapAgent(Carto::ILayer *pLayer,unsigned long snaptype);

		//�õ�һ��ͼ��Ĳ�׽��ʽ
		unsigned long GetLayerSnaptype(Carto::ILayer *pmapLayer);

		void RemoveSnapAgent(Carto::ILayer *pmapLayer);

		//ɾ�����в�׽��
		void RemoveAllSnapAgent();

		/****************************************************************************************
		*Ŀ��ͼ��������صĺ���
		*****************************************************************************************/

		//��õ�ǰ�༭ͼ���ѡ��
		//��õ�ǰͼ��ѡ��
		void GetCurLayerSelection(std::vector<Geometry*> &shapes, 
			std::vector<long> &shapeIds, vector<Carto::ILayer*> &players);

		//��õ�ǰͼ��
		Carto::ILayer* GetCurLayer() {return m_curLayer;};

		//�ı�༭Ŀ���
		void ChangeCurLayer(std::string layername);

		void OnTagetLayerChanged();

		/**************************************************************
		*�༭������صĺ���
		***************************************************************/

		//���õ�ǰ�༭����
		void SetEditTask(std::string &taskname);

		void DeleteAllTask();

		std::string GetCurTaskName() const;

		void OnEditTaskChanged();

		/**************************************************************
		*�Ҽ��˵����ݼ�����Ӧ����
		***************************************************************/
		void OnSketchAbsXY();

		//�����������
		void OnSketchDeltaXY();

		//���뷽λ\����
		void OnSketchDirLen();


	private:

		//��ʼ�����е�����
		void InitEditTask();

		//�༭����ʱ���ã���������
		void OnEndEdit();

		//����༭��ͼ��
		void ClearModifyGeometry();

		//������а��е�Ҫ��
		void ClearCopyFeatures();

		//���Ʊ༭��ͼ��


		void DrawEditPoints(Display::IDisplayPtr &pDisplay,GEOMETRY::geom::Geometry* pGeometry);

		void DrawEditPolyline(Display::IDisplayPtr &pDisplay,GEOMETRY::geom::Geometry* pGeometry);

		void DrawEditMultiPolyline(Display::IDisplayPtr &pDisplay,GEOMETRY::geom::Geometry* pGeometry);

		void DrawEditPolygon(Display::IDisplayPtr &pDisplay,GEOMETRY::geom::Geometry* pGeometry);

		void DrawEditPoints(Display::IDisplayPtr &pDisplay,INT_POINT *pts,long num);

		void DrawEditPolyline(Display::IDisplayPtr &pDisplay,INT_POINT *pts,long num);

		void DrawMousePoint(Display::IDisplayPtr &pDisplay);

		void DrawSnapCursor(Display::IDisplayPtr &pDisplay);

	public:
		std::vector<GEOMETRY::geom::Geometry*> m_modifyGeometrys;
		std::vector<Carto::ILayer*>      m_modifyLayers;
		std::vector<long>      m_modifyShapeId;
	private:

		//�Ƿ��ڱ༭
		bool m_bEditing;

		//�Ƿ��ڱ༭�ڵ�
		bool		m_bInVertexEdit;

		//�Ƿ��ڻ�ͼ��
		bool m_bSketch;
		//�Ƿ��ڱ༭ͼ��
		bool m_bEditFeature;

		//����
		Display::CGeometrySketchPtr m_pSketch;

		//��ǰ���Ƶ�ĵ�������
		GEOMETRY::geom::Coordinate    m_curSketchCoord;

		//��ǰ����ĵ�������
		GEOMETRY::geom::Coordinate    m_curMousePt;

		//�༭��������
		std::vector<IEditTask*> m_allTasks;

		//��ǰ�༭����
		IEditTask*       m_curTask;

		//�༭��ͼ������
		std::vector<Carto::ILayer*> m_EditLayers;
		//��ǰ�༭��
		Carto::ILayer* m_curLayer;

		typedef std::vector<CSnapAgent*> SnapAgentlist;

		//��׽���룬����Ļ����Ϊ��λ
		double m_screenTolerance;
		//��׽���б�
		SnapAgentlist m_snaplist;

		//Ҫ�صļ��а�
		std::vector<Geodatabase::CFeature*> m_copyFeatures;

		//֧��undo��redo����

		//ͼ��Ļ����б�
		std::vector<STCircle>	mg_undoCircles;
		long				mg_undoIndex;


		std::vector<STMemUndoCycle*> m_memUndoStack;
		long  m_memUndoIndex;

	};

	typedef SYSTEM::CSmartPtr<CEditor> CEditorPtr;
}



#endif