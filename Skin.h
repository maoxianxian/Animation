#include "Core.h"
#include "SkinVertex.h"
#include "Model.h"

class Skin
{
public:
	Skin(const char * filename, Skeleton* skel);
	~Skin();
	void Load(const char * filename);
	void Update();
	void Draw(const glm::mat4 &viewProjMtx, uint shader);
	uint VertexBuffer;
	uint IndexBuffer;
	std::vector<SkinVertex*> vertices;
	int numberOfVertex;
	int numberOfTriangle;
	std::vector<ModelVertex> vtx;
	std::vector<uint> idx;
	std::vector<glm::mat4> binds;
	Skeleton * skel;
};

