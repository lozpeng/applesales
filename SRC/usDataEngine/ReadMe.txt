========================================================================
    �ģ��⣺usDataEngine ��Ŀ����
========================================================================

Ӧ�ó�������Ϊ�������˴� usDataEngine ��Ŀ���������ڴ˻���֮��
��д�Լ��Ķ�̬���ӿ� (DLL)��


���ļ������������Ŀ��ÿ���ļ�
�����ݡ�

usDataEngine.vcproj
    ����ʹ��Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
    �������й����ɸ��ļ���ʹ�õ� Visual C++ �汾����Ϣ���Լ�
    �й���Ӧ�ó�������ѡ���ƽ̨�����ú���Ŀ����
    ����Ϣ��

usDataEngine.idl
    ���ļ�������������Ŀ�ж�������Ϳ⡢�ӿ�
    �� coclass �� IDL ���塣
    ���ļ����� MIDL ���������������ɣ�
        C++ �ӿڶ���� GUID ����                 (usDataEngine.h)
        GUID ����                                (usDataEngine_i.c)
        һ�����Ϳ�                               (usDataEngine.tlb)
        ���ʹ���                                 (usDataEngine_p.c �� dlldata.c)

usDataEngine.h
    ���ļ������� usDataEngine.idl �ж������� C++ �ӿڶ���
    �� GUID �����������ڱ���������� MIDL �������ɡ�

usDataEngine.cpp
    ���ļ���������ӳ��� DLL ������ʵ�֡�

usDataEngine.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ����
    ����

usDataEngine.def
    ��ģ�鶨���ļ�Ϊ�������ṩ�й� DLL ��Ҫ���
    ��������Ϣ�������������������ݵĵ�����
        DllGetClassObject  
        DllCanUnloadNow    
        GetProxyDllInfo    
        DllRegisterServer	
        DllUnregisterServer

/////////////////////////////////////////////////////////////////////////////
������׼�ļ���

StdAfx.h��StdAfx.cpp
    ��Щ�ļ�����������Ϊ usDataEngine.pch ��Ԥ����ͷ (PCH) �ļ�
    ����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    �������ڶ�����Դ ID �ı�׼ͷ�ļ���


/////////////////////////////////////////////////////////////////////////////
