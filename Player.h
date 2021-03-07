#pragma once

#include <Core/Engine.h>
#include "Transform3D.h"
#include "Constants.h"

class Player {
	public:
		Player();
		Player(glm::vec3 center, float diameter);
		~Player();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setGround(float newGround);
		void setJump(bool isJumping);
		void setFall(bool isFalling);
		void setFallTime(float newTime);
		void setOldGround(float ground);
		void setDeath(bool death);
		void setBlock(bool block);
		void setFuel(float newFuel);
		void setAcceleration(float newAcceleration);
		void setOldAccel(float oldAccel);
		void setMinAccel(float newAccel);
		void setBlockedTime(float newTime);
		void setPowerUp(bool power);
		void setPowerUpTime(float newTime);
		void setDeathTime(float newTime);
		void setDeathType(int newType);
		void setDifficultyTime(float newTime);
		void setInvincible(bool invincible);
		void setInvincibilityTime(float newTime);

		void doJump(float deltaTime, float jumpHeight);
		void doFall(float deltaTime);
		void translate(float newX, float newY, float newZ);
		void useFuel(float deltaTime);

		glm::mat4 getMatrix();
		glm::vec3 getCenter();
		glm::vec3 getPosition();
		float getDiameter();
		float getGround();
		float getOldGround();
		float getFuel();
		float getAcceleration();
		float getMinAccel();
		float getBlockedTime();
		float getPowerUpTime();
		float getDeathTime();
		float getDifficultyTime();
		float getInvincibilityTime();
		int getDeathType();
		bool isJumping();
		bool isFalling();
		bool isDead();
		bool isBlocked();
		bool getPowerUp();
		bool isInvincible();


	private:
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float diameter;
		glm::vec3 position;
		float ground, oldGround;
		bool jumping;
		bool falling;
		bool death;
		bool blocked;
		bool powerUp;
		bool invincible;
		float blockedTime;
		float invincibilityTime;
		float fuel;
		float fallTime;
		float acceleration, oldAccel, minAccel;
		float difficultyTimer;
		float powerUpTime;
		float deathTime;
		int deathType;
};