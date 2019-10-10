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
	int aimbone;
	matrix3x4_t pMatrix[128];

	Entity->SetupBones(pMatrix, 128, 0x00000100, 0.0f);

	auto pStudioModel = CInterfaces::pModelInfo->GetStudioModel(Entity->GetModel());

	if (!pStudioModel)
		return false;

	auto set = pStudioModel->pHitboxSet(0);

	if (!set)
		return false;

	for (int c = 0; c < set->numhitboxes; c++)
	{
		auto pHitBox = set->pHitbox(c);

		if (!pHitBox)
			return false;

		auto cHitBoxName = pStudioModel->pBone(pHitBox->bone)->pszName();


		if (cBoneName && strstr(cHitBoxName, cBoneName))
		{
			aimbone = pHitBox->bone;

			std::cout << "CBone name matches: " << cHitBoxName;
			std::cout << "Bone ID: " << aimbone << "\n";
		}	
	}

	return true;
}

