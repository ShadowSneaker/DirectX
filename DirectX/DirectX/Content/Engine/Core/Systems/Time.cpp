#include "Time.h"
#include <Windows.h>


float TTime::DeltaTime{ 1.0f / 60.0f };

float TTime::TimeScale{ 1.0f };



TTime::TTime()
{
	int64 CountsPerSecond;
	QueryPerformanceCounter((LARGE_INTEGER*) &CountsPerSecond);
	SecondsPerCount = 1.0f / (float)CountsPerSecond;
}


void TTime::Update()
{
	if (Paused)
	{
		DeltaTime = 0.0f;
		return;
	}

	int64 CountsPerSecond;
	QueryPerformanceCounter((LARGE_INTEGER*)&CountsPerSecond);
	SecondsPerCount = 1.0f / (float)CountsPerSecond;

	QueryPerformanceCounter((LARGE_INTEGER*) &CurrentTime);
	DeltaTime = ((CurrentTime - PreviousTime) * SecondsPerCount) * 20000.0f * TimeScale;

	PreviousTime = CurrentTime;
	if (DeltaTime < 0.0f) DeltaTime = 0.0f;
}


void TTime::Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*) &CurrentTime);
	Time = CurrentTime;
	PreviousTime = CurrentTime;
	StopTime = 0;
	Paused = false;
}


void TTime::Stop()
{
	if (!Paused)
	{
		QueryPerformanceCounter((LARGE_INTEGER*) &CurrentTime);
		StopTime = CurrentTime;
		Paused = true;
	}
}


void TTime::Start()
{
	int64 StartTime;
	QueryPerformanceCounter((LARGE_INTEGER*) &StartTime);
	if (Paused)
	{
		PausedTime += (StartTime - StopTime);
		PreviousTime = StartTime;
		StopTime = 0;
		Paused = false;
	}
}


float TTime::GetTotalTimeCounter() const
{
	if (Paused)
	{
		return (float)(((StopTime - PausedTime) - Time) * SecondsPerCount);
	}
	else
	{
		return (float)(((CurrentTime - PausedTime) - Time) * SecondsPerCount);
	}
}