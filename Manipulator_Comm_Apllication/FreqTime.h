#pragma once

#include <Windows.h>

class FreqTime
{
public:
	FreqTime();
	virtual ~FreqTime();

private:
	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;
	LARGE_INTEGER m_runTime;

public:
	void StartFreqTime();
	double GetFreqTime();
	double EndFreqTime();

	void StartFreqTime(HANDLE handle);
	double GetFreqTime(HANDLE handle);
	double EndFreqTime(HANDLE handle);
};
