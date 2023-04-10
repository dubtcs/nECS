
#include <iostream>
#include <vector>

#include "necs/include.h"
#include <unordered_map>

struct Position2D
{
	int32_t x;
	int32_t y;
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
	std::unordered_map<Entity, PackIndex> m{};
		
	Scene s{};

	Entity e1{ s.CreateEntity() };
	Entity e2{ s.CreateEntity() };

	// attachment returns a ref to the component
	Position2D& p{ s.Attach<Position2D>(e1) };
	p.x = 5;
	p.y = 10;

	// paramater packs
	s.Attach<Position2D>(e2, { 4, 8 });

	Heirarchy& h{ s.Attach<Heirarchy>(e1, e2) };
	h.Children.push_back(e2);

	Position2D& pr{ s.GetComponent<Position2D>(e1) };
	std::cout << pr.x << ", " << pr.y << "\n";

	Position2D& pr2{ s.GetComponent<Position2D>(e2) };
	std::cout << pr2.x << ", " << pr2.y << "\n";

	if (s.HasComponent<Heirarchy>(e1))
	{
		std::cout << "Heirarchy Attatched\n";
		Heirarchy& hr{ s.GetComponent<Heirarchy>(e1) };
		std::cout << "Parent: " << hr.Parent << "\n";
	}

}
