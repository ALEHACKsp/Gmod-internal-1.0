#pragma once
#include <Windows.h>


class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	char* m_pNetworkName;
	void* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class IClientNetworkable
{
public:
	virtual void*			GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass*	GetClientClass() = 0;// FOR NETVARS FIND YOURSELF ClientClass* stuffs
	virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/) = 0;
	virtual void			OnPreDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			OnDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			PreDataUpdate( /*DataUpdateType_t*/ int updateType) = 0;
	virtual void			PostDataUpdate( /*DataUpdateType_t updateType*/) = 0;
	virtual bool			IsDormant(void) = 0;
	virtual int				GetIndex(void) const = 0;
	virtual void			ReceiveMessage(int classID /*, bf_read &msg*/) = 0;
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;
	virtual void			OnDataUnchangedInPVS() = 0;
};

class IClientEntity : public IClientNetworkable
{
public:
	virtual ~IClientEntity();

};


class IClientEntityList
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void* GetClientEntity(int i); //index of entity, returns ptr to entity base
	virtual void* GetClientEntityFromHandle(HANDLE hEnt); //eg for obtaining weapons from handles
	virtual int NumberOfEntities(bool bIncludeNonNetworkable);
	virtual int GetHighestEntityIndex(void);
	virtual void SetMaxEntities(int n);
	virtual int GetMaxEntities();
};
