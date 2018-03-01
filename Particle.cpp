#include "Particle.h"
Particle::Particle(glm::vec3 pos, float mass, bool stationary)
{
	position = pos;
	this->mass = mass;
	this->stationary = stationary;
}

Particle::~Particle()
{
}

void Particle::Update(float time) {
	glm::vec3 acceleration = force / mass;
	velocity += acceleration*time;
	force = glm::vec3(0.0f);
	if (stationary) {
		velocity = glm::vec3(0.0f);
	}
	position += velocity*time;
}
void Particle::ApplyForce(glm::vec3 newforce) {
	force += newforce;
}