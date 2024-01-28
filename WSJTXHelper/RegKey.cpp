// RegKey.cpp : implementation file
//

#include "stdafx.h"
#include "RegKey.h"
#include "winreg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CString GetKey(CString Key)
{

#define BUFLEN 255
	WCHAR Buf[BUFLEN];
	Buf[0] = 0;
	long BufLen = BUFLEN;
	RegQueryValue(HKEY_LOCAL_MACHINE, Key, Buf, &BufLen);
	//Dlg->MessageBox(Key + "=" + Buf);
	CString result = Buf;
	return result;
}

CString GetUserKey(CString Key)
{

#define BUFLEN 255
	WCHAR Buf[BUFLEN];
	Buf[0] = 0;
	long BufLen = BUFLEN;
	RegQueryValue(HKEY_CURRENT_USER, Key, Buf, &BufLen);
	//Dlg->MessageBox(Key + "=" + Buf);
	CString result = Buf;
	return result;
}

//CString GetUserKey(CString Key, CString SubKey)
//{
//	HKEY pHkey;
//	RegOpenKeyEx(HKEY_CURRENT_USER,
//		Key,
//		0,
//		KEY_ALL_ACCESS,
//		&pHkey
//	);
//	CString str;
//	str.Empty();
//	DWORD dw = 0;
//	DWORD dwType = 0;
//	LONG lRes = RegQueryValueEx(pHkey, (LPTSTR)SubKey.GetBuffer(0), NULL, &dwType,
//		NULL, &dw);
//	if (lRes == ERROR_SUCCESS)
//	{
//		ASSERT(dwType == REG_SZ);
//		LPTSTR lpsz = str.GetBufferSetLength(dw);
//		lRes = RegQueryValueEx(pHkey, (LPTSTR)SubKey.GetBuffer(0), NULL, &dwType, (BYTE*)lpsz, &dw);
//		ASSERT(lRes == ERROR_SUCCESS);
//		return str;
//	}
//	return CString("");
//}
//
void SetKey(CString Key, CString Value)
{
	// Update registry
	//Dlg->MessageBox(CString("Saving ") + Key + " Value=" + Value);
	int result = RegSetValue(HKEY_LOCAL_MACHINE,
		Key.GetBuffer(0),
		REG_SZ,
		Value.GetBuffer(0),
		sizeof(Value)
	);
}

void CreateUserKey(CString Key)
{
	HKEY hKey;
	LPCTSTR sk = TEXT("SOFTWARE\\" + Key);

	LONG openRes = RegCreateKeyEx(
		HKEY_CURRENT_USER,
		sk,
		0,
		NULL,
		REG_OPTION_BACKUP_RESTORE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		NULL);
}

void SetUserKey(CString Key, CString Value)
{
	// Update registry
	//Dlg->MessageBox(CString("Saving ") + Key + " Value=" + Value);
	int result = RegSetValue(HKEY_CURRENT_USER,
		Key.GetBuffer(0),
		REG_SZ,
		Value.GetBuffer(0),
		sizeof(Value)
	);
}

//void SetUserKey(CString Key, CString SubKey, CString Value)
//{
//	HKEY pHkey;
//	int result = RegOpenKeyEx(HKEY_CURRENT_USER,
//		Key,
//		0,
//		KEY_ALL_ACCESS,
//		&pHkey
//	);
//	result = RegSetValueEx(pHkey,
//		SubKey,
//		0,
//		REG_SZ,
//		(unsigned char *)Value.GetBuffer(0),
//		Value.GetLength()
//	);
//}