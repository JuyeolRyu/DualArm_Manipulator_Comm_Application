#pragma once

#include "ThreadTask.h"
#include "FreqTime.h"

class TeleoperationCanOpenStatus : public ThreadTask
{
public:
	TeleoperationCanOpenStatus(std::string name, unsigned long period, void *userMsg1 = NULL );
	~TeleoperationCanOpenStatus(void);

	FreqTime _YGFreqTime;
	double _YGTime;

	void Run();
};

