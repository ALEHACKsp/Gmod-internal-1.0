#pragma once
#include "Interface.h"
#include "Math.h"



class aimbot
{
public:
	Math oMath;
	float CurrentDistance = 99999.0f;
	float DistanceTo;
	IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
	
	DWORD engine = (DWORD)GetModuleHandle("engine.dll");

	Vec3 LocalPlayerOrigin;
	Vec3 CurrentEntityOrigin;
	Vec3 AngleToAim;
	
	float* Pitch = (float*)(engine + 0x4E16E4);
	float* Yaw = (float*)(engine + 0x4E16E8);

	void StartAim();
	IClientEntity* GetBestTarget();
	bool CheckIfValid(IClientEntity* CurrentEntity);

	

};

