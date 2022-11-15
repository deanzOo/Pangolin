#pragma once

#include "Pangolin/Renderer/Textures/Texture.h"

namespace Pangolin {
	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> create(const std::string& path);
	};
}