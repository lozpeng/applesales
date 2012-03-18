/*******************************************
	 EnviColorMap.h : ͷ�ļ�

	 ������      ��ȡcolor.tlb�е���ɫ����Ϣ��color.tlb�Ǵ�envi��õģ���Ҫ����envi����ɫ��

	 ����        ����ǩ��   ���Աǩ��  ������ǩ��  �޸���� 

**********************************************/
struct COLOR_MAP
{
	BYTE ucR[256];
	BYTE ucG[256];
	BYTE ucB[256];
	char szName[32];
};                        //�洢��ȡ����ɫ���ÿ����ɫ��ֵ����ɫ����colors.tbl�ж�ȡ

CString GetAppPathName();

class CEnviColorMap
{
public:
	CEnviColorMap();
	~CEnviColorMap(void);
	///<summary>
	///��ö�Ӧ��������ɫ��
	///</summary>
	///<param name="iIndex">��ɫ�������</param>
	///<param name="struColorMap">��ȡ����ɫ�����Ϣ</param>
	///<returns>���ص�ǰ�ļ������ڵ�·��</returns>
	 void GetColorMap(int iIndex,COLOR_MAP& struColorMap);
	///<summary>
	///�����ɫ���ļ�����ɫ��ĸ���
	///</summary>
	///<param name="iColorMapCount">���ص���ɫ��ĸ���</param>
	///<returns>���ص�ǰ�ļ������ڵ�·��</returns>
	 void GetColorMapCount(int& iColorMapCount);
	///<summary>
	///��ô���ɫ���ļ��Ƿ�ɹ�
	///</summary>
	///<returns>�ɹ�����true�����򷵻�false</returns>
	 bool GetOpenResult();
private:
	CFile m_objFile;              //�洢�򿪵���ɫ����Ϣ
	bool  m_bSuccessOpen;         //�洢�Ƿ�򿪳ɹ�
	int   m_iColorMapCount;        //�洢��ɫ���ļ�����ɫ��ĸ���
};
