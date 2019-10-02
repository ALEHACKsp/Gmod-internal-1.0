#pragma once
#include <cmath>
#include "Vector.h"

struct Vec3
{
	float x, y, z;
};

class Math
{
public:
	float GetDistanceBetween(Vec3 LocalPlayerCoordinates, Vec3 EnemyPlayerCoordinates);

	Vec3 CalcAngle(Vec3 LocalPlayerOrigin, Vector EnemyPlayerOrigin);

	
};