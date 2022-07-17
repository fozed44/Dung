#pragma once

#include <SDL_rect.h>
#include <SDL.h>
#include <vector>
#include "CharacterConditions.h"
#include "Stats.h"

namespace mp {

	class Character {
	private:
		SDL_Point                       _location;
		std::vector<CharacterCondition> _conditions;
		Stats                           _stats;
		char                            _tile;
		SDL_Color                       _color;

	protected:
		virtual void LocationChanged()                     {};

		virtual CharacterCondition ApplyingCondition(CharacterCondition condition) { return condition; }
		virtual void ConditionApplied(CharacterCondition)  {}

		virtual void ConditionRemoved(CharacterCondition)  {}
		virtual bool RemovingCondition(CharacterCondition) { return true; }

	public:
		Character(const SDL_Point&);
		~Character() {}

		const SDL_Point& GetLocation() const { return _location; }
		void  SetLocation(const SDL_Point&);

		char  GetTile()             const { return _tile; }
		const SDL_Color& GetColor() const { return _color; }

		void ApplyCondition(CharacterCondition);
		bool HasCondition(CharacterCondition) const;
		void RemoveCondition(CharacterCondition);

	};
}
