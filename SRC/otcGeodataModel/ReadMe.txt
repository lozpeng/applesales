========================================================================
    �ģ��⣺otcGeodatabase ��Ŀ����
========================================================================

Ӧ�ó�������Ϊ�������˴� otcGeodatabase ��Ŀ���������ڴ˻���֮��
��д�Լ��Ķ�̬���ӿ� (DLL)��


���ļ������������Ŀ��ÿ���ļ�
�����ݡ�

otcGeodatabase.vcproj
    ����ʹ��Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
    �������й����ɸ��ļ���ʹ�õ� Visual C++ �汾����Ϣ���Լ�
    �й���Ӧ�ó�������ѡ���ƽ̨�����ú���Ŀ����
    ����Ϣ��

otcGeodatabase.idl
    ���ļ�������������Ŀ�ж�������Ϳ⡢�ӿ�
    �� coclass �� IDL ���塣
    ���ļ����� MIDL ���������������ɣ�
        C++ �ӿڶ���� GUID ����                 (GEOMETRY)
        GUID ����                                (otcGeodatabase_i.c)
        һ�����Ϳ�                               (otcGeodatabase.tlb)
        ���ʹ���                                 (otcGeodatabase_p.c �� dlldata.c)

GEOMETRY
    ���ļ������� otcGeodatabase.idl �ж������� C++ �ӿڶ���
    �� GUID �����������ڱ���������� MIDL �������ɡ�

otcGeodatabase.cpp
    ���ļ���������ӳ��� DLL ������ʵ�֡�

otcGeodatabase.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ����
    ����

otcGeodatabase.def
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
    ��Щ�ļ�����������Ϊ otcGeodatabase.pch ��Ԥ����ͷ (PCH) �ļ�
    ����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    �������ڶ�����Դ ID �ı�׼ͷ�ļ���

/////////////////////////////////////////////////////////////////////////////
����/��� (stub) DLL ��Ŀ��ģ�鶨���ļ���

otcGeodatabaseps.vcproj
    ���ļ����������ɴ���/��� (stub) DLL ����Ŀ�ļ������б�Ҫ����
	����Ŀ�е� IDL �ļ��������ٰ���һ���ӿڣ�����
	�����ɴ���/��� (stub) DLL ֮ǰ�����ȱ��� IDL �ļ���	�˽�������
	dlldata.c��otcGeodatabase_i.c �� otcGeodatabase_p.c�����ǡ�
	�����ɴ���/��� (stub) DLL ������ġ�

otcGeodatabaseps.def
    ��ģ�鶨���ļ�Ϊ�������ṩ�йش���/��� (stub) ��Ҫ���
    ��������Ϣ��

/////////////////////////////////////////////////////////////////////////////
