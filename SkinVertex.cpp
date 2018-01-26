#include "SkinVertex.h"
SkinVertex::SkinVertex(float x, float y, float z,int i)
{
	WorldPosition = glm::vec3(0, 0, 0);
	localPosition = glm::vec3(x, y, z);
	index = i;
}
void SkinVertex::addAttach(int id, float weight)
{
	attaches.push_back({ id,weight });
}

glm::vec3 SkinVertex::calculatePos(std::vector<glm::mat4> &binds, Skeleton* skel) {
	WorldPosition = glm::vec3(0, 0, 0);
	for (int i = 0; i < attaches.size(); i++)
	{		
		WorldPosition += glm::vec3(skel->GetWorldMatrix(attaches[i].jointId)*glm::inverse(binds[i])*glm::vec4(localPosition,1));
		
	}
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << glm::inverse(binds[1])[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	//std::cout << WorldPosition.x << " " << WorldPosition.y << " " << WorldPosition.z << std::endl;
	return WorldPosition;
}

SkinVertex::~SkinVertex() {

}
