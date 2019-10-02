#pragma once
#include "Interface.h"
#include "Math.h"
#include <iostream>


class aimbot
{
public:
	Math oMath;
	float DistanceTo;

	float YawDiff;
	float RealDiff;
	float MaxDiff = 9999999.0f;
	
	DWORD engine = (DWORD)GetModuleHandle("engine.dll");

	Vec3 LocalPlayerOrigin;
	Vec3 CurrentEntityOrigin;
	Vec3 AngleToAim;
	Vec3 EntBonePos;

	Vector vecHead;
	Vector vecEnemyOrg;

	matrix3x4_t bonePos[128];
	
	float* Pitch = (float*)(engine + 0x4E16E4);
	float* Yaw = (float*)(engine + 0x4E16E8);

	void StartAim();
	//IClientEntity* GetBestTarget();
	IClientEntity* GetBestFOV();
	void GetEnemyBonePos(IClientEntity* Entity);
	bool CheckIfValid(IClientEntity* CurrentEntity);

	

};

