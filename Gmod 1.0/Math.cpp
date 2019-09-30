#include "Math.h"

Vec3 Math::CalcAngle(Vec3 LocalPlayerOrigin, Vec3 EnemyPlayerOrigin)
{
	Vec3 Difference;
	Difference.x = EnemyPlayerOrigin.x - LocalPlayerOrigin.x;
	Difference.y = EnemyPlayerOrigin.y - LocalPlayerOrigin.y;
	Difference.z = EnemyPlayerOrigin.z - LocalPlayerOrigin.z;


	float magnitude = sqrt(pow(Difference.x, 2) + pow(Difference.y, 2) + pow(Difference.z, 2));

	Vec3 AngleToAim;

	AngleToAim.y = atan2(Difference.y, Difference.x) * 180 / 3.14;

	AngleToAim.x = -asin(Difference.z / magnitude) * 180 / 3.14;

	
	AngleToAim.z = 0.0f;



	return AngleToAim;
}
