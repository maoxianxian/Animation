#pragma once
#include "core.h"
#include "DOF.h"

class Joint {
public:
	glm::mat4x4 WorldMtx;
	glm::mat4x4 LocalMtx;
	std::vector<DOF*> DOFs;
	std::vector<Joint*> children;
	Joint();
	void Draw();

};
