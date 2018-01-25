#include "Skeleton.h"
#include "Tokenizer.h"
Skeleton::Skeleton(const char * filename)
{
	Load(filename);
}

void Skeleton::Load(const char * filename)
{
	Tokenizer scanner;
	scanner.Open(filename);
	char buffer[64];
	scanner.GetToken(buffer);
	if (std::string(buffer) == "balljoint")
	{
		Joint * temp = new Joint();
		joints.push_back(temp);
		temp->Load(scanner, joints);
		root = temp;
	}
}

void Skeleton::Draw(const glm::mat4 &viewProjMtx, uint shader) {
	root->Draw(viewProjMtx,glm::mat4(1.0f),shader);
}

void Skeleton::Update()
{
	root->Update();
}

glm::mat4 Skeleton::GetWorldMatrix(int i) {
	return joints[i]->WorldMtx;
}