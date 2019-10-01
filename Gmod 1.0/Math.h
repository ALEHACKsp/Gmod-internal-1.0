#pragma once
#include <cmath>

struct Vec3
{
	float x, y, z;
};

class Math
{
public:
	float GetDistanceBetween(Vec3 LocalPlayerCoordinates, Vec3 EnemyPlayerCoordinates);
	Vec3 CalcAngle(Vec3 LocalPlayerOrigin, Vec3 EnemyPlayerOrigin);

	
};