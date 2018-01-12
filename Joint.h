#pragma once
#include "core.h"
#include "DOF.h"
#include "Model.h"
class Joint {
public:
	glm::mat4x4 WorldMtx;
	glm::mat4x4 LocalMtx;
	Model model;
	glm::vec3 minBox;
	glm::vec3 maxBox;
	std::vector<DOF*> DOFs;
	std::vector<Joint*> children;
	Joint();
	void Draw(const glm::mat4 &viewProjMtx, const glm::mat4 &parentMat, uint shader);
	void Update();
	void loadBox();
};
