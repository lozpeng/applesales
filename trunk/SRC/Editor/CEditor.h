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

	//内存中Geometry回退的结构体，存放了一些必要信息
	struct STMemUndoCycle
	{
		~STMemUndoCycle() {delete pGeometry;}

		GEOMETRY::geom::Geometry* pGeometry;

		long lcurPart; //当前在Geometry哪一部分
		bool bcurPartFinish; //当前部分是否结束


	};

	class EDITOR_DLL CEditor : public Carto::IEditor
	{
	public:

		CEditor(Carto::CMap *pMap);

		virtual ~CEditor();
	public:

		/**
		* 开始编辑
		*/
		void StartEdit();

		/**
		* 结束编辑
		* @param bSave 是否保存修改
		*/
		void StopEdit(bool bSave);

		/**
		* 保存编辑
		*/
		void SaveEdit();

		/**
		* 是否在编辑
		*/
		bool IsEditing();

		/**
		* 撤销操作
		*/
		void Undo();

		/**
		* 重做操作
		*/
		void Redo();

		/**
		* 是否可以撤销
		*/
		bool CanUndo();

		/**
		* 是否可以重做
		*/
		bool CanRedo();

		/**
		* 绘制编辑对象，如正在创建的图形，编辑的图形等
		*/
		void DrawEdit(Display::IDisplayPtr pDisplay);
	public:

		/**
		* 删除要素
		*/
		void DeleteFeature();

		/**
		* 复制要素
		*/
		void CopyFeature();

		/**
		* 粘贴要素
		*/
		void PasteFeature();

		/**
		* 剪切要素
		*/
		void CutFeature();

		/**
		* 将图形加入到当前图层中
		*/
		void AppendGeometry(GEOMETRY::geom::Geometry *pGeometry);


		/**
		* 显示编辑属性对话框
		*/
		void EditAttribute();

		/**
		* 得到编辑的图层数组
		*/
		void GetEditLayers(std::vector<Carto::ILayer*> &layers);

		/**
		* 查找需要编辑的图形
		*/
		bool SearchEditGeometry();

		/**
		* 提交编辑空间编辑的图形
		*/
		void CommitModifyShape();

		/**
		* 提交要修改的要素,函数接管Geometry指针的控制
		*/
		void CommitModifyShapes(std::vector<GEOMETRY::geom::Geometry*> &vecShp,std::vector<long> &vecShapeId, std::vector<Carto::ILayer*> &vecLayers);

		void DrawEditShape(Display::IDisplayPtr &pDisplay,GEOMETRY::geom::Geometry* pGeometry);

	public:

		/****************************************************************************************
		*回退相关的函数
		*****************************************************************************************/

		/**
		* 将做过操作的图层加入到回退列表
		*/
		void AddToCircle(std::vector<Carto::ILayer*> &layers);

		/**
		* 节点回退
		*/
		void VertexUndo();
		/**
		* 节点重做
		*/
		void VertexRedo();

		bool VertexCanUndo();
		bool VertexCanRedo();

		//将Geometry压入回滚堆栈
		void PushGeometry2Undo(GEOMETRY::geom::Geometry* pGeometry,long lcurPart=0,bool bpartFinish=false);

		//清空节点回滚堆栈
		void ClearMemUndo();

		/****************************************************************************************
		*画笔相关的函数
		*****************************************************************************************/

		void CreateEditSketch(Carto::ILayer *pLayer);

		//添加画笔中的点
		void AddSketchPoint(GEOMETRY::geom::Coordinate &point,double dz =0.0,double dm =0.0);

		//结束画笔
		void FinishSketch();
		//结束画笔中的一部分
		void FinishSketchPart();

		void SetSketchEmpty();

		GEOMETRY::geom::Geometry* GetSketchGeometry() const;


		void SetMousePt(GEOMETRY::geom::Coordinate &pt){m_curMousePt =pt; }

		void SetbSketch(bool bSketch){m_bSketch =bSketch;};

		void SetbEditFeature(bool b){m_bEditFeature =b;};

		void SetbEditVertex(bool b) {m_bInVertexEdit =b;}

		/****************************************************************************************
		*以下为捕捉相关的函数
		*****************************************************************************************/

		/**
		* 捕捉
		* @param inPoint  输入的点
		* @param outPoint 捕捉到的点 
		*/
		void Snap(GEOMETRY::geom::Coordinate inPoint,GEOMETRY::geom::Coordinate &outPoint);

		//设置和获取捕捉距离
		double GetSnapTolerance();

		void  SetSnapTolerance(double d);

		void ShowSnapDlg();
		void AddSnapAgent(Carto::ILayer *pLayer,unsigned long snaptype);

		//得到一个图层的捕捉方式
		unsigned long GetLayerSnaptype(Carto::ILayer *pmapLayer);

		void RemoveSnapAgent(Carto::ILayer *pmapLayer);

		//删除所有捕捉器
		void RemoveAllSnapAgent();

		/****************************************************************************************
		*目标图层设置相关的函数
		*****************************************************************************************/

		//获得当前编辑图层的选择集
		//获得当前图层选择集
		void GetCurLayerSelection(std::vector<Geometry*> &shapes, 
			std::vector<long> &shapeIds, vector<Carto::ILayer*> &players);

		//获得当前图层
		Carto::ILayer* GetCurLayer() {return m_curLayer;};

		//改变编辑目标层
		void ChangeCurLayer(std::string layername);

		void OnTagetLayerChanged();

		/**************************************************************
		*编辑任务相关的函数
		***************************************************************/

		//设置当前编辑任务
		void SetEditTask(std::string &taskname);

		void DeleteAllTask();

		std::string GetCurTaskName() const;

		void OnEditTaskChanged();

		/**************************************************************
		*右键菜单或快捷键的响应函数
		***************************************************************/
		void OnSketchAbsXY();

		//输入相对坐标
		void OnSketchDeltaXY();

		//输入方位\长度
		void OnSketchDirLen();


	private:

		//初始化所有的任务
		void InitEditTask();

		//编辑结束时调用，用于清理
		void OnEndEdit();

		//清理编辑的图形
		void ClearModifyGeometry();

		//清理剪切板中的要素
		void ClearCopyFeatures();

		//绘制编辑的图形


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

		//是否在编辑
		bool m_bEditing;

		//是否在编辑节点
		bool		m_bInVertexEdit;

		//是否在画图形
		bool m_bSketch;
		//是否在编辑图形
		bool m_bEditFeature;

		//画笔
		Display::CGeometrySketchPtr m_pSketch;

		//当前绘制点的地理坐标
		GEOMETRY::geom::Coordinate    m_curSketchCoord;

		//当前鼠标点的地理坐标
		GEOMETRY::geom::Coordinate    m_curMousePt;

		//编辑任务数组
		std::vector<IEditTask*> m_allTasks;

		//当前编辑任务
		IEditTask*       m_curTask;

		//编辑的图层数组
		std::vector<Carto::ILayer*> m_EditLayers;
		//当前编辑层
		Carto::ILayer* m_curLayer;

		typedef std::vector<CSnapAgent*> SnapAgentlist;

		//捕捉距离，以屏幕像素为单位
		double m_screenTolerance;
		//捕捉器列表
		SnapAgentlist m_snaplist;

		//要素的剪切板
		std::vector<Geodatabase::CFeature*> m_copyFeatures;

		//支持undo与redo操作

		//图层的回退列表
		std::vector<STCircle>	mg_undoCircles;
		long				mg_undoIndex;


		std::vector<STMemUndoCycle*> m_memUndoStack;
		long  m_memUndoIndex;

	};

	typedef SYSTEM::CSmartPtr<CEditor> CEditorPtr;
}



#endif