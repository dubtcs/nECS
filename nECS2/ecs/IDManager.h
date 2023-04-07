#pragma once

#include "etypes.h"

#include <vector>
#include <stack>

namespace ecs
{

	class IDManager
	{
	public:
		IDManager();
		Entity Create();
		void Destroy(const Entity& id);
	protected:
		std::vector<Entity> mIdsUsed;
		std::stack<Entity> mStack;
	};

}
