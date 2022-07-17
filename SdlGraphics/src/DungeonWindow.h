#pragma once

#include "TextWindow.h"
#include "TextSheet.h"
#include "mpInterfaces.h"

namespace mp::gfx {

	class TextSheet;

	class DungeonWindow : public TextWindow {
	public:
		using TextWindow::TextWindow;
		virtual ~DungeonWindow() {};

		virtual void Render(const IScene*) override;
	};
}
