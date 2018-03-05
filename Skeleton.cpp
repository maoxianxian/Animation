#include "Skeleton.h"
#include "Tokenizer.h"
Skeleton::Skeleton(const char * filename)
{
	Load(filename);
	translate = glm::mat4(1.0f);
}

void Skeleton::Load(const char * filename)
{
	Tokenizer scanner;
	scanner.Open(filename);
	char buffer[64];
	scanner.GetToken(buffer);
	if (std::string(buffer) == "balljoint")
	{
		Joint * temp = new Joint(NULL);
		temp->name = "root";
		joints.push_back(temp);
		temp->Load(scanner, joints);
		root = temp;
	}
	scanner.Close();
}

void Skeleton::Draw(const glm::mat4 &viewProjMtx, uint shader) {
	root->Draw(viewProjMtx,shader);
}

void Skeleton::Update()
{
	root->Update(translate);
}

glm::mat4 Skeleton::GetWorldMatrix(int i) {
	return joints[i]->WorldMtx;
}

std::string Skeleton::UpdateJoint(int index, int dof, float amount) {
	joints[index]->UpdateDOF(dof, amount);
	return joints[index]->name;
}

void Skeleton::setTranslate(float x, float y, float z) {
	translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Skeleton::calculateDOFs(int index, float x, float y, float z) {
	for (int i = 0; i < joints.size(); i++) {
		if (joints[i]->approachPos(glm::vec3(x, y, z), joints[index],this)) {
			return;
		}
	}
	//std::cout << joints[index]->calculatePos().x << " " << joints[index]->calculatePos().y << " " << joints[index]->calculatePos().z << std::endl;
}