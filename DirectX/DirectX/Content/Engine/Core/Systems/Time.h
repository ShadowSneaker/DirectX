#pragma once
#include "../../Math/MathValues.h"

// http://aranna.altervista.org/data2/3d_game_programming_with_DirectX11.pdf


class TTime
{
public:
	// 
	static float DeltaTime;

	// 
	static float TimeScale;

private:
	/// Properties
	float SecondsPerCount{ 0.0f };

	int64 Time{ 0 };
	int64 PausedTime{ 0 };
	int64 StopTime{ 0 };
	int64 PreviousTime{ 0 };
	int64 CurrentTime{ 0 };

	bool Paused{ false };


public:
	/// Constructors
	TTime();
	
	/// Functions


	void Update();

	void Reset();

	void Start();

	void Stop();


	/// Getters

	float GetTotalTimeCounter() const;
};