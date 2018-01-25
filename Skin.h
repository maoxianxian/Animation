#include "Core.h"
struct ModelVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
};
class Skin
{
public:
	Skin(const char * filename);
	~Skin();
	void Load(const char * filename);
	void Update();
	void Draw(const glm::mat4 &viewProjMtx, uint shader);
	uint VertexBuffer;
	uint IndexBuffer;
	//std::vector<
	int numberOfVertex;
};

