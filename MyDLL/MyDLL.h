
#pragma once  

#include <windows.h>
#include <tchar.h>

#ifndef MACRO_T_DEVICE_PROPERTY  
#define MACRO_T_DEVICE_PROPERTY  

#define PROPERTY_MAX_LEN    128 // �����ֶ���󳤶�  
typedef struct _T_DEVICE_PROPERTY
{
	TCHAR szProperty[PROPERTY_MAX_LEN];
} T_DEVICE_PROPERTY;
#endif  

#define WMI_QUERY_TYPENUM   7   // WMI��ѯ֧�ֵ�������  

//�̶�����֤����ID��CPU-ID

TCHAR D_mainboardID[PROPERTY_MAX_LEN] = { _T("PFXGK00WB660H") };
TCHAR D_cpuID[PROPERTY_MAX_LEN] = { _T("BFEBFBFF000806E9") };

#ifdef __cplusplus  
extern "C"
{
#endif  

	/*
	���ܣ�ͨ��WMI��ȡ�豸����
	����˵����
	iQueryType����Ҫ��ѯ���豸����
	0������ԭ��MAC��ַ
	1��Ӳ�����к�
	2���������к�
	3��CPU ID
	4��BIOS���к�
	5�������ͺ�
	6��������ǰMAC��ַ
	properties���洢�豸����ֵ
	iSize���ɴ洢������豸����
	����ֵ��
	-1����֧�ֵ��豸����ֵ
	-2��WMI����ʧ��
	-3������ȷ��WQL��ѯ���
	>=0����ȡ���豸����
	*/
	INT WMI_DeviceQuery(INT iQueryType, T_DEVICE_PROPERTY *properties, INT iSize);

	/*
	���ܣ���֤�����������к���CPU���к��Ƿ���̶���һ��
	*/
	BOOL Verify_BoardIDAndCpuID();

#ifdef __cplusplus  
}
#endif  
