#include <iostream>
#include <Windows.h>
#include "Aimbot.h"



int main()
{
	FILE* pFile = nullptr;
	AllocConsole();
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	aimbot oAim;

	int health = 0;
	CCreateInterface::GetInstance().Initialize();
	while (true) 
	{
		/*for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
		{
			IClientEntity* pEntity = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);
			IClientEntity* pLocalPlayer = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(CInterfaces::pEngine->GetLocalPlayer());
			if (pEntity == nullptr)
				continue;

			if (pLocalPlayer == nullptr)
				continue;

			int PoopID = pEntity->GetClientClass()->m_ClassID;
			poop = *(vec3*)(((uintptr_t)pLocalPlayer + 0x260));

			health = *(int*)(((uintptr_t)pEntity + 0x90));

			std::cout << "=================================\n";

			std::cout << "Current Entity: " << i << "\n\n";
			std::cout << "Current Entity Health: " << health << "\n\n";
			std::cout << "ClassID: " << PoopID << "\n\n";

			std::cout << "LocalPlayer X: " << poop.x << "\n\n";


			std::cout << "=================================\n";

			Sleep(1000);
		}*/


		oAim.StartAim();


	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
