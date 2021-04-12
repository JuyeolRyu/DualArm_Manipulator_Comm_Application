#include "StdAfx.h"
#include "CanOpenStatusTask.h"

CanOpenStatusTask::CanOpenStatusTask(void* userMsg1)
{
	_userMsg1 = userMsg1;
}


CanOpenStatusTask::~CanOpenStatusTask(void)
{
}


void CanOpenStatusTask::ExeCanOpenStatusTask() 
{
	CanOpenRead* _canRead = (CanOpenRead*) _userMsg1;

	//m_MotionTab = new CMotionTabDlg(this);

	_canRead->ReadFunc();
	
}
