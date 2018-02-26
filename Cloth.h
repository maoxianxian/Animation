#pragma once
#include "Core.h"
#include "SpringDamper.h"
#include "Triangle.h"

class Cloth {
public:
	int height;
	int width;
	float prevtime;
	glm::mat4 modelmat;
	std::vector<Triangle*> triangles;
	std::vector<SpringDamper*> springs;
	std::vector<Particle*> particles;
	Cloth(int height, int width);
	~Cloth();
	void Draw(const glm::mat4 &viewProjMtx, uint shader);
	void Update();
};