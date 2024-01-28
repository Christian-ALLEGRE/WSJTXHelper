#ifndef __REGKEY_H
#define __REGKEY_H

CString GetKey(CString Key);
CString GetUserKey(CString Key);
void SetKey(CString Key, CString Value);
void CreateUserKey(CString Key);
void SetUserKey(CString Key, CString Value);
#endif