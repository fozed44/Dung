#pragma once

#include "SDL.h"
#include "mpInterfaces.h"
#include "Window.h"
#include "TextSheet.h"


namespace mp::gfx {

	class DungeonWindow;
	class TextOverlayWindow;

	/// <summary>
	/// Layout is the base class for the layout system.
	/// 
	/// The Layout contains 
	/// lifetime. The render container also contains the sub-renderers that
	/// render various parts of the scene.
	/// </summary>
	class DungeonLayoutWindow : public Window {
		std::shared_ptr<DungeonWindow>     _pDungeonWindow;
		std::shared_ptr<TextOverlayWindow> _pOverlayWindow;
	public:
		DungeonLayoutWindow();
		virtual ~DungeonLayoutWindow();

		void SetDungeonWindow(const std::shared_ptr<DungeonWindow>& window) {
			_pDungeonWindow = window;
		}

		void SetTextOverlayWindow(const std::shared_ptr<TextOverlayWindow>& window) {
			_pOverlayWindow = window;
		}

		/// <summary>
		/// Render all Windows 
		/// </summary>
		virtual void Render(const IScene* pScene) override;

		void SetOverlayTextSheet(const TextSheetHandle& textSheet);

		void SetDungeonTextSheet(const TextSheetHandle& textSheet);

	};
}