#pragma once

#include "ThreadTask.h"

class TeleoperationCanOpenTask : public ThreadTask
{
public:
	TeleoperationCanOpenTask(std::string name, unsigned long period, void *userMsg1 = NULL);
	virtual ~TeleoperationCanOpenTask(void);

	void Run(void);
};
