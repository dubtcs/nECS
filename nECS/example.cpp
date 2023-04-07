
#include <iostream>

#include "necs/include.h"

#include "necs/ComponentPackCRTP.h"

struct NumberValue
{
	int32_t First{ 0 };
	int32_t Last{ 0 };
};

int main()
{
	using namespace necs;
	
	ComponentPackCRTP<int> c{};

	std::vector<BaseComponentPack> bruh{};

	/*
	Scene s{};

	Entity e1{ s.CreateEntity() };

	NumberValue& nv1{ s.Attach<NumberValue>(e1) };

	std::cout << nv1.First << ", " << nv1.Last << "\n";

	nv1.First = 50;
	nv1.Last = 12;

	std::cout << nv1.First << ", " << nv1.Last << "\n";

	s.Detach<NumberValue>(e1);

	s.DestroyEntity(e1);*/

}
