#include <afxsock.h>//CAsyncSocket 사용하기 위해 include
#define WM_RECEIVE_DATA WM_USER+2

class CClientSock : public CAsyncSocket
{

public:
	CClientSock();

	void SetWnd(HWND hwnd);

	virtual void OnReceive(int nErrorCode);
public:

	HWND m_pHwnd;
};