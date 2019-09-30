#pragma once
#include "Interface.h"
#include "Math.h"



class aimbot
{
public:
	Math oMath;

	Vec3 LocalPlayerOrigin;
	Vec3 CurrentEntityOrigin;
	Vec3 AngleToAim;
	
	DWORD engine = (DWORD)GetModuleHandle("engine.dll");


	float* pitch = (float*)(engine + 0x4E16E4);
	float* Yaw = (float*)(engine + 0x4E16E8);
	void StartAim();

};

