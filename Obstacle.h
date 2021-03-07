#pragma once

#include <Core/Engine.h>
#include "Player.h"

class Obstacle {
	public:
		Obstacle();
		Obstacle(glm::vec3 center, float init_size);
		~Obstacle();

		void setMatrix(glm::mat4 newMatrix);
		void setPosition(glm::vec3 newPosition);
		void setLength(float newLength);
		void setWidth(float newWidth);
		void setHeight(float newHeight);
		void setColor(glm::vec3 newColor);
		void setRendered(bool render);

		void checkHit(Player* player);
		void translate(float newX, float newY, float newZ);
		void scale(float scaleX, float scaleY, float scaleZ);

		glm::mat4 getMatrix();
		glm::vec3 getCenter();
		float getLength();
		float getWidth();
		float getHeight();
		float getInitSize();
		bool isRendered();
		glm::vec3 getPosition();
		glm::vec3 getColor();

	private:
		bool rendered;
		float init_size;
		glm::mat4 modelMatrix;
		glm::vec3 center;
		float width, length, height;
		glm::vec3 position;
		glm::vec3 color;
};