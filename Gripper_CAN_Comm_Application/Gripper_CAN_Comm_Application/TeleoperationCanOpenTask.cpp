#include "StdAfx.h"
#include "TeleoperationCanOpenTask.h"

#include "CanOpenCheckTask.h"


TeleoperationCanOpenTask::TeleoperationCanOpenTask(std::string name, unsigned long period, void *userMsg1)
: ThreadTask(name, period, userMsg1)
{
}

TeleoperationCanOpenTask::~TeleoperationCanOpenTask(void)
{
}

void TeleoperationCanOpenTask::Run(void)
{
	CanOpenCheckTask *_CanOpenCheckTask = (CanOpenCheckTask *)_userMsg1;

	_CanOpenCheckTask->ExeCanOpenCheckTask();
}