#include "Aimbot.h"



void aimbot::StartAim()
{
	while (GetAsyncKeyState(VK_XBUTTON2))
	{

		IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
		IClientEntity* Entity = GetBestFOV();
		

		if (Entity != nullptr)
		{
			GetEnemyBonePos(Entity);
			AngleToAim = oMath.CalcAngle(LocalPlayerOrigin, vecHead);

			*Pitch = AngleToAim.x;
			*Yaw = AngleToAim.y;
		}
	}
}

/*IClientEntity* aimbot::GetBestTarget()
{
	CurrentDistance = 9999999.0f;
	IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
	IClientEntity* BestEntity = 0;

	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pEntity = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (pEntity == pLocalPlayer)
			continue;

		if (!CheckIfValid(pEntity))
			continue;

		LocalPlayerOrigin = *(Vec3*)(((uintptr_t)pLocalPlayer + 0x260));
		CurrentEntityOrigin = *(Vec3*)(((uintptr_t)pEntity + 0x260));

		DistanceTo = oMath.GetDistanceBetween(LocalPlayerOrigin, CurrentEntityOrigin);

		if (DistanceTo < CurrentDistance)
		{
			CurrentDistance = DistanceTo;

			BestEntity = pEntity;
		}
	}

	return BestEntity;
}
*/


IClientEntity* aimbot::GetBestFOV()
{
	MaxDiff = 9999999.0f;
	IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
	IClientEntity* BestEntity = 0;

	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pEntity = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (pEntity == pLocalPlayer)
			continue;

		if (!CheckIfValid(pEntity))
			continue;

		LocalPlayerOrigin = *(Vec3*)(((uintptr_t)pLocalPlayer + 0x260));
		CurrentEntityOrigin = *(Vec3*)(((uintptr_t)pEntity + 0x260));

		vecEnemyOrg.x = CurrentEntityOrigin.x;
		vecEnemyOrg.y = CurrentEntityOrigin.y;
		vecEnemyOrg.z = CurrentEntityOrigin.z;

		AngleToAim = oMath.CalcAngle(LocalPlayerOrigin, vecEnemyOrg);

		YawDiff = (*Yaw - AngleToAim.y);

		YawDiff = fabsf(YawDiff);

		if (YawDiff > 10.0f)
			continue;

		DistanceTo = oMath.GetDistanceBetween(LocalPlayerOrigin, CurrentEntityOrigin);

		RealDiff = sin((YawDiff * 3.14 / 180)) * DistanceTo;


		if (RealDiff < MaxDiff)
		{
			MaxDiff = RealDiff;

			BestEntity = pEntity;
		}
	}

	return BestEntity;
}

void aimbot::GetEnemyBonePos(IClientEntity* Entity)
{
	Entity->SetupBones(bonePos, 128, 256, 0.0f);

	matrix3x4_t Hitbox = bonePos[7];

	vecHead.x = Hitbox[0][3];
	vecHead.y = Hitbox[1][3];
	vecHead.z = Hitbox[2][3];


}


bool aimbot::CheckIfValid(IClientEntity* CurrentEntity)
{
	if (CurrentEntity == nullptr)
		return false;

	if (CurrentEntity->IsDormant())
		return false;

	int health = *(int*)(((uintptr_t)CurrentEntity + 0x90));

	if (!health)
		return false;

	if (CurrentEntity->GetClientClass()->m_ClassID != 69)
		return false;

	return true;
}
