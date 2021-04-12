#pragma once

#include "CanOpenDef.h"

extern int g_CanID;
extern UINT16 g_CanBitRate0;
extern UINT16 g_CanBitRate1;

class CanOpenComm
{
public:
	CanOpenComm(void);
	virtual ~CanOpenComm(void);

public:
	HANDLE CanOpenConnect(uint32_t dwCanNo);
	int CanOpenDisConnect();

private:
	HANDLE hDevice;     // device handle
	HANDLE hCanCtl;		// controller handle 
	HANDLE hCanChn;		// channel handle
};

