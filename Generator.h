#pragma once

#include <Core/Engine.h>
#include "Pattern.h"

class Generator {
	public:
		Generator();
		~Generator();

		void checkLanding(Player* player);
		void checkIfLanded(Player* player);
		void translate(float newX, float newY, float newZ);
		void generate(Pattern* pattern);
		void setGone(int pattern_id);

		Pattern** getPatterns();
		bool isGone(int pattern_id);

	private:
		Pattern* patterns[PATTERN_COUNT];
		bool gone[PATTERN_COUNT];
		float max_distance;
		int furthest_pattern;
		int last_direction;
		int last_type;
};