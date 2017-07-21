#include<iostream>  
#include<Windows.h>
#include<tchar.h>
#include<string.h>

#define PROPERTY_MAX_LEN    128 // �����ֶ���󳤶�
typedef struct _T_DEVICE_PROPERTY
{
	TCHAR szProperty[PROPERTY_MAX_LEN];
} T_DEVICE_PROPERTY;

using namespace std;

string TCHAR2STRING(TCHAR *STR);

int main(){
	HMODULE hModule = NULL;
	typedef BOOL(*Func)();
	typedef INT(*Funcc)(INT iQueryType, T_DEVICE_PROPERTY *properties, INT iSize);
	// ��̬���� DLL �ļ�
	hModule = LoadLibrary(_TEXT("..//Debug//MyDLL.dll"));

	// ��ȡ������ַ
	Func Func_Verify_BoardIDAndCpuID = (Func)GetProcAddress(hModule, "Verify_BoardIDAndCpuID");
	
	if (Func_Verify_BoardIDAndCpuID()){
		cout << "��֤�ɹ���"<<endl;
	}
	else
	{
		cout << "��֤ʧ�ܣ�" << endl;
	}

	cout << endl;

	Funcc Func_WMI_DeviceQuery = (Funcc)GetProcAddress(hModule, "WMI_DeviceQuery");

	T_DEVICE_PROPERTY mainboardID;
	T_DEVICE_PROPERTY CpuID;

	Func_WMI_DeviceQuery(2, &mainboardID, 1);
	Func_WMI_DeviceQuery(3, &CpuID, 1);

	string mainboardIDStr = TCHAR2STRING(mainboardID.szProperty);
	string CpuIDStr = TCHAR2STRING(CpuID.szProperty);

	cout << "�������кţ�" << mainboardIDStr.data() << endl;
	cout << "CPU���кţ�" <<  CpuIDStr.data() << endl;

	system("pause");

};
string TCHAR2STRING(TCHAR *STR){

	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);

	char* chRtn = new char[iLen*sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	std::string str(chRtn);

	return str;

}