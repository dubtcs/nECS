
#include <iostream>

#include "necs/include.h"
#include <unordered_map>

struct NumberValue
{
	int32_t First{ 0 };
	int32_t Last{ 0 };
};

int main()
{
	using namespace necs;
	std::unordered_map<Entity, PackIndex> m{};
		
	//Shared<Scene> s{ MakeShared<Scene>() };
	Scene s{};

	Entity e1{ s.CreateEntity() };
	Entity e2{ s.CreateEntity() };
	Entity e3{ s.CreateEntity() };

	NumberValue& nv{ s.Attach<NumberValue>(e1) };
	nv.First = 17;
	nv.Last = 38;
	NumberValue& nv2 = s.Attach<NumberValue>(e2);
	nv2.First = 24;
	nv2.Last = 19;
	NumberValue& nv3 = s.Attach<NumberValue>(e3);
	nv3.First = 150;
	nv3.Last = 44;

	uint32_t& g = s.Attach<uint32_t>(e2);

	NumberValue& b{ s.GetComponent<NumberValue>(e1) };
	std::cout << b.First << ", " << b.Last << "\n";

	NumberValue& b2{ s.GetComponent<NumberValue>(e2) };
	std::cout << b2.First << ", " << b2.Last << "\n";

	NumberValue& b3{ s.GetComponent<NumberValue>(e3) };
	std::cout << b3.First << ", " << b3.Last << "\n";

	s.Detach<NumberValue>(e1);

	NumberValue& b4{ s.GetComponent<NumberValue>(e2) };
	std::cout << b4.First << ", " << b4.Last << "\n";

	NumberValue& b5{ s.GetComponent<NumberValue>(e3) };
	std::cout << b5.First << ", " << b5.Last << "\n";

	std::cout << "\nView\n";
	SceneView<NumberValue> v{ s };
	for (Entity i : v)
	{
		NumberValue& v{ s.GetComponent<NumberValue>(i) };
		v.First = 5;
	}

	if (s.HasComponent<NumberValue>(e2))
		std::cout << "Has\n";

	s.DestroyEntity(e1);

}
