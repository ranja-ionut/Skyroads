#include "Pattern.h"

Pattern::Pattern()
{
	count = 3;
	pattern_id = 0;
	platforms = new Platform*[3];
	obstacles = new Obstacle*[1];
}

Pattern::Pattern(int count, int pattern_id)
{
	this->count = count;
	this->pattern_id = pattern_id;
	platforms = new Platform*[count];
	obstacles = new Obstacle*[count / 3];
}

Pattern::~Pattern()
{
}

int Pattern::getCount()
{
	return count;
}

int Pattern::getId()
{
	return pattern_id;
}

Platform** Pattern::getPlatforms()
{
	return platforms;
}

Obstacle** Pattern::getObstacles()
{
	return obstacles;
}

float Pattern::getLeft()
{
	float left = platforms[0]->getPosition().x;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().x - platforms[i]->getWidth() / 2 < left) {
			left = platforms[i]->getPosition().x - platforms[i]->getWidth() / 2;
		}
	}

	return left;
}

float Pattern::getRight()
{
	float right = platforms[0]->getPosition().x;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().x + platforms[i]->getWidth() / 2 > right) {
			right = platforms[i]->getPosition().x + platforms[i]->getWidth() / 2;
		}
	}

	return right;
}

float Pattern::getUp()
{
	float up = platforms[0]->getPosition().z;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().z - platforms[i]->getLength() / 2 < up) {
			up = platforms[i]->getPosition().z - platforms[i]->getLength() / 2;
		}
	}

	return up;
}

float Pattern::getDown()
{
	float down = platforms[0]->getPosition().z;

	for (int i = 0; i < count; i++) {
		if (platforms[i]->getPosition().z + platforms[i]->getLength() / 2 > down) {
			down = platforms[i]->getPosition().z + platforms[i]->getLength() / 2;
		}
	}

	return down;
}

void Pattern::checkLanding(Player* player)
{
	for (int i = 0; i < count; i++) {
		platforms[i]->checkLanding(player);
	}

	for (int i = 0; i < count / 3; i++) {
		obstacles[i]->checkHit(player);
	}
}

void Pattern::checkIfLanded(Player* player)
{
	for (int i = 0; i < count; i++) {
		platforms[i]->checkIfLanded(player);
	}
}

void Pattern::translate(float newX, float newY, float newZ)
{
	for (int i = 0; i < count; i++) {
		platforms[i]->translate(newX, newY, newZ);
	}

	for (int i = 0; i < count / 3; i++) {
		obstacles[i]->translate(newX, newY, newZ);
	}
}

void Pattern::createPlatforms()
{
	for (int i = 0; i < count; i++) {
		platforms[i] = new Platform(ORIGIN, PLATFORM_SIZE);
	}
	
	for (int i = 0; i < count / 3; i++) {
		obstacles[i] = new Obstacle(ORIGIN, OBSTACLE_SIZE);
	}
}

