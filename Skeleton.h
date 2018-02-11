#pragma once
#include "Core.h"
#include "Joint.h"
class Skeleton {
public:
	Joint * root;
	glm::mat4 translate;
	std::vector<Joint*> joints;
	Skeleton(const char * filename);
	void Load(const char * filename);
	void Update();
	void Draw(const glm::mat4 &viewProjMtx, uint shader);
	glm::mat4 GetWorldMatrix(int i);
	std::string UpdateJoint(int index, int dof, float amount);
	void setTranslate(float x, float y, float z);
};