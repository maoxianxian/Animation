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
	//std::cout << glm::length(force) << std::endl;
	force = glm::vec3(0.0f);
	if (stationary) {
		velocity = glm::vec3(0.0f);
	}
	position += velocity*time;
	if (position.y < -2) {
		if (position.z == 0) {
			position.z += 0.001f;
		}
		velocity = glm::vec3(velocity.x, abs(velocity.y), velocity.z);
		/*if (abs(velocity.y) < 0.1f) {
			velocity.y = 0.1f;
		}*/
	}
}
void Particle::ApplyForce(glm::vec3 newforce) {
	force += newforce;
}

