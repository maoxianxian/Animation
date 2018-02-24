#pragma once
#include "Core.h"
class Particle
{
public:
	float mass;
	glm::vec3 force;
	glm::vec3 velocity;
	glm::vec3 position;
	Particle(glm::vec3 pos,float mass);
	void Update(float time);
	void ApplyForce(glm::vec3 newforce);
	~Particle();
};

