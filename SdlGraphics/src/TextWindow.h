#pragma once

#include "Window.h"
#include "TextSheet.h"

namespace mp::gfx {

	/// <summary>
	/// Base class for renderer that render text.
	/// 
	/// TextRenderer provides support for calculating the width and height (in characters) of the
	/// render area, based on the size of the render rect.
	/// </summary>
	class TextWindow : public Window {

	private:

		/// <summary>
		/// recalculates the size of the char view port.
		/// </summary>
		void CalculateMaxCharViewPortSize();

		/// <summary>
		/// The width of the view port in characters.
		/// </summary>
		int _maxViewPortWidthInChars;

		/// <summary>
		/// The height of the view port in characters.
		/// </summary>
		int _maxViewPortHeightInChars;

	protected:

		/// <summary>
		/// The sheet containing the glyphs used by the renderer.
		/// </summary>
		TextSheetHandle _pTextSheet;
	 	
		/// <summary>
		/// When the window rect changes, we will update the
		/// max char view port with and height. (if possible,
		/// assuming that the text sheet has been set)
		/// </summary>
		virtual void WindowRectChanged() override;

		/// <summary>
		/// called by Set text sheet. After the max characters
		/// width and height has been recalculated.
		/// </summary>
		virtual void TextSheetChanged() {}

	public:
		TextWindow(int width, int height);
		virtual ~TextWindow() {}

		int GetMaxViewPortWidthInChars()  const { return _maxViewPortHeightInChars; }
		int GetMaxViewPortHeightInChars() const { return _maxViewPortHeightInChars; }

		void SetTextSheet(const TextSheetHandle&);
	};
}
