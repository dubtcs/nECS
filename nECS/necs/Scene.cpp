
#include "Scene.h"

#include <iostream>

namespace necs
{

	Entity Scene::CreateEntity()
	{
		Entity id{ mIDManager.Create() };

		if (mSignatures.size() <= id)
		{
			mSignatures.resize(id);
			mSignatures.push_back(0);
		}

		return id;
	}

	void Scene::DestroyEntity(const Entity& id)
	{
		mIDManager.Destroy(id);
		mSignatures.at(id).reset();
		for (ComponentTypeID i{ 0 }; i < globals::gComponentTypesRegistered; i++)
		{
			if (mPacks.at(i) != nullptr)
			{
				mPacks.at(i)->Destroy(id);
			}
		}
	}

	// Make sure the Signature exists and create one if not
	Signature& Scene::ValidateSignature(const Entity& id)
	{
		if (mSignatures.size() <= id)
		{
			mSignatures.resize(id);
			mSignatures.push_back(0);
		}
		return mSignatures.at(id);
	}

}
