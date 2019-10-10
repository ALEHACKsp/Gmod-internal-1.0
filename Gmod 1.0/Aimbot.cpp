#include "Aimbot.h"


void aimbot::StartAim()
{
	int Health;
	int BestEntityFound = 0;
	Vector Buns;
	while (GetAsyncKeyState(VK_XBUTTON2))
	{
		BestEntityFound = GetBestEntity();
		IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
		IClientEntity* pCurrentEntity = CInterfaces::pEntityList->GetClientEntity(BestEntityFound);

		if (pCurrentEntity != nullptr)
		{
			bool test = GetHitBox(pCurrentEntity, Buns, boneArray[12]);
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

		RealDifference = oMath.GetDistanceBetween(LocalPlayerOrg, CurrentEntOrg);

		if (RealDifference < MaxDiff)
		{
			MaxDiff = RealDifference;
			BestEnt = i;
		}
	}
	return BestEnt;
}


void aimbot::GetEnemyBonePos(IClientEntity* Entity)
{
	Entity->SetupBones(bonePos, 128, 0x00000100, 0.0f);

	matrix3x4_t Hitbox = bonePos[6];

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

bool aimbot::GetHitBox(IClientEntity* Entity, Vector vecHitbox, const char* cBoneName)
{

	matrix3x4_t pMatrix[128];

	Entity->SetupBones(pMatrix, 128, 0x00000100, 0.0f);

	auto pStudioHdr = CInterfaces::pModelInfo->GetStudioModel(Entity->GetModel());

	if (!pStudioHdr)
		return false;

	auto pSet = pStudioHdr->pHitboxSet(0);

	if (pSet)
	{
		for (auto i = 0; i < pSet->numhitboxes; i++)
		{

			auto pHitBox = pSet->pHitbox(i);

			if (pHitBox)
			{
				auto cHitBox = pStudioHdr->pBone(pHitBox->bone)->pszName();
				Vector vecMin, vecMax;

				std::cout << "Current pBone Name: " << cHitBox << "\n";
				std::cout << "pHitboxBone: " << pHitBox->bone << "\n";
				return true;
			}
		}
	}
	return true;
}


