#pragma once

#include "sdl_rect.h"

namespace mp::gfx {

	/// <summary>
	/// Wrapper over a SDL_Rect that adds boundary validation against the top level window.
	///
	/// This rect type always represents a rect in coordinates relative to the top level window.
	///
	/// Note that SetRect is protected. The RenderRect is intended to be a base class of something
	/// more intelligent like a window. Since the subclass should be managing the location of
	/// the rect based on some higher level concept (a window for example keeps track of a location
	/// relative to a parent) the SetRect method is protected.
	/// </summary>
	class RenderRect {
		// _rect is a rectangle relative to the top level window, and represents the section of the window
		// that this renderer can render to. 
		SDL_Rect _rect;

	protected:

		/// <summary>
		/// Set a new rect. The rect must be within boundaries of the top level window.
		/// </summary>
		void  SetRenderRect(const SDL_Rect& rect);

	public:

		RenderRect(const SDL_Rect& rect) : _rect{ rect } {};
		virtual ~RenderRect() {}

		const SDL_Rect& GetRenderRect() const { return _rect; }
	};
}
