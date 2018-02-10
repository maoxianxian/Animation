#include "Joint.h"
Joint::Joint() {
	LocalMtx = glm::mat4(1.0f);
	WorldMtx = glm::mat4(1.0f);
	DOF *xDOF = new DOF(0, -100000, 100000);
	DOF *yDOF = new DOF(0, -100000, 100000);
	DOF *zDOF = new DOF(0, -100000, 100000);
	DOFs.push_back(xDOF);
	DOFs.push_back(yDOF);
	DOFs.push_back(zDOF);
}

void Joint::Load(Tokenizer &scanner, std::vector<Joint*> &joints)
{
	bool end = false;
	while (!end)
	{
		char buffer[64];
		end = !scanner.GetToken(buffer);
		//std::cout << buffer << std::endl;
		if (std::string(buffer) == "balljoint")
		{
			Joint * temp = new Joint();
			joints.push_back(temp);
			temp->Load(scanner, joints);
			children.push_back(temp);
		}
		else if (std::string(buffer) == "}")
		{
			model.MakeBox(minBox, maxBox);
			return;
		}
		else if (std::string(buffer) == "offset")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			offset = glm::vec3(x, y, z);
			//std::cout << "offset " <<" "<<x <<" "<<y<<" "<<z << std::endl;
		}
		else if (std::string(buffer) == "boxmin")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			minBox = glm::vec3(x,y,z);
			//std::cout << "boxmin " << " " << x << " " << y << " " << z << std::endl;
		}
		else if (std::string(buffer) == "boxmax")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			maxBox = glm::vec3(x, y, z);
			//std::cout << "boxmax " << " " << x << " " << y << " " << z << std::endl;
		}
		else if (std::string(buffer) == "pose")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			DOFs[0]->setval(x);
			DOFs[1]->setval(y);
			DOFs[2]->setval(z);
			//std::cout << "pose " << " " << x << " " << y << " " << z << std::endl;
		}
		else if (std::string(buffer) == "rotxlimit")
		{
			float min = scanner.GetFloat();
			float max = scanner.GetFloat();
			DOFs[0]->min = min;
			DOFs[0]->max = max;
			//std::cout << "rotx " << " " << min << " " <<max << std::endl;
		}
		else if (std::string(buffer) == "rotylimit")
		{
			float min = scanner.GetFloat();
			float max = scanner.GetFloat();
			DOFs[1]->min = min;
			DOFs[1]->max = max;
			//std::cout << "roty " << " " << min << " " << max << std::endl;
		}
		else if (std::string(buffer) == "rotzlimit")
		{
			float min = scanner.GetFloat();
			float max = scanner.GetFloat();
			DOFs[2]->min = min;
			DOFs[2]->max = max;
			//std::cout << "rotx " << " " << min << " " << max << std::endl;
		}
		else if(std::string(buffer)!="{")
		{
			name = std::string(buffer);
			//std::cout << name << std::endl;
		}
	}
}
void Joint::Draw(const glm::mat4 &viewProjMtx, uint shader) {
	model.Draw(WorldMtx , viewProjMtx, shader);
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Draw(viewProjMtx, shader);
	}
}

void Joint::Update(const glm::mat4 &parentMat)
{
	LocalMtx = glm::mat4(1.0f);
	LocalMtx = LocalMtx*glm::rotate(glm::mat4(1.0f), DOFs[2]->val, glm::vec3(0, 0, 1));
	LocalMtx = LocalMtx*glm::rotate(glm::mat4(1.0f), DOFs[1]->val, glm::vec3(0, 1, 0));
	LocalMtx = LocalMtx*glm::rotate(glm::mat4(1.0f), DOFs[0]->val, glm::vec3(1, 0, 0));
	LocalMtx = glm::translate(glm::mat4(1.0f), offset)*LocalMtx;
	WorldMtx = parentMat*LocalMtx;

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update(WorldMtx);
	}
}

void Joint::UpdateDOF(int dof, float amount)
{
	DOFs[dof]->setval(DOFs[dof]->val + amount);
}
void Joint::UpdateDOF(float x,float y,float z)
{
	DOFs[0]->setval(x);
	DOFs[1]->setval(y);
	DOFs[2]->setval(z);
}
