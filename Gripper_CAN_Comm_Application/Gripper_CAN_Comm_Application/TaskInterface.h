#pragma once

#include <string>
#include "FreqTime.h"

extern int nThreadMask;
extern unsigned long threadMaks[];

class TaskInterface
{
public:
	TaskInterface(std::string name, unsigned long period = 10, void *userMsg1 = NULL, void *userMsg2 = NULL);
	virtual ~TaskInterface(void);

protected:
	std::string _name;
	void *_userMsg1;
	void *_userMsg2;

public:
	unsigned long _period;
	FreqTime _periodFreqTime;
	double _periodTime;
	FreqTime _runFreqTime;
	double _runTime;

	std::string GetName(void);
	double GetPeriod(void) {
		return _periodTime;
	}

	double GetRunTime(void) {
		return _runTime;
	}

	virtual int Start(void);
	virtual int Stop(void);
	virtual void Run(void);
};
