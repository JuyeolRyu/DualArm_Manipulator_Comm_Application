#include "StdAfx.h"
#include "TeleoperationCanOpenStatus.h"
#include "CanOpenStatusTask.h"


TeleoperationCanOpenStatus::TeleoperationCanOpenStatus(std::string name, unsigned long period, void *userMsg1 )
	:ThreadTask(name, period, userMsg1)
{

}


TeleoperationCanOpenStatus::~TeleoperationCanOpenStatus(void)
{
}


void TeleoperationCanOpenStatus::Run() 
{
	CanOpenStatusTask* _CanOpenStatusTask = (CanOpenStatusTask *) _userMsg1;

	_CanOpenStatusTask -> ExeCanOpenStatusTask();
}