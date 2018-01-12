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

void Joint::loadBox(float min, float max)
{

}
void Joint::Draw(const glm::mat4 &viewProjMtx, const glm::mat4 &parentMat, uint shader) {
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelMtx"), 1, false, (float*)&(LocalMtx*parentMat));
	glm::mat4 mvpMtx = viewProjMtx * LocalMtx*parentMat;
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelViewProjMtx"), 1, false, (float*)&mvpMtx);
}