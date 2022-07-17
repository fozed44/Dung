#include "Character.h" 

using namespace mp;

Character::Character(const SDL_Point& location) {
	_location = location;
}

void Character::SetLocation(const SDL_Point& location) {
	_location = location;
	LocationChanged();
}

void Character::ApplyCondition(CharacterCondition condition) {
	condition = ApplyingCondition(condition);

	if (condition != CharacterCondition::None) {
		_conditions.push_back(condition);
		ConditionApplied(condition);
	}
}

void Character::RemoveCondition(CharacterCondition condition) {
	if (RemovingCondition(condition)) {
		std::erase(_conditions, condition);
		ConditionRemoved(condition);
	}
}

bool Character::HasCondition(CharacterCondition condition) const {
	return std::find(
		_conditions.begin(), _conditions.end(), condition
	) != _conditions.end();
}
