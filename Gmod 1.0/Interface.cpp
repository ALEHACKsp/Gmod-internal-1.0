#include "Interface.h"


IClientEntityList* CInterfaces::pEntityList;

void CCreateInterface::Initialize()
{
	auto clientFactory = GetModuleFactory(GetModuleHandle("client.dll"));
	auto engineFactory = GetModuleFactory(GetModuleHandle("engine.dll"));

	CInterfaces::pEntityList = GetInterface<IClientEntityList*>(clientFactory, "VClientEntityList003");
}

