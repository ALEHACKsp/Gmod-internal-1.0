#pragma once
#include <Windows.h>

class IClientNetworkable;


typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);


class IClientThinkable
{
public:
	virtual ~IClientThinkable() {};
};

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}

	virtual void SetRefEHandle() = 0;
	virtual void GetRefEHandle() const = 0;
};

class ICollideable
{
public:
	virtual IHandleEntity* GetEntityHandle() = 0;
	virtual const void*& OBBMinsPreScaled() const = 0;
	virtual const void*& OBBMaxsPreScaled() const = 0;
	virtual const void*& OBBMins() const = 0;
	virtual const void*& OBBMaxs() const = 0;
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable* GetCollideable() = 0;
};


struct model_t
{
	char name[255];
};

class IPVSNotify
{
public:
	virtual void OnPVSStatusChanged(bool bInPVS) = 0;
};

class IClientRenderable
{
public:
	virtual void* GetIClientUnknown() = 0;
	virtual void* const& GetRenderOrigin(void) = 0;
	virtual void* const& GetRenderAngles(void) = 0;
	virtual bool			    ShouldDraw(void) = 0;
	virtual bool			    IsTransparent(void) = 0;
	virtual bool			    UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool			    UsesFullFrameBufferTexture() = 0;
	virtual unsigned short	    GetShadowHandle() const = 0;
	virtual unsigned short& RenderHandle() = 0;
	virtual const void* GetModel() const = 0;
	virtual int				    DrawModel(int flags) = 0;
	virtual int				    GetBody() = 0;
	virtual void			    ComputeFxBlend() = 0;
	virtual int				    GetFxBlend(void) = 0;
	virtual void			    GetColorModulation(float* color) = 0;
	virtual bool			    LODTest() = 0;
	virtual bool			    SetupBones(void* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void			    SetupWeights(const void* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void			    DoAnimationEvents(void) = 0;
	virtual IPVSNotify* GetPVSNotifyInterface() = 0;
	virtual void			    GetRenderBounds(void*& mins, void*& maxs) = 0;
	virtual void			    GetRenderBoundsWorldspace(void*& mins, void*& maxs) = 0;
	virtual void			    GetShadowRenderBounds(void*& mins, void*& maxs, unsigned short shadowType) = 0;
	virtual bool			    ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool			    GetShadowCastDistance(float* pDist, unsigned short shadowType) const = 0;
	virtual bool			    GetShadowCastDirection(void** pDirection, unsigned short shadowType) const = 0;
	virtual bool			    IsShadowDirty() = 0;
	virtual void			    MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable* GetShadowParent() = 0;
	virtual IClientRenderable* FirstShadowChild() = 0;
	virtual IClientRenderable* NextShadowPeer() = 0;
	virtual unsigned short		ShadowCastType() = 0;
	virtual void				CreateModelInstance() = 0;
	virtual unsigned short		GetModelInstance() = 0;
	virtual const void* RenderableToWorldTransform() = 0;
	virtual int					LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool				GetAttachment(int number, void* origin, void* angles) = 0;
	virtual bool				GetAttachment(int number, void* matrix) = 0;
	virtual float* GetRenderClipPlane(void) = 0;
	virtual int					GetSkin() = 0;
	virtual bool				IsTwoPass(void) = 0;
	virtual void				OnThreadedDrawSetup() = 0;
	virtual bool				UsesFlexDelayedWeights() = 0;
	virtual void				RecordToolMessage() = 0;
	virtual bool				IgnoresZBuffer(void) const = 0;
};

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

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
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
