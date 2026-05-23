#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Particle
{
	glm::vec3 position;
	glm::vec3 veloctiy;
	glm::float32 mass;
};

struct Fluid
{
	std::vector<Particle> particles;
};