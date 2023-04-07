#pragma once

#include "etypes.h"
#include "ComponentPack.h"
#include "IDManager.h"

namespace necs
{

	class Scene
	{
	public:
		Scene() : mIDManager{} {};

		Entity CreateEntity()
		{
			return mIDManager.Create();
		}

		void DestroyEntity(const Entity& id)
		{
			mIDManager.Destroy(id);
			mSignatures.at(id).reset();
			for (ComponentTypeID i{ 0 }; i < GComponentTypesRegistered; i++)
			{
				if (mPacks.at(i) != nullptr)
				{
					mPacks.at(i)->Destroy(id);
				}
			}
		}

		template<typename T, typename... Ar>
		T& Attach(const Entity& id, Ar... params)
		{
			ComponentTypeID cid{ GetComponentTypeID<T>() };
			if (mPacks.size() <= cid)
			{
				mPacks.resize(cid);
				mPacks.push_back(MakeShared<ComponentPack<T>>());
			}

			if (mSignatures.size() <= id)
			{
				mSignatures.resize(id);
			}
			mSignatures.push_back(0);
			mSignatures.at(id).set(cid);

			Shared<ComponentPack<T>> pack{ std::static_pointer_cast<ComponentPack<T>>(mPacks.at(cid)) };
			pack->Add(id, std::forward<Ar>(params)...);
			return pack->Get(id);
		}

		template<typename T>
		void Detach(const Entity& id)
		{
			ComponentTypeID cid{ GetComponentTypeID<T>() };
			if (mPacks.size() <= cid)
				return;

			mSignatures.at(id).reset(cid);
			Shared<ComponentPack<T>> pack{ std::static_pointer_cast<ComponentPack<T>>(mPacks.at(cid)) };
			pack->Destroy(id);
		}

		template<typename T>
		T& Get(const Entity& id)
		{
			ComponentTypeID cid{ GetComponentTypeID<T>() };
			if (mPacks.size() <= cid)
				assert(false && "Pack no exists honey");
			return (std::static_pointer_cast<ComponentPack<T>>(mPacks.at(cid)))->Get(id);
		}

		template<typename T>
		bool HasAttached(const Entity& id)
		{

		}

	protected:
		std::vector<Shared<AComponentPack>> mPacks;
		std::vector<Signature> mSignatures;
		IDManager mIDManager;
	};

}
