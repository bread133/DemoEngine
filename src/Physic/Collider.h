#include <glm/vec3.hpp>
#include <string>

enum ColliderType
{
	SPHERE = 1,
	PARALLELEPIPED = 2,
	NONE = 4,
};

struct Collider
{
public:
	ColliderType collider_type;

	Collider();
	~Collider();
};

struct SphereCollider : public Collider
{
public:
	glm::vec3 center;
	glm::vec3 radius;

	SphereCollider();
	~SphereCollider();
};

struct ParallelepipedCollider : public Collider
{
public:
	glm::vec3 min_point;
	glm::vec3 max_point;
	glm::vec3 center;

	glm::vec3 diff;

	ParallelepipedCollider();
	~ParallelepipedCollider();
};

struct NoneCollider : public Collider
{
public:
	NoneCollider();
	~NoneCollider();
};