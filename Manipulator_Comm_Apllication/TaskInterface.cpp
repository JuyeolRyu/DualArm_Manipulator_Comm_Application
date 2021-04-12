#include "stdafx.h"
#include "TaskInterface.h"

int nThreadMask = 1;
unsigned long threadMaks[] = {1, 2, 4, 8};

TaskInterface::TaskInterface(std::string name, unsigned long period, void *userMsg1, void *userMsg2)
{
	_name = name;
	_period = period;
	_userMsg1 = userMsg1;
	_userMsg2 = userMsg2;

	_periodTime = 0.0;
	_runTime = 0.0;
}

TaskInterface::~TaskInterface(void)
{
}

std::string TaskInterface::GetName(void)
{
	return _name;
}

int TaskInterface::Start(void)
{
	return -1;
}

int TaskInterface::Stop(void)
{
	return -1;
}

void TaskInterface::Run(void)
{
}