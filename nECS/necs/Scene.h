#pragma once

#include "etypes.h"
#include "CPack.h"
#include "IDHandler.h"

namespace necs
{

	class Scene
	{
	public:
		Scene() : mIDManager{} {};
		Entity CreateEntity();
		void DestroyEntity(const Entity& id);
	protected:
		// Make sure the Signature exists and create one if not
		Signature& ValidateSignature(const Entity& id);

		// Make sure a component pack is available and return the type id
		template<typename T>
		ComponentTypeID ValidatePack()
		{
			ComponentTypeID cid{ GetComponentTypeID<T>() };
			if (mPacks.size() <= cid)
			{
				mPacks.resize(cid);
				mPacks.push_back(MakeShared<ComponentPack<T>>());
			}
			else if (mPacks.at(cid) == nullptr)
			{
				mPacks.at(cid) = MakeShared<ComponentPack<T>>();
			}
			return cid;
		}
	public:
		template<typename T>
		T& Attach(const Entity& id)
		{
			ComponentTypeID cid{ ValidatePack<T>() };
			Signature& sig{ ValidateSignature(id) };
			sig.set(cid);
			Shared<ComponentPack<T>> pack{ std::static_pointer_cast<ComponentPack<T>>(mPacks.at(cid)) };
			return pack->Add(id);
		}

		template<typename T>
		T& Attach(const Entity& id, const T& other)
		{
			ComponentTypeID cid{ ValidatePack<T>() };

			Signature& sig{ ValidateSignature(id) };
			sig.set(cid);

			Shared<ComponentPack<T>> pack{ std::static_pointer_cast<ComponentPack<T>>(mPacks.at(cid)) };
			pack->Add(id, other);
			return pack->Get(id);
		}

		template<typename T>
		T& Attach(const Entity& id, std::initializer_list<T>&& initializer_list)
		{
			ComponentTypeID cid{ ValidatePack<T>() };
			Signature& sig{ ValidateSignature(id) };
			sig.set(cid);

			//error here most likely means the initializer list you gave doesn't match any of the components contructors
			Shared<ComponentPack<T>> pack{ static_cast<Shared<ComponentPack<T>>>(mPacks.at(cid)) };
			return pack->Add(id, std::forward<std::initializer_list<T>>(initializer_list));
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
		T& GetComponent(const Entity& id)
		{
			ComponentTypeID cid{ GetComponentTypeID<T>() };
			if (mPacks.size() <= cid)
				assert(false && "Pack no exists honey");
			return (std::static_pointer_cast<ComponentPack<T>>(mPacks.at(cid)))->Get(id);
		}

		template<typename T>
		bool HasComponent(const Entity& id)
		{
			ComponentTypeID cid{ GetComponentTypeID<T>() };
			if (mPacks.size() <= cid)
				assert(false && "Pack no exists honey");
			return mSignatures.at(id).test(cid);
		}

		std::vector<Signature>& GetSignatures()
		{
			return mSignatures;
		}

		IDHandler& GetIDHandler()
		{
			return mIDManager;
		}

	protected:
		std::vector<Shared<AComponentPack>> mPacks;
		std::vector<Signature> mSignatures;
		IDHandler mIDManager;
	};

	template<typename... T>
	class SceneView
	{
	public:
		SceneView(Shared<Scene>& scene)
		{
			static_assert(sizeof...(T) > 0, "Must have at least 1 component in scene view");

			ComponentTypeID ids[]{ GetComponentTypeID<T>()... };
			for (ComponentTypeID i : ids)
			{
				mSignature.set(i);
			}

			const std::vector<Signature>& sigs{ scene->GetSignatures() };
			for (Entity i : scene->GetIDHandler())
			{
				if ((mSignature & (sigs.at(i))) == mSignature)
				{
					mEntities.push_back(i);
				}
			}
		}
		SceneView(Scene& scene)
		{
			static_assert(sizeof...(T) > 0, "Must have at least 1 component in scene view");

			ComponentTypeID ids[]{ GetComponentTypeID<T>()... };
			for (ComponentTypeID i : ids)
			{
				mSignature.set(i);
			}

			const std::vector<Signature>& sigs{ scene.GetSignatures() };
			for (Entity i : scene.GetIDHandler())
			{
				if ((mSignature & (sigs.at(i))) == mSignature)
				{
					mEntities.push_back(i);
				}
			}
		}
	public:
		const std::vector<Entity>::const_iterator begin() const { return mEntities.begin(); }
		const std::vector<Entity>::const_iterator end() const { return mEntities.end(); }
	protected:
		std::vector<Entity> mEntities;
		Signature mSignature;
	};

}
