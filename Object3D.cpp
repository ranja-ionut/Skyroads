#include "Object3D.h"


Mesh* Object3D::CreateCube(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
	float half_length = length / 2;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-half_length, -half_length, -half_length), color), // stanga jos close
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color), // dreapta jos close
		VertexFormat(center + glm::vec3(-half_length, half_length, -half_length), color), // stanga sus close
		VertexFormat(center + glm::vec3(half_length, half_length, -half_length), color), // dreapta sus close
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color), // stanga jos far
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color), // dreapta jos far
		VertexFormat(center + glm::vec3(-half_length, half_length, half_length), color), // stanga sus far
		VertexFormat(center + glm::vec3(half_length, half_length, half_length), color), // dreapta sus far
	};

	std::vector<unsigned short> indices = { 0, 1, 2,
			1, 3, 2,
			2, 3, 7,
			2, 7, 6,
			1, 7, 3,
			1, 5, 7,
			6, 7, 4,
			7, 5, 4,
			0, 4, 1,
			1, 4, 5,
			2, 6, 4,
			0, 2, 4 };

	Mesh* cube = new Mesh(name);

	if (!fill) {
		cube->SetDrawMode(GL_LINE_LOOP);
	}

	return CreateMesh(cube, vertices, indices);
}

Mesh* Object3D::CreateSphere(std::string name, glm::vec3 center, float length, glm::vec3 color, int sectorCount, int stackCount, bool fill)
{
	float radius = length / 2;
	std::vector<unsigned short> indices;
	std::vector<VertexFormat> vertices;

	float x, y, z, xy;
	float sector = 2 * M_PI / sectorCount;
	float stack = M_PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stack;        // de la pi/2 la -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sector;           // de la 0 la 2 * pi

			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
		}
	}

	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // stack curent
		k2 = k1 + sectorCount + 1;      // stack urmator

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	Mesh* sphere = new Mesh(name);
	
	if (!fill) {
		sphere->SetDrawMode(GL_LINES);
	}

	return CreateMesh(sphere, vertices, indices);
}

Mesh* Object3D::CreateSquare(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color) {
	glm::vec3 corner = bottomLeftCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), // stanga jos
		VertexFormat(corner + glm::vec3(length, 0, 0), color), // dreapta jos
		VertexFormat(corner + glm::vec3(length, length, 0), color), // dreapta sus
		VertexFormat(corner + glm::vec3(0, length, 0), color) // stanga sus
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2 };

	return CreateMesh(square, vertices, indices);
}

Mesh* Object3D::CreateMesh(Mesh* mesh, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	// VAO
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// IBO
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;
	return mesh;
}
