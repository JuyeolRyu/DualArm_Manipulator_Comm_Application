#include "stdafx.h"
#include "ClientSock.h"

CClientSock::CClientSock()
{
	CAsyncSocket::CAsyncSocket();
}

void CClientSock::SetWnd(HWND hwnd)
{
	m_pHwnd = hwnd;
}


void CClientSock::OnReceive(int nErrorCode)
{
	TRACE("Errocode = %d", nErrorCode);
	SendMessage(m_pHwnd, WM_RECEIVE_DATA, 0, 0);
}