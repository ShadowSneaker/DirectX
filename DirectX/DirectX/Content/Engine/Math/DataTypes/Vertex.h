#pragma once
//#define _XM_NO_INTRINSICS_
//#define XM_NO_ALIGNMENT
//#include <xnamath.h>
#include "../DataTypes/Vector.h"


//struct SVertexBase
//{
//	SVector Position;
//	SVector4 Colour;
//};


//struct SModelVertex
//{
//	SVector Position;
//	SVector4 Colour;
//	SVector2 UV;
//};


struct SVertex
{
	SVector Position;
	SVector4 Colour;
	SVector2 UV;
	SVector Normal;
};