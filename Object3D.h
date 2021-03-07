#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>

namespace Object3D
{
	// Creeaza o primitiva geometrica cu parametrii specificat fiind centrata pe centrul mesh-ului
	Mesh* CreateCube(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateSphere(std::string name, glm::vec3 center, float length, glm::vec3 color, int sectorCount, int stackCount, bool fill = false);
	Mesh* CreateSquare(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color);

	// Creeaza un mesh
	Mesh* CreateMesh(Mesh* mesh, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
}

