#pragma once

#include <memory>
#include <SDL.h>
#include "TextSheet.h"

namespace mp::gfx {

	/// <summary>
	/// Wraps some basic high level SDL graphics objects.
	/// 
	/// currently we are wrapping the SDL_Window and the SDL_Renderer objects and managing
	/// the lifetime of these objects in the constructor and destructor.
	/// </summary>
	class SDLGraphics {
		SDL_Window*   _pWindow;
		SDL_Renderer* _pRenderer;
		int           _width;
		int           _height;

		SDLGraphics(int width, int height);

		static SDLGraphics* _instance;
		virtual ~SDLGraphics();

	public:

		/// <summary>
		/// Get the current instance ( the instance created by calling InitializeInstance )
		/// </summary>
		static SDLGraphics* Instance() { return _instance; };


		/// <summary>
		/// Create a new instance. Calling the Instance method will also get a pointer
		/// to the instance created by InitializeInstance.
		/// </summary>
		static SDLGraphics* InitializeInstance(int width, int height);

		/// <summary>
		/// Destroy the current instance.
		/// </summary>
		static void DestroyInstance();

		/// <summary>
		/// Gets a pointer to the SDL_Window object.
		/// </summary>
		SDL_Window*   GetWindow()   { return _pWindow;   }

		/// <summary>
		/// Gets a pointer to the 
		/// </summary>
		SDL_Renderer* GetRenderer() { return _pRenderer; }
		
		TextSheetHandle LoadTextSheet(
			const std::string& filename,
			int                fontSize,
			int                characterWidth,
			int                characterHeight,
			uint8_t			   r = 0xFF,
			uint8_t			   g = 0xFF,
			uint8_t			   b = 0xFF
		);

		int GetWidth()  const { return _width;  }

		int GetHeight() const { return _height; }
	};
}
