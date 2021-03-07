#include "Obstacle.h"

Obstacle::Obstacle()
{
	modelMatrix = glm::mat4(1);
	center = glm::vec3(0);
	position = glm::vec3(0);
	length = 0;
	width = 0;
	height = 0;
	init_size = 0;
	rendered = false;
	color = WHITE;
}

Obstacle::Obstacle(glm::vec3 center, float init_size)
{
	this->center = center;
	this->init_size = init_size;
	length = init_size;
	width = init_size;
	height = init_size;
	position = glm::vec3(0);
	modelMatrix = glm::mat4(1);
	color = WHITE;
	rendered = false;
}

Obstacle::~Obstacle()
{
}

void Obstacle::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Obstacle::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Obstacle::setLength(float newLength)
{
	length = newLength;
}

void Obstacle::setWidth(float newWidth)
{
	width = newWidth;
}

void Obstacle::setHeight(float newHeight)
{
	height = newHeight;
}

void Obstacle::setColor(glm::vec3 newColor)
{
	color = newColor;
}

void Obstacle::setRendered(bool render)
{
	rendered = render;
}


void Obstacle::checkHit(Player* player)
{
	glm::vec3 sphere = player->getPosition();

	float x = std::max(-width / 2 + position.x, std::min(sphere.x, width / 2 + position.x));
	float y = std::max(-height / 2 + position.y, std::min(sphere.y, height / 2 + position.y));
	float z = std::max(-length / 2 + position.z, std::min(sphere.z, length / 2 + position.z));

	float distance = sqrtf((x - sphere.x) * (x - sphere.x) +
		(y - sphere.y) * (y - sphere.y) +
		(z - sphere.z) * (z - sphere.z));

	bool gotHit = distance < player->getDiameter();

	if (gotHit) {
		if (!player->isInvincible()) {
			player->setDeathType(4);
			player->setDeath(true);
		}
		else {
			rendered = false;
		}
	}
}

void Obstacle::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Obstacle::scale(float scaleX, float scaleY, float scaleZ)
{
	width *= scaleX;
	height *= scaleY;
	length *= scaleZ;

	position.x *= scaleX;
	position.y *= scaleY;
	position.z *= scaleZ;
}

glm::mat4 Obstacle::getMatrix()
{
	return modelMatrix * Transform3D::Translate(position.x, position.y, position.z)
		* Transform3D::Scale(width / init_size, height / init_size, length / init_size) *
		Transform3D::RotateOX(RADIANS(45)) * Transform3D::RotateOY(RADIANS(45));
}

glm::vec3 Obstacle::getCenter()
{
	return center;
}

float Obstacle::getLength()
{
	return length;
}

float Obstacle::getWidth()
{
	return width;
}

float Obstacle::getHeight()
{
	return height;
}

float Obstacle::getInitSize()
{
	return init_size;
}

bool Obstacle::isRendered()
{
	return rendered;
}

glm::vec3 Obstacle::getPosition()
{
	return position;
}

glm::vec3 Obstacle::getColor()
{
	return color;
}
