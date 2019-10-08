#include "Aimbot.h"


void aimbot::StartAim()
{
	int Health;
	int BestEntityFound = 0;
	while (GetAsyncKeyState(VK_XBUTTON2))
	{
		BestEntityFound = GetBestEntity();
		IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
		IClientEntity* pCurrentEntity = CInterfaces::pEntityList->GetClientEntity(BestEntityFound);

		if (pCurrentEntity != nullptr)
		{
			GetEnemyBonePos(pCurrentEntity);
			AngleToAim = oMath.CalcAngle(LocalPlayerOrg, vHeadPos);

			*Pitch = AngleToAim.x;
			*Yaw = AngleToAim.y;
		}
	}
}


int aimbot::GetBestEntity()
{
	MaxDiff = 9999999.0f;
	IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
	int BestEnt = 0;
	for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pCurrentEnt = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

		if (!CheckIfValid(pCurrentEnt))
			continue;

		if (pCurrentEnt == pLocalPlayer)
			continue;

		LocalPlayerOrg = *(Vector*)(((uintptr_t)pLocalPlayer + 0x260));
		CurrentEntOrg = *(Vector*)(((uintptr_t)pCurrentEnt + 0x260));

		AngleToAim = oMath.CalcAngle(LocalPlayerOrg, CurrentEntOrg);

		RealDifference = oMath.GetDistAngles(Yaw, Pitch, AngleToAim);

		if (RealDifference > 10.f)
			continue;

		if (RealDifference < MaxDiff)
		{
			MaxDiff = RealDifference;
			BestEnt = i;
		}
	}
	return BestEnt;
}

/*IClientEntity* aimbot::GetBestFOV()
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

		LocalPlayerOrigin = *(Vector*)(((uintptr_t)pLocalPlayer + 0x260));
		CurrentEntityOrigin = *(Vector*)(((uintptr_t)pEntity + 0x260));


		AngleToAim = oMath.CalcAngle(LocalPlayerOrigin, CurrentEntityOrigin);

		YawDiff = (*Yaw - AngleToAim.y);
		PitchDiff = (*Pitch - AngleToAim.x);

		YawDiff = fabsf(YawDiff);
		PitchDiff = fabsf(PitchDiff);

		if (YawDiff > 10.0f || PitchDiff > 10.0f)
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
*/
void aimbot::GetEnemyBonePos(IClientEntity* Entity)
{
	Entity->SetupBones(bonePos, 128, 0x00000100, 0.0f);

	matrix3x4_t Hitbox = bonePos[7];

	vHeadPos.x = Hitbox[0][3];
	vHeadPos.y = Hitbox[1][3];
	vHeadPos.z = Hitbox[2][3];

}


bool aimbot::CheckIfValid(IClientEntity* CurrentEntity)
{
	if (CurrentEntity == nullptr)
		return false;

	if (CurrentEntity->IsDormant())
		return false;

	int health = *(int*)(((uintptr_t)CurrentEntity + 0x90));

	if (health < 1)
		return false;

	if (CurrentEntity->GetClientClass()->m_ClassID != 69)
		return false;

	return true;
}
