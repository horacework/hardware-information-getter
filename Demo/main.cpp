#include<iostream>  
#include<Windows.h>
#include<tchar.h>
#include<string.h>

#define PROPERTY_MAX_LEN    128 // 属性字段最大长度
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
	// 动态加载 DLL 文件
	hModule = LoadLibrary(_TEXT("..//Debug//MyDLL.dll"));

	// 获取函数地址
	Func Func_Verify_BoardIDAndCpuID = (Func)GetProcAddress(hModule, "Verify_BoardIDAndCpuID");
	
	if (Func_Verify_BoardIDAndCpuID()){
		cout << "验证成功！"<<endl;
	}
	else
	{
		cout << "验证失败！" << endl;
	}

	cout << endl;

	Funcc Func_WMI_DeviceQuery = (Funcc)GetProcAddress(hModule, "WMI_DeviceQuery");

	T_DEVICE_PROPERTY mainboardID;
	T_DEVICE_PROPERTY CpuID;

	Func_WMI_DeviceQuery(2, &mainboardID, 1);
	Func_WMI_DeviceQuery(3, &CpuID, 1);

	string mainboardIDStr = TCHAR2STRING(mainboardID.szProperty);
	string CpuIDStr = TCHAR2STRING(CpuID.szProperty);

	cout << "主板序列号：" << mainboardIDStr.data() << endl;
	cout << "CPU序列号：" <<  CpuIDStr.data() << endl;

	system("pause");

};
string TCHAR2STRING(TCHAR *STR){

	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);

	char* chRtn = new char[iLen*sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	std::string str(chRtn);

	return str;

}