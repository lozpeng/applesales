// workflowWizard.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "workflowWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//


// CworkflowWizardApp

BEGIN_MESSAGE_MAP(CworkflowWizardApp, CWinApp)
END_MESSAGE_MAP()


// CworkflowWizardApp ����

CworkflowWizardApp::CworkflowWizardApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CworkflowWizardApp ����

CworkflowWizardApp theApp;


// CworkflowWizardApp ��ʼ��

BOOL CworkflowWizardApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
