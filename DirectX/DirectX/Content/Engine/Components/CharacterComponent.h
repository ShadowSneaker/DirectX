#pragma once
#include "Component.h"


class CCharacterComponent :public CComponent
{
public:
	/// Properties

	float MoveSpeed{ 500.0f };


public:
	/// Constructors

	CCharacterComponent(SComponentInfo Info);


	/// Fuctions

	void Move(SVector Direction, float Axis, bool ForceMove = false);
};