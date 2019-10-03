#pragma once
#include "Interface.h"
#include "Math.h"
#include <iostream>

#define PI 3.1415926535897


class aimbot
{
public:
	Math oMath;

	float RealDifference, DistanceToEnt;
	float MaxDiff = 9999999.0f;
	
	DWORD engine = (DWORD)GetModuleHandle("engine.dll");

	Vector LocalPlayerOrg, CurrentEntOrg, AngleToAim, CurrenEntBonePos, vHeadPos;

	matrix3x4_t bonePos[128];
	
	float* Pitch = (float*)(engine + 0x4E16E4);
	float* Yaw = (float*)(engine + 0x4E16E8);

	void StartAim();
	int GetBestEntity();

	void GetEnemyBonePos(IClientEntity* Entity);
	bool CheckIfValid(IClientEntity* CurrentEntity);

	

};

