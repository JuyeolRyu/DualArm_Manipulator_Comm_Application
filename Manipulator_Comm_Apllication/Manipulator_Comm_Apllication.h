
// MFC_Ryu_ClientPgr.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Ryu_ClientPgrApp:
// �� Ŭ������ ������ ���ؼ��� MFC_Ryu_ClientPgr.cpp�� �����Ͻʽÿ�.
//

class CMFC_Ryu_ClientPgrApp : public CWinApp
{
public:
	CMFC_Ryu_ClientPgrApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Ryu_ClientPgrApp theApp;