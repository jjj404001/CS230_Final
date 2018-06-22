#pragma once
#include "vector2.hpp"


class Object;
namespace Contact
{
	bool CollisionTest(Object* first, Object* second);

	void GetInterval(Object input_obj, const vector2& xAxis, float& min, float& max);
	bool IntervalIntersection(Object* first, Object* second);
};
