#include "stdafx.h"

#pragma comment (lib,"winmm.lib")

#include <Process.h>
#include "ThreadTask.h"

//#include <windows.h>
#include <mmsystem.h>

#define TIMER_RESOLUTION	1        // 1-millisecond target resolution

static int _nInit = 0;
static unsigned int _timerRes;
static MMRESULT _id;

unsigned __stdcall ThreadFunc(void *pArg)
{
	ThreadTask *task = (ThreadTask *)pArg;

	if(task == NULL)	return 0;

	double period = (double)task->_period;

	while(task->_isRun == true) {
		task->_periodTime = task->_periodFreqTime.GetFreqTime();
		task->_runFreqTime.StartFreqTime();
		task->Run();
		task->_runTime = task->_runFreqTime.EndFreqTime();

		if(period - task->_runTime >= 0.0) {
			Sleep((DWORD)(period - task->_runTime));
		}
		else {
			Sleep(0);
		}
	}

	_endthreadex(0);

	return 0;
}

ThreadTask::ThreadTask(std::string name, unsigned long period, void *userMsg1, void *userMsg2)
: TaskInterface(name, period, userMsg1, userMsg2)
{
	if(_nInit++ == 0) {
		TIMECAPS tc;

		timeGetDevCaps(&tc, sizeof(TIMECAPS));
		_timerRes = min(max(tc.wPeriodMin, TIMER_RESOLUTION), tc.wPeriodMax);
		timeBeginPeriod(_timerRes);
	}

	_hThread = INVALID_HANDLE_VALUE;
}

ThreadTask::~ThreadTask(void)
{
	if(_hThread != INVALID_HANDLE_VALUE) {
		CloseHandle(_hThread);
	}

	if(--_nInit == 0) {
		timeKillEvent(_id);

		if (_timerRes > 0) {
			timeEndPeriod (_timerRes);
		}
	}
}

int ThreadTask::Start(void)
{
	unsigned threadId;

	_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, this, CREATE_SUSPENDED, &threadId);
	if(_hThread == INVALID_HANDLE_VALUE) {
		return -1;
	}
	_periodFreqTime.StartFreqTime();
	

	/*
	if(SetThreadAffinityMask(_hThread, threadMaks[nThreadMask++]) == 0) {
	}
	if(nThreadMask == 4) {
		nThreadMask = 0;
	}
	//*/

	if(SetThreadPriority(_hThread, THREAD_PRIORITY_TIME_CRITICAL) == FALSE) {
	}

	if(ResumeThread(_hThread) == -1) {
	}
	
	_isRun = true;

	return 0;
}

int ThreadTask::Stop(void)
{
	_isRun = false;

	if(_hThread != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(_hThread, _period + 5);
		CloseHandle(_hThread);
		_hThread = INVALID_HANDLE_VALUE;
	}

	return 0;
}

void ThreadTask::Run(void)
{
}