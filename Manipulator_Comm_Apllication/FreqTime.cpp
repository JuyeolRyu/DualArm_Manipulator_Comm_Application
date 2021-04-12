#include "stdafx.h"
#include "FreqTime.h"

FreqTime::FreqTime() 
{
	QueryPerformanceFrequency(&m_freq);
} 

FreqTime::~FreqTime()
{
}

void FreqTime::StartFreqTime()
{
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&m_startTime);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	m_runTime = m_startTime;
}

double FreqTime::GetFreqTime()
{
	double freqTime;

	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&m_endTime);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);

	freqTime = (double)(m_endTime.QuadPart - m_runTime.QuadPart) / m_freq.QuadPart * 1000;
	m_runTime = m_endTime;

	return freqTime;
}

double FreqTime::EndFreqTime()
{
	double freqTime;

	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceCounter(&m_endTime);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);

	freqTime = (double)(m_endTime.QuadPart - m_startTime.QuadPart) / m_freq.QuadPart * 1000;
	m_runTime = m_endTime;

	return freqTime;
}

void FreqTime::StartFreqTime(HANDLE handle)
{
	DWORD_PTR oldMask = SetThreadAffinityMask(handle, 1);
	QueryPerformanceCounter(&m_startTime);
	SetThreadAffinityMask(handle, oldMask);
	m_runTime = m_startTime;
}

double FreqTime::GetFreqTime(HANDLE handle)
{
	double freqTime;

	DWORD_PTR oldMask = SetThreadAffinityMask(handle, 1);
	QueryPerformanceCounter(&m_endTime);
	SetThreadAffinityMask(handle, oldMask);

	freqTime = (double)(m_endTime.QuadPart - m_runTime.QuadPart) / m_freq.QuadPart * 1000;
	m_runTime = m_endTime;

	return freqTime;
}

double FreqTime::EndFreqTime(HANDLE handle)
{
	double freqTime;

	DWORD_PTR oldMask = SetThreadAffinityMask(handle, 1);
	QueryPerformanceCounter(&m_endTime);
	SetThreadAffinityMask(handle, oldMask);

	freqTime = (double)(m_endTime.QuadPart - m_startTime.QuadPart) / m_freq.QuadPart * 1000;
	m_runTime = m_endTime;

	return freqTime;
}