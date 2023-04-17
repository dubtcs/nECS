#pragma once

#include "etypes.h"
#include <vector>
#include <array>
#include <unordered_map>

#include <assert.h>

namespace necs
{

	namespace globals
	{
		extern ComponentTypeID gComponentTypesRegistered;
	}

	template<typename T>
	ComponentTypeID GetComponentTypeID()
	{
		static ComponentTypeID sTypeID{ globals::gComponentTypesRegistered++ };
		return sTypeID;
	}

	class AComponentPack
	{
	public:
		AComponentPack() {};
		virtual ~AComponentPack() {};
		virtual void Destroy(Entity id) = 0;
	};

	template<typename T>
	class ComponentPack : public AComponentPack
	{
	public:
		ComponentPack() :
			mData{ MakeShared<std::vector<T>>() },
			mIndexToEntity{ MakeShared<std::vector<Entity>>() },
			mEntityToIndex{ MakeShared<std::unordered_map<Entity, PackIndex>>() }
		{

		}
		virtual ~ComponentPack() {}
	protected:
		T& AddCore(const Entity& id, const T& other = {})
		{
			mData->push_back(other);
			if (mEntityToIndex->contains(id))
			{
				mEntityToIndex->at(id) = mData->size() - 1;
			}
			else
			{
				mEntityToIndex->emplace(id, mData->size() - 1);
			}
			mIndexToEntity->push_back(id);
			return mData->at(mData->size() - 1);
		}
	public:
		T& Get(const Entity& id)
		{
			if (mEntityToIndex->contains(id))
			{
				PackIndex index{ mEntityToIndex->at(id) };
				if (index < GMaxEntities)
				{
					return mData->at(index);
				}
			}
			assert(false && "entity does not contain component");
			return mScratchData;
		}

		T& Add(const Entity& id)
		{
			return AddCore(id);
		}

		T& Add(const Entity& id, const T& other)
		{
			return AddCore(id, other);
		}

		T& Add(const Entity& id, const std::initializer_list<T>&& initializer_list)
		{
			return AddCore(id, std::forward<std::initializer_list<T>>(initializer_list));
		}
		
		virtual void Destroy(Entity id) override
		{
			if (id == nil)
				return;

			if (mEntityToIndex->contains(id))
			{
				PackIndex at{ mEntityToIndex->at(id) };
				if (at < GMaxEntitiesOOB)
				{
					Entity last{ mIndexToEntity->back() };

					if (mData->size() > 1 && (at < (mData->size() - 1)))
					{
						mData->at(at) = mData->back();
						mEntityToIndex->at(last) = at;
						mIndexToEntity->at(at) = last;
					}

					mData->pop_back();
					mIndexToEntity->pop_back();
					mEntityToIndex->at(id) = GMaxEntitiesOOB;
				}
			}
			return;
		}
	protected:
		T mScratchData;
		Shared<std::vector<T>> mData;
		Shared<std::vector<Entity>> mIndexToEntity;
		Shared<std::unordered_map<Entity, PackIndex>> mEntityToIndex;
	};

}
