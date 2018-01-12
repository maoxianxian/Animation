#pragma once
#include "Core.h"
#include "Joint.h"
class Skeleton {
public:
	Joint * root;
	Skeleton(const char * filename);
	void Load(const char * filename);
	void Update();
	void Draw(const glm::mat4 &viewProjMtx, uint shader);
};