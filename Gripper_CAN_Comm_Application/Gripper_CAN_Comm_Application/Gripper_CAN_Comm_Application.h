
// can_comm_basic.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Ccan_comm_basicApp:
// �� Ŭ������ ������ ���ؼ��� can_comm_basic.cpp�� �����Ͻʽÿ�.
//

class Ccan_comm_basicApp : public CWinApp
{
public:
	Ccan_comm_basicApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Ccan_comm_basicApp theApp;