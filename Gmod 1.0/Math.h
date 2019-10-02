#pragma once
#include <cmath>
#include "Vector.h"


class Math
{
public:
	float GetDistanceBetween(Vector LocalPlayerCoordinates, Vector EnemyPlayerCoordinates);

	Vector CalcAngle(Vector LocalPlayerOrigin, Vector EnemyPlayerOrigin);
};