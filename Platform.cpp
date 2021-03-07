#include "Platform.h"

bool Platform::willLand = false;

Platform::Platform()
{
	modelMatrix = glm::mat4(1);
	center = glm::vec3(0);
	position = glm::vec3(0);
	length = 0;
	width = 0;
	height = 0;
	init_size = 0;
	color = WHITE;
}

Platform::Platform(glm::vec3 center, float init_size)
{
	this->center = center;
	this->init_size = init_size;
	length = init_size;
	width = init_size;
	height = init_size;
	position = glm::vec3(0);
	modelMatrix = glm::mat4(1);
	color = WHITE;
}

Platform::~Platform()
{
}

void Platform::setMatrix(glm::mat4 newMatrix)
{
	modelMatrix = newMatrix;
}

void Platform::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Platform::setLength(float newLength)
{
	length = newLength;
}

void Platform::setWidth(float newWidth)
{
	width = newWidth;
}

void Platform::setHeight(float newHeight)
{
	height = newHeight;
}

void Platform::setColor(glm::vec3 newColor)
{
	color = newColor;
}

void Platform::checkLanding(Player* player)
{
	glm::vec3 sphere = player->getPosition();

	float x = std::max(-width/2 + position.x, std::min(sphere.x, width/2 + position.x));
	float y = std::max(-height/2 + position.y, std::max(sphere.y, height/2 + position.y));
	float z = std::max(-length/2 + position.z, std::min(sphere.z, length/2 + position.z));

	float distance = sqrtf((x - sphere.x) * (x - sphere.x) +
		(y - sphere.y) * (y - sphere.y) +
		(z - sphere.z) * (z - sphere.z));

	bool canLand = distance < player->getDiameter()/8;

	willLand = willLand || canLand;

	if (canLand) {
		player->setGround(position.y + height/2 + player->getDiameter()/2);
		if (player->getPosition().y == player->getGround()) {
			player->setOldGround(position.y + height/2 + player->getDiameter()/2);
			player->setFall(false);
			player->setFallTime(0);
		}
	}
}

void Platform::checkIfLanded(Player* player)
{
	glm::vec3 sphere = player->getPosition();

	float x = std::max(-width / 2 + position.x, std::min(sphere.x, width / 2 + position.x));
	float y = std::max(-height / 2 + position.y, std::min(sphere.y, height / 2 + position.y));
	float z = std::max(-length / 2 + position.z, std::min(sphere.z, length / 2 + position.z));

	float distance = sqrtf((x - sphere.x) * (x - sphere.x) +
		(y - sphere.y) * (y - sphere.y) +
		(z - sphere.z) * (z - sphere.z));

	bool landed = distance < player->getDiameter();

	if (landed && color != PURPLE) {
		updatePlayer(player);
		color = PURPLE;
	}
}

void Platform::updatePlayer(Player* player)
{
	if (color == RED && !player->isInvincible()) {
		player->setDeath(true);
	}

	if (color == YELLOW && !player->isInvincible()) {
		player->setFuel(player->getFuel() * 0.75f);
		player->setPowerUp(true);
	}

	if (color == ORANGE && !player->isInvincible()) {
		player->setBlock(true);
		player->setPowerUp(true);
	}

	if (color == GREEN) {
		player->setFuel(player->getFuel() * 1.4f);
		player->setPowerUp(true);
	}

	if (color == BLUE) {
		player->setInvincible(true);
	}
}

void Platform::translate(float newX, float newY, float newZ)
{
	position.x += newX;
	position.y += newY;
	position.z += newZ;
}

void Platform::scale(float scaleX, float scaleY, float scaleZ)
{
	width *= scaleX;
	height *= scaleY;
	length *= scaleZ;

	position.x *= scaleX;
	position.y *= scaleY;
	position.z *= scaleZ;
}

glm::mat4 Platform::getMatrix()
{
	return modelMatrix * Transform3D::Translate(position.x, position.y, position.z) 
					   * Transform3D::Scale(width / init_size, height / init_size, length / init_size);
}

glm::vec3 Platform::getCenter()
{
	return center;
}

float Platform::getLength()
{
	return length;
}

float Platform::getWidth()
{
	return width;
}

float Platform::getHeight()
{
	return height;
}

float Platform::getInitSize()
{
	return init_size;
}

glm::vec3 Platform::getPosition()
{
	return position;
}

glm::vec3 Platform::getColor()
{
	return color;
}
