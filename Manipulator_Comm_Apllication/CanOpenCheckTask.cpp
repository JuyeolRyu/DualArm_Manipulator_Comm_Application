#include "StdAfx.h"
#include "CanOpenCheckTask.h"


CanOpenCheckTask::CanOpenCheckTask(void *userMsg1)
{
	_userMsg1 = userMsg1; // Dlg pointer
}

CanOpenCheckTask::~CanOpenCheckTask(void)
{
}



void CanOpenCheckTask::ExeCanOpenCheckTask()
{
	CanOpenDsp402*		_canDSP = (CanOpenDsp402*)_userMsg1;

	int test_id=9;

	_canDSP->GetPositionRobotro(test_id);

}
