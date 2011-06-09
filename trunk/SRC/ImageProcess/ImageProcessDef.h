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
	HRGN hRgn;				//һ��Polypolygon,��Part����
	unsigned char Red;			//����ɫ
	unsigned char Green;
	unsigned char Blue;
	char szClsDes[256];		//������
}ClassInfo, *PClassInfo;

typedef struct ClassifyInfo
{
	long		lClsCount; //����Ŀ
	ClassInfo*		pstCls;

}ClassifyInfo, *PClassifyInfo;

//���������
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

//���ӣ��������λ��
typedef struct{
	int Height;
	int Width;
}Seed;

}
#endif