#include "Interface.h"


IClientEntityList* CInterfaces::pEntityList;
IEngineClient* CInterfaces::pEngine;

void CCreateInterface::Initialize()
{
	auto clientFactory = GetModuleFactory(GetModuleHandle("client.dll"));
	auto engineFactory = GetModuleFactory(GetModuleHandle("engine.dll"));

	CInterfaces::pEntityList = GetInterface<IClientEntityList*>(clientFactory, "VClientEntityList003");
	CInterfaces::pEngine = GetInterface<IEngineClient*>(engineFactory, "VEngineClient013");

}

