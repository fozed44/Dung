#pragma once

#include "SDL.h"
#include <vector>
#include <memory>
#include "RenderRect.h"
#include "mpInterfaces.h"

namespace mp::gfx {

	class Window;
	using WindowHandle = ::std::shared_ptr<Window>;

	/// <summary>
	/// Sets up a parent/child relationship between widows. 
    ///
	/// A note on the relationship between a Window's _windowRect and the base classes (Renderer)
	/// _rect field:
	///		_windowRect is always relative to the window parent
	///		_rect is always relative to the top level window, this should make some sense
	///     since the _rect is used for rendering purposes, while _windowRect is used for window
	///     layering.
	///
	/// The window alters the _rect of the Renderer whenever _windowRect is
	/// changed, thus a windows _rect should never be altered by anything except
	/// the window its self, and only when _windowRect is updated.
	/// </summary>
	class Window : RenderRect, IRenderable {

		/// <summary>
		/// _windowRect is the window rect relative to its parent. 
		/// If the window has no parent, then the position of _windowRect should always be 0, 0
		/// since this must be the top level window.
		/// </summary>
		SDL_Rect _windowRect;

		/// <summary>
		/// Points to the parent window, if there is one.
		/// </summary>
		WindowHandle _parent;

		/// <summary>
		/// maintain a list of child windows.
		/// </summary>
		std::vector<WindowHandle> _children;

		/// <summary>
		/// Called by SetWindowRect just after _windowRect has been updated. The method updates
		/// the _renderRect based on the new position of the _windowRect.
		///
		/// Note that the method is called UpdateRenderRect(s). This method calls itself on
		/// children also.
		/// </summary>
		void UpdateRenderRects();

	protected:

		/// <summary>
		/// Called after the WindowRect has been changed, allowing
		/// subclasses a chance to react.
		/// </summary>
		virtual void WindowRectChanged() {};

	public:

		/// <summary>
		/// Creates a window of the given width and height. The window
		/// will be initialized at position 0, 0 with no parent.
		/// </summary>
		Window(int width, int height);

		virtual ~Window() {}

		/// <summary>
		/// Add 'child' as a child to 'parent'. 
		///
		/// This child is moved to 'position', relative to this window.
		/// The child must be able to fit inside this window, given 'position',
		/// meaning that position.x + child.width must be <= this.width. Same for
		/// the height.
		/// 
		/// Note: the child window must not be a child of another window.
		/// </summary>
		static void AddChild(
			const WindowHandle& parent,
			const WindowHandle& child, 
			const SDL_Point& position
		);

		/// <summary>
		/// Remove a child from this window.
		/// </summary>
		void RemoveChild(const WindowHandle& child);

		const SDL_Rect& GetWindowRect() const { return _windowRect; }

		/// <summary>
		/// Attempts to set the window rect. This method can fail if the new size of
		/// the window is too small to fit children.
		/// </summary>
		bool SetWindowRect(const SDL_Rect& rect);

		/// <summary>
		/// Return true if rect is of a valid size and position. This method can fail
		/// if the children of this window do not fit within the new rect.
		/// </summary>
		bool CanSetWindowRect(const SDL_Rect& rect);

		/// <summary>
		/// This implementation of render doesn't do much. It just
		/// calls render on children, but can be used by subclass for
		/// passing Render calls to children.
		/// </summary>
		void Render(const IScene* pScene);
	};
}
