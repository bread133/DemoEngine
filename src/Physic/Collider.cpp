#include "Collider.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

SphereCollider::SphereCollider()
{
	collider_type = SPHERE;
}

SphereCollider::~SphereCollider()
{
}

ParallelepipedCollider::ParallelepipedCollider()
{
	collider_type = PARALLELEPIPED;
}

ParallelepipedCollider::~ParallelepipedCollider()
{
}

NoneCollider::NoneCollider()
{
	collider_type = NONE;
}

NoneCollider::~NoneCollider()
{
}
