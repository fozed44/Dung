#pragma once

#include "TextWindow.h"

namespace mp::gfx {
	class TextOverlayWindow : public TextWindow {
	public:
		using TextWindow::TextWindow;
		virtual ~TextOverlayWindow() {}


		virtual void Render(const IScene* pScene) override;
	};
}

