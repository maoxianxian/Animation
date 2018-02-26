#include "SpringDamper.h"
SpringDamper::SpringDamper(Particle* p1, Particle* p2, float length, float SpringConst, float DamperConst) {
	this->p1 = p1;
	this->p2 = p2;
	this->restLength = length;
	this->SpringConst = SpringConst;
	this->DamperConst = DamperConst;
}
SpringDamper::~SpringDamper() {

}
void SpringDamper::ComputerForces() {

}