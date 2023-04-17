
#include <iostream>
#include <vector>

#include "necs/include.h"

struct Position2D
{
	int32_t x;
	int32_t y;
	Position2D(int32_t X, int32_t Y) :x{ X }, y{ Y } {}
	Position2D() = default;
};

struct Heirarchy
{
	necs::Entity Parent;
	std::vector<necs::Entity> Children;
	Heirarchy(const necs::Entity& parent) : Parent{ parent } {}
	Heirarchy() = default;
};

int main()
{

	using namespace necs;

	Scene scene{};

	Entity e1{ scene.CreateEntity() };
	Entity e2{ scene.CreateEntity() };

	scene.Attach<Position2D>(e1, { 1, 2 });
	scene.Attach<Position2D>(e2);

	scene.DestroyEntity(e1);

	Entity e3{ scene.CreateEntity() };
	Entity e4{ scene.CreateEntity() };

	scene.Attach<Heirarchy>(e2, e3);
	scene.Attach<Heirarchy>(e4, e2);

	// scene views return a vector of all entities that have the template components attached to them
	SceneView<Position2D> view{ scene };
	for (Entity i : view)
	{
		Position2D& p{ scene.GetComponent<Position2D>(i) };
		p.x = i;
		p.y = i + 1;
		std::cout << p.x << ", " << p.y << "\n";
	}

	if (scene.HasComponent<Heirarchy>(e2))
	{
		std::cout << "Has heirarchy\n";
	}

	std::cout << 1;
}
