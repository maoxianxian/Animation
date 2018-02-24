#pragma once
#include "Core.h"
#include "Particle.h"
class SpringDamper {
public:
	float SpringConst;
	float DamperConst;
	Particle *p1,*p2;
	float restLength;
	SpringDamper();
	~SpringDamper();
	void ComputerForces();
};