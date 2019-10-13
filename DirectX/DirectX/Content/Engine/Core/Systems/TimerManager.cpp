#include "TimerManager.h"
#include "Time.h"


CTimerManager::CTimerManager()
{}


CTimerManager::~CTimerManager()
{
	DeleteAllTimers();
}


void CTimerManager::Update()
{
	if (Active)
	{
		for (uint i = 0; i < Timers.size(); ++i)
		{
			if (Timers[i]->Object)
			{
				if (Timers[i]->Active)
				{
					if (Timers[i]->OnDelay)
					{
						if (Timers[i]->CurrentDelay > 0.0f)
						{
							Timers[i]->CurrentDelay -= TTime::DeltaTime;
							if (Timers[i]->TimerMethodFlags & (ETimerMethod::OnDelayUpdate))
							{
								Timers[i]->BoundFunction(ETimerMethod::OnDelayUpdate);
							}
						}
						else
						{
							Timers[i]->OnDelay = false;
							if (Timers[i]->TimerMethodFlags & (ETimerMethod::OnDelayEnd))
							{
								Timers[i]->BoundFunction(ETimerMethod::OnDelayEnd);
							}
						}
					}
					else
					{
						if (Timers[i]->CurrentTime > 0.0f)
						{
							Timers[i]->CurrentTime -= TTime::DeltaTime;
							if (Timers[i]->TimerMethodFlags & (ETimerMethod::OnUpdate))
							{
								Timers[i]->BoundFunction(ETimerMethod::OnUpdate);
							}
						}
						else
						{
							if (Timers[i]->TimerMethodFlags & (ETimerMethod::OnEnd))
							{
								Timers[i]->BoundFunction(ETimerMethod::OnEnd);
							}

							if (Timers[i]->RemoveOnFinish)
							{
								DeleteTimerIndex(i);
							}
							else
							{
								Timers[i]->Active = false;
							}
						}
					}
				}
			}
			else
			{
				// Remove timers if the object they are bound to is missing.
				DeleteTimerIndex(i);
			}
		}
	}
}


STimer* CTimerManager::AddTimer(class CWorldObject* Object, std::function<void(ETimerMethod)> Function, float Duration, const ETimerMethod TimerFlags, bool Loop, float Delay, bool Activate, bool RemoveOnFinish)
{
	STimer* Timer = new STimer{ Object, Function, Duration, Delay, TimerFlags, Loop, Activate, RemoveOnFinish };
	Timers.push_back(Timer);
	return Timer;
}


void CTimerManager::AddTimer(STimer* Timer)
{
	Timers.push_back(Timer);
}


void CTimerManager::ResetTimer(STimer* Timer, bool Activate)
{
	Timer->Active = Activate;
	Timer->CurrentDelay;
	Timer->CurrentTime = Timer->TotalDuration;
	Timer->OnDelay = (Timer->TotalDelay > 0.0f);
}


void CTimerManager::DeleteTimer(STimer* Timer)
{
	if (Timer)
	{
		for (uint i = 0; i < Timers.size(); ++i)
		{
			if (Timers[i] == Timer)
			{
				Timers.erase(Timers.begin() + i);
				break;
			}
		}
		delete Timer;
	}
}


void CTimerManager::DeleteTimerIndex(uint Index)
{
	if (Index < Timers.size())
	{
		delete Timers[Index];
		Timers.erase(Timers.begin() + Index);
	}
}


void CTimerManager::DeleteAllTimers()
{
	while (!Timers.empty())
	{
		delete Timers[Timers.size() - 1];
		Timers.pop_back();
	}
}