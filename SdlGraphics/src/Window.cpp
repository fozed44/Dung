#include "Window.h"
#include "SDLGraphics.h"


using namespace mp::gfx;

/// <summary>
/// Create a new window of the given size.
/// </summary>
Window::Window(int width, int height) 
	: RenderRect({ 0, 0, width,	height}), 
	_windowRect { 0, 0, width, height } { }

void Window::AddChild(
	const WindowHandle& parent,
	const WindowHandle& child,
	const SDL_Point& position
) {
	// Set the _parent pointer on the child
	child->_parent = parent;

	// Add the child to the parents list of children.
	parent->_children.push_back(child);

	child->SetWindowRect({
		position.x,
		position.y,
		child->_windowRect.w,
		child->_windowRect.h
	});
}

void Window::RemoveChild(const WindowHandle& child) {
	std::erase(_children, child);
	child->_parent = nullptr;
}

bool  Window::SetWindowRect(const SDL_Rect& rect) {

	if (!CanSetWindowRect(rect))
		return false;

	_windowRect = rect;

	UpdateRenderRects();

	WindowRectChanged();

	return true;
}

bool Window::CanSetWindowRect(const SDL_Rect& rect) {
	// Regardless of whether or not we have a parent, the rect must be positioned
	// in a positive location.
	if (rect.x < 0 || rect.y < 0)
		return false;

	if (_parent) {
		// If this window has a parent, the right and bottom edges must be within
		// the parents rect.
		if (rect.x + rect.w > _parent->_windowRect.w)
			return false;

		if (rect.y + rect.h > _parent->_windowRect.h)
			return false;
	} else {
		// Otherwise the right and bottom edges must be within the boundaries of
		// the top level window.
		if (rect.x + rect.w > SDLGraphics::Instance()->GetWidth())
			return false;

		if (rect.y + rect.h > SDLGraphics::Instance()->GetHeight())
			return false;
	}

	// If any child's right edge is out side of the right and bottom edges of
	// the new rect, we are returning false.
	for (auto& child : _children) {
		if (child->_windowRect.x + child->_windowRect.w > rect.w)
			return false;

		if (child->_windowRect.y + child->_windowRect.h > rect.h)
			return false;
	}

	// Everything is ok.
	return true;
}

void Window::UpdateRenderRects() {
	if (_parent) {
		auto parentRenderRect = _parent->GetRenderRect();
		// The new UL position of this render rect will be
		// The parents render rect position (render rect is in
		// screen space) plus the this window's position relative
		// to its parent (_windowRect.{x, y})
		SetRenderRect({
			parentRenderRect.x + _windowRect.x,
			parentRenderRect.y + _windowRect.y,
			_windowRect.w,
			_windowRect.h
		});
	}
	else {
		// If this window does not have a parent, the _windowRect
		// is relative to { 0, 0 }.
		SetRenderRect(_windowRect);
	}

	for (auto& child : _children)
		child->UpdateRenderRects();
}

/// <summary>
/// Calls render on each child. Main use as a base class call at the
/// end of subclass implementations.
/// </summary>
void Window::Render(const IScene* pScene) {
	for (auto& child : _children)
		child->Render(pScene);
}

