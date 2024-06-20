#include "Collider.h"

Collider::Collider(ColliderType collider_type, bool has_impulse) :
	collider_type(collider_type),
	has_impulse(has_impulse)
{
}

Collider::~Collider()
{
}
