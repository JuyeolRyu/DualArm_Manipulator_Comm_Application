#pragma once

#include "CanOpenDef.h"

//#include "FreqTime.h"
#define	MOTORINFO_CUR		1
#define	MOTORINFO_POS		2
#define	MOTORINFO_VEL		3
#define	MOTORINFO_STA		4
#define	MOTORINFO_ERR		5
#define	MOTORINFO_MODE	6
#define	CUR							11
#define	POS							12
#define	VEL							13
#define	MAX_CUR					14

#define WM_RECEIVE_CAN_DATA	(WM_USER+3)

class CanOpenRead
{
public:
	CanOpenRead(HWND m_hWnd, HANDLE ch);
	~CanOpenRead(void);

	void ReadFunc();

	//int getMotor(int value, int id);
	//void setMotor(int value, int id, int data);
	MOTORINFO _motor;

private:
	HWND _hWnd;
	HANDLE _ch;
	uint32_t *pdwNum;
	uint32_t motornum;

	int current[MOTORNUM];
	int velocity[MOTORNUM];
	int position[MOTORNUM];
	int tmpPosition[MOTORNUM];
	int maxCur[MOTORNUM];
		
	void rMsgProcessing(CANMSG *msg, MOTORINFO* motor);
	
};


