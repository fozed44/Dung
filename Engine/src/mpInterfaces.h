#pragma once

#include "Scene.h"
#include "SDL.h"

namespace mp {

	/// <summary>
	/// An object that can be rendered.
	/// </summary>
	class IRenderable {
	public:
		virtual ~IRenderable() = 0 {};
		virtual void Render(const IScene* pScene) = 0;
	};
}
