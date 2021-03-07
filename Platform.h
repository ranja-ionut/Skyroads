#pragma once

#include <Core/Engine.h>
#include "Player.h"

class Platform {
	public:
		static bool willLand;

		Platform();
		Platform(glm::vec3 center, float init_size);
		~Platform();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setLength(float newLength);
		void setWidth(float newWidth);
		void setHeight(float newHeight);
		void setColor(glm::vec3 newColor);

		void checkLanding(Player* player);
		void checkIfLanded(Player* player);
		void updatePlayer(Player* player);
		void translate(float newX, float newY, float newZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		glm::mat4 getMatrix();
		glm::vec3 getCenter();
		float getLength();
		float getWidth();
		float getHeight();
		float getInitSize();
		glm::vec3 getPosition();
		glm::vec3 getColor();

	private:
		float init_size;
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float width, length, height;
		glm::vec3 position;
		glm::vec3 color;
};