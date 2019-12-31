#pragma once
#include "../../Math/MathValues.h"
#include "Time.h"

#include <functional>
#include <vector>


enum ETimerMethod
{
	OnEnd = 0x00000000,			// Runs once when the timer hits 0.
	OnDelayEnd = 0x00000001,	// Runs once when the delay hits 0.
	OnUpdate = 0x00000002,		// Runs every loop until the timer hits 0 (Only runs when not on delay).
	OnDelayUpdate = 0x00000004,	// Runs every loop until the delay hits 0.
};


// To use multiple types do ETimerMethod(OnEnd | OnUpdate | OnDelayEnd | OnDelayUpdate)



// A timer struct that will countdown until it hits zero.
// Note, this struct is just stores the information for a timer
// it does not do the countdown locally. use CTimerManager to
// start the timer.
struct STimer
{
public:
	/// Properties

	// The current time this timer has left.
	float CurrentTime{ 0.0f };

	// The amount of time this timer was assgned with.
	float TotalDuration{ 0.0f };

	// The current time this timer will be delayed for.
	float CurrentDelay{ 0.0f };

	// The amount of delay this timer was assigned with.
	float TotalDelay{ 0.0f };

	// A reference to the object this timer is ran on.
	class CWorldObject* Object{ nullptr };

	// The flags used to determine when the delegated function should be called.
	const ETimerMethod TimerMethodFlags{ ETimerMethod::OnEnd };

	// Enabled when the timer is currently delayed.
	bool OnDelay{ false };

	// Determines if this timer is active.
	bool Active{ false };

	// Should this timer be deleted when it reaches 0.
	bool RemoveOnFinish{ true };

	// Should this timer loop constantly.
	// When the timer reaches 0, it restarts.
	bool Loop{ false };

	// The function this timer should run when it finishes.
	std::function<void(const ETimerMethod)> BoundFunction{ NULL };


public:
	/// Constructors

	// Constructor, Default.
	STimer() {}


	// Constructor, Initiates all properties of the timer.
	// @param Function - The assigned function to call.
	// @param Duration - How long the timer will be running for.
	// @param Delay - How long this timer should wait before starting the countdown.
	// @param TimerFlags - Flags used to determine when to call the bound function.
	// @param Activate - Should the timer be created active.
	// @param ShouldRemoveOnFinish - Determines if this timer should be removed from the list when it reaches 0.
	STimer(class CWorldObject* BoundObject, std::function<void(const ETimerMethod)> Function, float Duration, float Delay, const ETimerMethod TimerFlags, bool SetLoop, bool Activate, bool ShouldRemoveOnFinish)
		:CurrentTime{ Duration }, TotalDuration{ Duration }, CurrentDelay{ Delay }, TotalDelay{ Delay }, Object{ BoundObject },
		TimerMethodFlags{ TimerFlags }, Loop{ SetLoop }, Active{ Activate }, RemoveOnFinish{ ShouldRemoveOnFinish }, BoundFunction{ Function }
	{
		OnDelay = (TotalDelay > 0.0f);
	}
};


// Manages all the timers in the world.
// Timers will call a bound function when they reach
// their specified timer method.
class CTimerManager
{
private:
	/// Properties

	// A list of all the stored timers.
	std::vector<STimer*> Timers;

public:
	// Allows the update function to run.
	bool Active{ true };



public:
	/// Constructors

	// Constructor, Initiates the timer manager.
	CTimerManager();

	// Destructor.
	~CTimerManager();


private:
	/// Functions.

	// Deletes a timer from the manager based on an index.
	// @param Index - The index of the timer to remove.
	void DeleteTimerIndex(uint Index);

	// Delets all the timers from the manager.
	void DeleteAllTimers();

public:
	// Updates all the timers in this manager.
	void Update();

	// Creates and adds a timer to the timer manager.
	// @param Object - The object this timer is bound to.
	// @param Function - The function the timer should call when it finishes.
	// @param Duration - How long the timer will be running.
	// @param Delay - How long the timer should delay before running.
	// @param ShouldRemoveOnFinish - If true, removes the timer when it hits 0.
	// @return - The reference to the created timer.
	STimer* AddTimer(class CWorldObject* Object, std::function<void(ETimerMethod)> Function, float Duration, const ETimerMethod TimerMethod, bool Loop = true, float Delay = 0.0f, bool Activate = true, bool RemoveOnFinish = true);

	// Adds a pre-created timer to the timer manager.
	// Note: These timers need to be setup before added.
	// @param Timer - The reference to the timer to add.
	void AddTimer(STimer* Timer);

	// Resets all the values of the timer to its origional starting position.
	// @param Timer - A reference to the timer to reset.
	// @param Activate - Should the timer be activated after being reset.
	void ResetTimer(STimer* Timer, bool Activate = true);

	// Deletes a specified timer from the manager.
	// @param Timer - A reference to the timer to be deleted.
	void DeleteTimer(STimer* Timer);
};
