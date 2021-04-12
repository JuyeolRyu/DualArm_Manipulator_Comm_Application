#pragma once

#include "CanOpenRead.h"

class CanOpenStatusTask
{
public:
	CanOpenStatusTask(void* userMsg1 );
	~CanOpenStatusTask(void);

	void ExeCanOpenStatusTask();

	int control_flag;
	
protected:
	void *_userMsg1;
};

