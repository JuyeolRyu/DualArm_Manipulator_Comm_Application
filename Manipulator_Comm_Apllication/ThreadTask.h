#pragma once
#include "TaskInterface.h"

class ThreadTask : public TaskInterface
{
public:
	ThreadTask(std::string name, unsigned long period = 10, void *userMsg1 = NULL, void *userMsg2 = NULL);
	virtual ~ThreadTask(void);

	bool _isRun;
	HANDLE _hThread;

	int Start(void);
	int Stop(void);
	virtual void Run(void);
};
