#include "Aimbot.h"


void aimbot::StartAim()
{
	IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());

	if (!pLocalPlayer)
		return;



	if (GetAsyncKeyState(VK_XBUTTON2))
	{
		for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
		{
			IClientEntity* pEntity = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

			if (!pEntity)
				continue;

			if (pEntity == pLocalPlayer)
				continue;

			if (pEntity->GetClientClass()->m_ClassID != 69)
				continue;

			LocalPlayerOrigin = *(Vec3*)(((uintptr_t)pLocalPlayer + 0x260));

			CurrentEntityOrigin = *(Vec3*)(((uintptr_t)pEntity + 0x260));

			AngleToAim = oMath.CalcAngle(LocalPlayerOrigin, CurrentEntityOrigin);


			*pitch = AngleToAim.x;
			*Yaw = AngleToAim.y;



		}
	}

	// calc angle here


}
