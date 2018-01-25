#include "Skin.h"
#include "Tokenizer.h"

Skin::Skin(const char * filename)
{
	Load(filename);
}

Skin::~Skin()
{
}

void Skin::Load(const char * filename)
{
	glGenBuffers(1, &VertexBuffer);
	glGenBuffers(1, &IndexBuffer);
	numberOfVertex = 0;

	std::vector<ModelVertex> vtx;
	std::vector<uint> idx;
	Tokenizer scanner;
	scanner.Open(filename);
	char buffer[64];
	scanner.GetToken(buffer);
	if (std::string(buffer) == "positions")
	{
		int numberOfVertex = scanner.GetInt();
		for (int i = 0; i < numberOfVertex; i++)
		{
			float x = scanner.GetFloat();
			float y = scanner.GetFloat();
			float z = scanner.GetFloat();
			vtx.push_back({glm::vec3(x,y,z),glm::vec3(0,0,0)});
		}
		//normals
		scanner.GetToken(buffer);
		if (std::string(buffer) == "normals")
		{
			scanner.GetInt();
			for (int i = 0; i < numberOfVertex; i++)
			{
				float x = scanner.GetFloat();
				float y = scanner.GetFloat();
				float z = scanner.GetFloat();
				vtx[i].Normal=glm::vec3(x,y,z);
			}
		}
		else
		{
			std::cout << "error reading normals" << std::endl;
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vtx.size() * sizeof(ModelVertex), &vtx[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(uint), &idx[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		std::cout << "error reading positions" << std::endl;
		return;
	}
}

