#pragma once

#include "etypes.h"

#include <vector>
#include <array>
#include <assert.h>

#include <variant>

namespace necs
{

	// CRTP inheritance

	extern ComponentTypeID GComponentTypesRegistered;

	template<typename T>
	ComponentTypeID GetComponentTypeIDCRTP()
	{
		static ComponentTypeID sTypeID{ GComponentTypesRegistered++ };
		return sTypeID;
	}

	// Component Packs

	template<typename T, typename Derive>
	class BaseComponentPack
	{
		friend Derive;
	public:
		template<typename... Ar>
		T& Add(const Entity& id, Ar&&... params)
		{
			return static_cast<Derive&>(*this).AddI<T>(id, std::forward<Ar>(params)...);
		}
	protected:
		BaseComponentPack() = default;
		~BaseComponentPack() = default;

		template<typename... Ar>
		T& AddI(const Entity& id, Ar&&... params) = delete;

	protected:
		T mScratchData;
		Shared<std::vector<T>> mData;
		Shared<std::vector<Entity>> mIndexToEntity;
		Shared<std::array<PackIndex, GMaxEntities>> mEntityToIndex;
	};

	template<typename T>
	class ComponentPackCRTP : public BaseComponentPack<T, ComponentPackCRTP<T>>
	{
	public:
		ComponentPackCRTP() 
		{
			this->mData = MakeShared<std::vector<T>>();
			this->mIndexToEntity = MakeShared<std::vector<Entity>>();
			this->mEntityToIndex = MakeShared<std::array<PackIndex, GMaxEntities>>();
			this->mEntityToIndex->fill(GMaxEntitiesOOB);
		}

		template<typename... Ar>
		T& AddI(const Entity& id, Ar&&... params)
		{
			this->mData->push_back({ params... });
			this->mEntityToIndex->at(id) = this->mData->size() - 1;
			this->mIndexToEntity->push_back(id);
			return this->mData->at(this->mData->size() - 1);
		}

	};

	template<typename... ty>
	using cpack_interface = std::variant<ty...>;

	template<typename T>
	using cpack_container = std::vector<ComponentPackCRTP<T>>;

}
