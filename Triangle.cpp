#include"Triangle.h"
Triangle::Triangle(Particle *p1, Particle *p2, Particle *p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	idx.push_back(0);
	idx.push_back(1);
	idx.push_back(2);
	glGenBuffers(1, &VertexBuffer);
	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(uint), &idx[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	UpdateVTX();
}

Triangle::~Triangle() {
	delete p1;
	delete p2;
	delete p3;
}

void Triangle::Draw() {
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	uint posLoc = 0;
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), 0);
	uint normLoc = 1;
	glEnableVertexAttribArray(normLoc);
	glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)12);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Triangle::Update() {
	UpdateVTX();
}

void Triangle::UpdateVTX() {
	vtx.clear();
	normal = glm::cross(p1->position - p2->position, p1->position - p3->position);
	normal = glm::normalize(normal);
	vtx.push_back({ p1->position,normal });
	vtx.push_back({ p2->position,normal });
	vtx.push_back({ p3->position,normal });
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vtx.size() * sizeof(ModelVertex), &vtx[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}