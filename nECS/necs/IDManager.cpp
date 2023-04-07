
#include "IDManager.h"

namespace necs
{

	Entity IDManager::Create()
	{
		Entity id{ mStack.top() };
		mStack.pop();
		return id;
	}

	void IDManager::Destroy(const Entity& id)
	{
		mStack.push(id);
	}

	IDManager::IDManager()
	{
		for (Entity i{ 0 }; i < GMaxEntities; i++)
		{
			mStack.push(i);
		}
	}

}
