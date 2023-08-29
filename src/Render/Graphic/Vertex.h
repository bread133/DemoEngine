#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coord;

	glm::vec3 tangent;
	// bitangent
	glm::vec3 bitangent;
	// bone indexes which will influence this vertex
	int m_bone_ids[MAX_BONE_INFLUENCE];
	// weights from each bone
	float m_weights[MAX_BONE_INFLUENCE];
};