
#include <iostream>

#include "ecs/include.h"

struct b
{
	int a;
	char c;
};

int main()
{
	using namespace ecs;
	ecs::Scene s{};
	ecs::Entity e1{ s.CreateEntity() };
	ecs::Entity e2{ s.CreateEntity() };
	s.Attach<b>(e1);
	s.Attach<int>(e2);
	s.DestroyEntity(e1);
}
