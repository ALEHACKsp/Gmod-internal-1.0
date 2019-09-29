#include <iostream>
#include "Interface.h"





int main()
{
	FILE* pFile = nullptr;
	AllocConsole();
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	CCreateInterface::GetInstance().Initialize();

	int health;
	while (true) {
		for (int i = 0; i < CInterfaces::pEntityList->GetHighestEntityIndex(); i++)
		{
			IClientEntity* pEntity = (IClientEntity*)CInterfaces::pEntityList->GetClientEntity(i);

			if (pEntity == nullptr)
				continue;


			health = *(int*)(((uintptr_t)pEntity + 0x90));

			std::cout << "=================================\n";

			std::cout << "Current Entity: " << i << "\n\n";
			std::cout << "Current Entity Health: " << health << "\n\n";

			std::cout << "=================================\n";

			Sleep(1000);
		}
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
