#pragma once

#include "CanOpenDsp402.h"

class CanOpenCheckTask
{
public:
	CanOpenCheckTask(void *userMsg1);
	virtual ~CanOpenCheckTask(void);

	void ExeCanOpenCheckTask();


protected:
	void *_userMsg1;
};
