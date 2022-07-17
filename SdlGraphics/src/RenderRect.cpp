#include "RenderRect.h"
#include "SDLGraphics.h"

using namespace mp::gfx;

void RenderRect::SetRenderRect(const SDL_Rect& rect) {
	_rect = rect;

	SDL_assert(_rect.x >= 0	&& _rect.x + _rect.w < SDLGraphics::Instance()->GetWidth());
	SDL_assert(_rect.y >= 0 && _rect.y + _rect.h < SDLGraphics::Instance()->GetHeight());
}