void Pattern::createType(int type)
{
	switch (type) {
		case GRAY_TYPE:
			for (int i = 0; i < count; i++) {
				int chance = rand() % 100;
				if (chance < 50) {
					platforms[i]->setColor(GRAY);
				}
				else {
					platforms[i]->setColor(BLUE);
				}
			}
			break;
		case GREEN_TYPE:
			for (int i = 0; i < count; i++) {
				platforms[i]->setColor(GREEN);
			}
			break;
		case ORANGE_TYPE:
			for (int i = 0; i < count; i++) {
				platforms[i]->setColor(ORANGE);
			}
			break;
		case YELLOW_TYPE:
			for (int i = 0; i < count; i++) {
				platforms[i]->setColor(YELLOW);
			}
			break;
		case GYO_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;
				
				if (choice <= 50) {
					platforms[i]->setColor(GREEN);
				}

				if (choice > 50 && choice <= 75) {
					platforms[i]->setColor(YELLOW);
				}

				if (choice > 75) {
					platforms[i]->setColor(ORANGE);
				}
			}
			break;
		case GO_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice <= 75) {
					platforms[i]->setColor(GREEN);
				}

				if (choice > 75) {
					platforms[i]->setColor(ORANGE);
				}
			}
			break;
		case GY_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice <= 50) {
					platforms[i]->setColor(GREEN);
				}

				if (choice > 50) {
					platforms[i]->setColor(YELLOW);
				}
			}
			break;
		case GRAY_GR_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice < 15) {
					platforms[i]->setColor(GREEN);
				}

				if (choice >= 15 && choice < 45) {
					platforms[i]->setColor(GRAY);
				}

				if (choice >= 45 && choice < 85) {
					platforms[i]->setColor(BLUE);
				}

				if (choice >= 85) {
					platforms[i]->setColor(RED);
				}
			}
			break;
		case GRAYR_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice < 10) {
					platforms[i]->setColor(BLUE);
				}

				if (choice >= 10 && choice < 75) {
					platforms[i]->setColor(GRAY);
				}

				if (choice >= 75) {
					platforms[i]->setColor(RED);
				}
			}
			break;
		case GRAYG_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice < 10) {
					platforms[i]->setColor(BLUE);
				}

				if (choice >= 10 && choice < 50) {
					platforms[i]->setColor(GRAY);
				}

				if (choice >= 50) {
					platforms[i]->setColor(GREEN);
				}
			}
			break;
		case GRAYY_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice < 10) {
					platforms[i]->setColor(BLUE);
				}

				if (choice >= 10 && choice < 40) {
					platforms[i]->setColor(GRAY);
				}

				if (choice >= 60) {
					platforms[i]->setColor(YELLOW);
				}
			}
			break;
		case GRAYO_TYPE:
			for (int i = 0; i < count; i++) {
				int choice = rand() % 100;

				if (choice < 10) {
					platforms[i]->setColor(BLUE);
				}

				if (choice >= 10 && choice < 50) {
					platforms[i]->setColor(GRAY);
				}

				if (choice >= 50) {
					platforms[i]->setColor(ORANGE);
				}
			}
			break;
		default:
			for (int i = 0; i < count; i++) {
				platforms[i]->setColor(GRAY);
			}
	}
}

void Pattern::generatePlatforms(float offsetX, float offsetZ, float distance, int direction, int type)
{
	translate(offsetX, 0, offsetZ);

	for (int i = 0; i < count; i++) {
		createType(type);
	}

	if (direction == MIDDLE) {
		int odd = 1;
		int even = 0;
		int j = 0;
		for (int i = 1; i < count; i++) {
			int chance = rand() % 100;

			if (i % 2 == 0) {
				platforms[i]->translate(-distance * (i - odd), 0, 0);
				if (chance < 50 && j < count / 3) {
					obstacles[j]->setRendered(true);
					obstacles[j++]->translate(-distance * (i - odd),
						OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
						-platforms[i]->getLength() / 2);
				}
				odd++;
			}
			else {
				platforms[i]->translate(distance * (i - even), 0, 0);
				if (chance > 50 && j < count / 3) {
					obstacles[j]->setRendered(true);
					obstacles[j++]->translate(distance * (i - even),
						OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y, 
						-platforms[i]->getLength() / 2);
				}
				even++;
			}
		}
	}

	if (direction == LEFT) {
		int j = 0;
		for (int i = 1; i < count; i++) {
			int chance = rand() % 100;
			platforms[i]->translate(-distance * i, 0, 0);
			if (chance < 30 && j < count / 3) {
				obstacles[j]->setRendered(true);
				obstacles[j++]->translate(-distance * i,
					OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2);
			}
		}
	}

	if (direction == RIGHT) {
		int j = 0;
		for (int i = 1; i < count; i++) {
			int chance = rand() % 100;
			platforms[i]->translate(distance * i, 0, 0);
			if (chance > 60 && j < count / 3) {
				obstacles[j]->setRendered(true);
				obstacles[j++]->translate(distance * i,
					OBSTACLE_SIZE + platforms[i]->getHeight() / 2 + platforms[i]->getPosition().y,
					-platforms[i]->getLength() / 2);
			}
		}
	}
}

void Pattern::resetPlatforms()
{
	for (int i = 0; i < count; i++) {
		float width = platforms[i]->getWidth();
		float height = platforms[i]->getHeight();
		float length = platforms[i]->getLength();
		float init = platforms[i]->getInitSize();
		
		platforms[i]->scale(init/width, init/height, init/length);

		platforms[i]->setPosition(glm::vec3(0));

		platforms[i]->setColor(WHITE);
	}

	for (int i = 0; i < count / 3; i++) {
		float width = obstacles[i]->getWidth();
		float height = obstacles[i]->getHeight();
		float length = obstacles[i]->getLength();
		float init = obstacles[i]->getInitSize();

		obstacles[i]->scale(init / width, init / height, init / length);

		obstacles[i]->setPosition(glm::vec3(0));

		obstacles[i]->setColor(WHITE);

		obstacles[i]->setRendered(false);
	}
}