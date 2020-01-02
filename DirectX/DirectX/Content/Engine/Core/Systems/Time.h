#pragma once
#include "../../Math/MathValues.h"

// http://aranna.altervista.org/data2/3d_game_programming_with_DirectX11.pdf


// Stores various values related to time.
class TTime
{
public:
	/// Static Properties

	// The amount of time between this frame and the last frame (in microseconds).
	static float DeltaTime;

	// Determines the scale of DeltaTime.
	static float TimeScale;



private:
	/// Properties

	// How many seconds per frame counter.
	float SecondsPerCount{ 0.0f };

	// The amount of time that has elapsed during runtime.
	int64 Time{ 0 };

	// The time that the program was at when it is paused.
	int64 PausedTime{ 0 };

	// The time the program stopped at.
	int64 StopTime{ 0 };

	// THe previous time.
	int64 PreviousTime{ 0 };

	// The current time.
	int64 CurrentTime{ 0 };

	// Represents when this time class is paused.
	bool Paused{ false };



public:
	/// Constructors
	
	// Constructor, Default.
	TTime();
	
	
	
	/// Functions

	// Calculates the value of deltatime.
	void Update();

	// Resets this object to 0.
	void Reset();

	// Resumes the time class.
	void Start();

	// Pauses the time class.
	void Stop();



	/// Getters

	// Returns the time couter.
	float GetTotalTimeCounter() const;
};