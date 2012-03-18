/*******************************************
	 EnviColorMap.h : 头文件

	 描述：      读取color.tlb中的颜色表信息，color.tlb是从envi获得的，主要利用envi的颜色表

	 日期        作者签字   检查员签字  负责人签字  修改情况 

**********************************************/
struct COLOR_MAP
{
	BYTE ucR[256];
	BYTE ucG[256];
	BYTE ucB[256];
	char szName[32];
};                        //存储读取的颜色表的每个颜色的值，颜色表在colors.tbl中读取

CString GetAppPathName();

class CEnviColorMap
{
public:
	CEnviColorMap();
	~CEnviColorMap(void);
	///<summary>
	///获得对应索引的颜色表
	///</summary>
	///<param name="iIndex">颜色表的索引</param>
	///<param name="struColorMap">读取的颜色表的信息</param>
	///<returns>返回当前文件夹所在的路径</returns>
	 void GetColorMap(int iIndex,COLOR_MAP& struColorMap);
	///<summary>
	///获得颜色表文件中颜色表的个数
	///</summary>
	///<param name="iColorMapCount">返回的颜色表的个数</param>
	///<returns>返回当前文件夹所在的路径</returns>
	 void GetColorMapCount(int& iColorMapCount);
	///<summary>
	///获得打开颜色表文件是否成功
	///</summary>
	///<returns>成功返回true，否则返回false</returns>
	 bool GetOpenResult();
private:
	CFile m_objFile;              //存储打开的颜色表信息
	bool  m_bSuccessOpen;         //存储是否打开成功
	int   m_iColorMapCount;        //存储颜色表文件中颜色表的个数
};
