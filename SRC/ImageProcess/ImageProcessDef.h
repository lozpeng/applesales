#ifndef _IMAGE_PROCESS_DEF_H_
#define _IMAGE_PROCESS_DEF_H_

#if defined  IMAGEPROCESS_EXPORTS
#define IMP_DLL __declspec(dllexport)
#else
#define IMP_DLL __declspec(dllimport)
#pragma comment(lib,"ImageProcess.lib")
#pragma message("Automatically linking with ImageProcess.dll")
#endif

namespace ImageProcess
{

typedef struct ClassInfo
{
	HRGN hRgn;				//一个Polypolygon,多Part构成
	unsigned char Red;			//类颜色
	unsigned char Green;
	unsigned char Blue;
	char szClsDes[256];		//类描述
}ClassInfo, *PClassInfo;

typedef struct ClassifyInfo
{
	long		lClsCount; //类数目
	ClassInfo*		pstCls;

}ClassifyInfo, *PClassifyInfo;

//整型坐标点
struct IntPoint
{
	int x;
	int y;
};

typedef struct st_Extent
{
	double xmin, xmax;
	double ymin, ymax;
}STExtent;

//种子，用来标记位置
typedef struct{
	int Height;
	int Width;
}Seed;

}
#endif