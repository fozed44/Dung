#pragma once

#include <SDL.h>
#include "SDL_ttf.h"
#include <string>
#include <memory>


namespace mp::gfx{

	class TextSheet;
	using TextSheetHandle = ::std::shared_ptr<TextSheet>;

	/// <summary>
	/// A texture containing ascii characters.
	/// </summary>
	class TextSheet {
		// Define the glyph range that will be loaded into
		static const char GLYPH_START = ' ';
		static const char GLYPH_END = 'z';
		static_assert(GLYPH_START < GLYPH_END);
		// MAX_GLYPHS determines the size of the memory block we
		// allocate for _pGlyphs.   
		static const int MAX_GLYPHS = 128;

		SDL_Texture*              _pTextSheet;
		std::unique_ptr<SDL_Rect> _pGlyphs;

		// The width and height of the characters in the loaded
		// font. 
		int _characterWidth;
		int _characterHeight;

		// Calculated based on the number of glyphs in the sheet
		// and _characterWidth and _characterHeight
		int _textureWidth;
		int _textureHeight;

		TextSheet(TextSheet&)    = delete;
		TextSheet(TextSheet&& o) = delete;
	public:

		TextSheet(
			const std::string& filename,
			int                fontSize,
			int                characterWidth,
			int                characterHeight,
			uint8_t			   r,
			uint8_t			   g,
			uint8_t			   b
		);

		virtual ~TextSheet();

		void RenderChar(char c, const SDL_Point& targetLocation);
		void RenderString(const std::string& s, SDL_Point targetLocation);

		int GetCharacterWidth() { return _characterWidth; }
		int GetCharacterHeight() { return _characterHeight; }

		SDL_Texture* getTexture() { return _pTextSheet; }
	};
}
