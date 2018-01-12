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
	bool end = false;
	std::vector<Joint*> stack;
	Joint* temp=NULL;
	while (!end)
	{
		char buffer[64];
		end=!scanner.GetToken(buffer);
		//std::cout << buffer << std::endl;
		if (std::string(buffer) == "balljoint")
		{
			Joint* parent = temp;
			temp = new Joint();
			stack.push_back(temp);
			if (!root)
			{
				root = temp;
			}
			if (parent) {
				parent->children.push_back(temp);
			}
			//std::cout << "create new joint" << std::endl;
		}
		else if (std::string(buffer) == "}")
		{
			stack.pop_back();
			temp = stack[stack.size()-1];
			//std::cout << "return" << std::endl;
		}
		else if (std::string(buffer) == "offset")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			temp->LocalMtx = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
			//std::cout << "offset " <<" "<<x <<" "<<y<<" "<<z << std::endl;
		}
		else if (std::string(buffer) == "boxmin")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			temp->minBox = glm::vec3(x,y,z);
			//std::cout << "boxmin " << " " << x << " " << y << " " << z << std::endl;
		}
		else if (std::string(buffer) == "boxmax")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			temp->maxBox = glm::vec3(x, y, z);
			//std::cout << "boxmax " << " " << x << " " << y << " " << z << std::endl;
		}
		else if (std::string(buffer) == "pose")
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			temp->DOFs[0]->val = x;
			temp->DOFs[1]->val = y;
			temp->DOFs[2]->val = z;
			//std::cout << "pose " << " " << x << " " << y << " " << z << std::endl;
		}
		else if (std::string(buffer) == "rotxlimit")
		{
			float min = scanner.GetFloat();
			float max = scanner.GetFloat();
			temp->DOFs[0]->min = min;
			temp->DOFs[0]->max = max;
			//std::cout << "rotx " << " " << min << " " <<max << std::endl;
		}
		else if (std::string(buffer) == "rotylimit")
		{
			float min = scanner.GetFloat();
			float max = scanner.GetFloat();
			temp->DOFs[1]->min = min;
			temp->DOFs[1]->max = max;
			//std::cout << "roty " << " " << min << " " << max << std::endl;
		}
		else if (std::string(buffer) == "rotzlimit")
		{
			float min = scanner.GetFloat();
			float max = scanner.GetFloat();
			temp->DOFs[2]->min = min;
			temp->DOFs[2]->max = max;
			//std::cout << "rotx " << " " << min << " " << max << std::endl;
		}
	}
}

void Skeleton::Draw(const glm::mat4 &viewProjMtx, uint shader) {
	root->Draw(viewProjMtx,glm::mat4(1.0f),shader);
}

void Skeleton::Update()
{
	root->Update();
}