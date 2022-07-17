#include "TextSheet.h"
#include "Exception.h"
#include "SDL_ttf.h"
#include <string.h>
#include <format>
#include "SDLGraphics.h"

using namespace mp::gfx;

TextSheet::TextSheet(
	const std::string& filename,
	int                fontSize,
	int                characterWidth,
	int                characterHeight,
	uint8_t			   r,
	uint8_t			   g,
	uint8_t			   b
) {
	_characterWidth  = characterWidth;
	_characterHeight = characterHeight;

	// This is not a perfect calculation to make the characters tightly in a
	// texture. It is over-sized, but just a bit, so good enough.
	_textureWidth  = static_cast<int>(sqrt((GLYPH_END - GLYPH_START)) + 2) * _characterWidth;
	_textureHeight = static_cast<int>(sqrt((GLYPH_END - GLYPH_START)) + 2) * _characterHeight;

	_pGlyphs = std::unique_ptr<SDL_Rect>(static_cast<SDL_Rect*>(malloc(sizeof(SDL_Rect) * MAX_GLYPHS)));
	memset(_pGlyphs.get(), 0, sizeof(SDL_Rect) * MAX_GLYPHS);

	// Ensure that SDL_TTF is initialized. This method should be fine to call
	// repeatedly.
	ThrowWhenNotZero<MpGraphicsInitException>(
		TTF_Init(),
		std::format("Failed initialize {} TTF Error: _se", filename)
	);

	TTF_Font* pFont = ThrowWhenNull<MpGraphicsException>(
		TTF_OpenFont(filename.c_str(), fontSize), 
		std::format("Failed to load font {}\n Error: _se", filename)
	);

	// The surface we will copy pCharSurfaces to. When it
	// we have copied all chars to this surface, it will be
    // copied into the _pTextSheet.
	SDL_Surface* pTextureSurface = ThrowWhenNull<MpGraphicsException>(
		SDL_CreateRGBSurface(0, _textureWidth, _textureHeight, 32, 0, 0, 0, 0xff),
		"Failed create surface Error : _se"
	);

	ThrowWhenNotZero<MpGraphicsException>(
		SDL_SetColorKey(pTextureSurface, SDL_TRUE, SDL_MapRGBA(pTextureSurface->format, 0, 0, 0, 0)),
		"Failed to set color key. _e"
	);

	SDL_Rect  dest   { 0, 0, characterWidth, characterHeight };

	for (char i = GLYPH_START; i <= GLYPH_END; i++) {
		char c[2] = { i, 0 };

		SDL_Surface* pCharSurface = TTF_RenderUTF8_Blended(pFont, c, { r, g, b });
		ThrowWhenNull<MpGraphicsException>(pCharSurface, "Failed to render blended surface. _se");

		SDL_Rect  source { 0, 0, 0, 0 };
		TTF_SizeText(pFont, c, &source.w, &source.h);

		if (dest.x + _characterWidth >= _textureWidth) {
			dest.x = 0;
			dest.y += _characterHeight;

			if (dest.y + _characterHeight >= _textureHeight) {
				Throw<MpGraphicsException>(
					std::format("Out of glyph space in {}x{} font atlas texture map.\n Error: _se", _textureWidth, _textureHeight)
				);
			}
		}
		
		SDL_BlitScaled(pCharSurface, &source, pTextureSurface, &dest);

		SDL_Rect* pGlyphRect = &_pGlyphs.get()[i];

		pGlyphRect->x = dest.x;
		pGlyphRect->y = dest.y;
		pGlyphRect->w = dest.w;
		pGlyphRect->h = dest.h;

		SDL_FreeSurface(pCharSurface);

		dest.x += _characterWidth;
	}

	_pTextSheet = SDL_CreateTextureFromSurface(
		SDLGraphics::Instance()->GetRenderer(),
		pTextureSurface
	);
};

TextSheet::~TextSheet() {
	if (_pTextSheet)
		SDL_DestroyTexture(_pTextSheet);
}

/// <summary>
/// Render a character to a target location. The target location
/// will be relative to the UL corner of the window that the renderer
/// is attached to.
/// </summary>
/// <param name="pRenderer">
/// The render.
/// </param>
/// <param name="c">
/// The character to be rendered
/// </param>
/// <param name="targetLocation">
/// The upper left hand corner of the character on the target.
/// </param>
void TextSheet::RenderChar(char c, const SDL_Point& targetLocation) {
	if (c < GLYPH_START || c > GLYPH_END) {
		Throw<MpGraphicsException>(
			std::format("character out of range {}", c)
		);
	}

	SDL_Rect targetRect {
		targetLocation.x,
		targetLocation.y,
		_characterWidth,
		_characterHeight
	};

	SDL_RenderCopy(
		SDLGraphics::Instance()->GetRenderer(),
		_pTextSheet,
		&_pGlyphs.get()[c],
		&targetRect
	);
}

/// <summary>
/// Render a string to a target location. The target location
/// will be relative to the UL corner of the window that the renderer
/// is attached to.
/// </summary>
/// <param name="pRenderer">
/// The renderer.
/// </param>
/// <param name="s">
/// The string that will be rendered.
/// </param>
/// <param name="targetLocation">
/// The location relative to the UL corner of the window attached
/// to the renderer.
/// </param>
void TextSheet::RenderString(const std::string& s, SDL_Point targetLocation) {
	for (auto c : s) {
		RenderChar(c, targetLocation);
		targetLocation.x += _characterWidth;
	};
}
