#pragma once

#include <Core/Engine.h>
#include "Platform.h"
#include "Obstacle.h"
#include "Object3D.h"

class Pattern {
	public:
		Pattern();
		Pattern(int count, int pattern_id);
		~Pattern();

		int getCount();
		int getId();
		Platform** getPlatforms();
		Obstacle** getObstacles();
		float getLeft();
		float getRight();
		float getUp();
		float getDown();

		void checkLanding(Player* player);
		void checkIfLanded(Player* player);
		void translate(float newX, float newY, float newZ);
		void createPlatforms();
		void createType(int type);
		void generatePlatforms(float offsetX, float offsetZ, float distance, int direction, int type);
		void resetPlatforms();

	private:
		int count;
		int pattern_id;
		Platform** platforms;
		Obstacle** obstacles;
};