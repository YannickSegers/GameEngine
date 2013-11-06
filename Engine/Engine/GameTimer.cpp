//=======================================================================================
// GameTimer.cpp by Frank Luna (C) 2008 All Rights Reserved.
// Adapted for this by Yannick Segers
//=======================================================================================
#include "GameTimer.h"
#include "Util.h"

GameTimer::GameTimer()
	:m_SecondsPerCount(0.0)
	,m_DeltaTime(-1.0)
	,m_BaseTime(0)
	,m_PausedTime(0)
	,m_PrevTime(0)
	,m_CurrTime(0)
	,m_Stopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::GetGameTime()const
{
	// If we are stopped, do not count the time that has passed since we stopped

	if(m_Stopped)
	{
		// I think this also need m_PausedTime subtracted from it, otherwise all the previous pause time 
		// is added to the result
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
	}

	// The distnace m_CurrTimer - m_BaseTime includes paused timer
	// which we do not want to count. To correct this we can subtract
	// the paused time from m_CurrTime

	else 
	{
		return (float) (((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
	}
}

float GameTimer::GetDeltaTime()const
{
	return (float)m_DeltaTime;
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_Stopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//Accumulate the time elapsed between stop and start pairs.

	// If we are resuming the timer from a stopped state
	if(m_Stopped)
	{
		//then accumulate the paused timer.
		m_PausedTime += (startTime - m_StopTime);

		//Since we are starting the timer back up, the current
		//previous time is not valid, as it occurred while paused
		//So reset it to the current time.
		m_PrevTime = startTime;

		// no longer stopped
		m_StopTime = 0;
		m_Stopped = false;
	}
}

void GameTimer::Stop()
{
	// If we are already stopped, then don't do anything.
	if(!m_Stopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//Otherwise, save the time we stopped at, and set
		//the Boolean flag indicating the timer is stopped.
		m_StopTime = currTime;
		m_Stopped = true;
	}
}

void GameTimer::Tick()
{
	if(m_Stopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

	//Get the time this frame.
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	//Time difference betweeen this frame and the previous.
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount;

	//Prepare for next frame.
	m_PrevTime = m_CurrTime;

	//Force nonnegative. The DXSDK's CDXUTTimer mentions that if the
	//processor goes into a power save mode or we get shuffled to
	//another processor, then m_DeltaTime can be negative.
	if(m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}