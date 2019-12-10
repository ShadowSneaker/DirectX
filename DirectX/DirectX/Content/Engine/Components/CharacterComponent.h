#pragma once
#include "Component.h"


enum class EMovementType
{
	Walking,
	Running,
	Sprinting,
	Flying,
	Swimming
};


class CCharacterComponent :public CComponent
{
public:
	/// Properties

	EMovementType MovementType{ EMovementType::Running };

	float MoveSpeed{ 500.0f };


public:
	/// Constructors

	CCharacterComponent(SComponentInfo Info);


	/// Fuctions

	void Move(SVector Direction, float Axis, bool ForceMove = false);
};