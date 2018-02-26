#include "Cloth.h"

Cloth::Cloth(int height,int width) {
	prevtime = ((float)glutGet(GLUT_ELAPSED_TIME)) / 1000.f;
	this->height = height;
	this->width = width;
	modelmat = glm::mat4(1.0f);
	for(int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Particle* temp = new Particle(glm::vec3(i,j,0),1);
			particles.push_back(temp);
		}
	}
	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width - 1; j++) {
			int upperleft = i*width + j;
			int upperright = upperleft + 1;
			int bottomleft = upperleft + width;
			int bottomright = bottomleft + 1;
			Triangle* temp = new Triangle(particles[upperleft], particles[bottomleft], particles[upperright]);
			triangles.push_back(temp);
			temp = new Triangle(particles[bottomright], particles[upperright], particles[bottomleft]);
			triangles.push_back(temp);
			SpringDamper* spr = new SpringDamper(particles[upperleft], particles[bottomright], sqrt(2), 0.1f, 0.1f);
			springs.push_back(spr);
			spr = new SpringDamper(particles[bottomleft], particles[upperright], sqrt(2), 0.1f, 0.1f);
			springs.push_back(spr);
			spr = new SpringDamper(particles[bottomright], particles[upperright], 1, 0.1f, 0.1f);
			springs.push_back(spr);
			spr = new SpringDamper(particles[bottomright], particles[bottomleft], 1, 0.1f, 0.1f);
			springs.push_back(spr);
		}
	}
	for (int i = 0; i < height - 1; i++) {
		SpringDamper* spr = new SpringDamper(particles[i*width], particles[(i+1)*width], 1, 0.1f, 0.1f);
		springs.push_back(spr);
	}
	for (int j = 0; j < width - 1; j++) {
		SpringDamper* spr = new SpringDamper(particles[j], particles[(j + 1)], 1, 0.1f, 0.1f);
		springs.push_back(spr);
	}
}

Cloth::~Cloth() {
	triangles.clear();
	particles.clear();
	springs.clear();
}

void Cloth::Draw(const glm::mat4 &viewProjMtx, uint shader) {
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelMtx"), 1, false, (float*)&modelmat);
	glm::mat4 mvpMtx = viewProjMtx;
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelViewProjMtx"), 1, false, (float*)&mvpMtx);
	for (int i = 0; i < triangles.size(); i++) {
		triangles[i]->Draw();
	}
	glUseProgram(0);
}

void Cloth::Update() {
	float currtime = ((float)glutGet(GLUT_ELAPSED_TIME)) / 1000.f;
	float timediff = currtime-prevtime;
	prevtime = currtime;
	for (int i = 0; i < springs.size(); i++) {
		springs[i]->ComputerForces();
	}
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->Update(timediff);
	}
}