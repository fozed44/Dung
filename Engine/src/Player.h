#pragma once

#include "Character.h"

namespace mp {

	class Player : public Character {
	public:
		using Character::Character;
		Player() : Character({ 0, 0 }) {};
	};
}
