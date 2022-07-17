#include "TextWindow.h"

using namespace mp::gfx;

TextWindow::TextWindow(int width, int height)
	: Window(width, height) {}

void TextWindow::CalculateMaxCharViewPortSize() {
	if (_pTextSheet) {
		_maxViewPortHeightInChars = GetWindowRect().w / _pTextSheet->GetCharacterWidth();
		_maxViewPortWidthInChars  = GetWindowRect().h / _pTextSheet->GetCharacterHeight();
	}
}

void TextWindow::WindowRectChanged() {
	CalculateMaxCharViewPortSize();
}

void TextWindow::SetTextSheet(const TextSheetHandle& textSheet) {
	_pTextSheet = textSheet;
	CalculateMaxCharViewPortSize();
	TextSheetChanged();
}
