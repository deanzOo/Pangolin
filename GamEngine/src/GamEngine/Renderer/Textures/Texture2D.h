#pragma once

#include "GamEngine/Renderer/Textures/Texture.h"

namespace GamEngine {
	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> create(const std::string& path);
	};
}