#pragma once

#include <string>
#include "GamEngine/Core/Core.h"

namespace GamEngine {
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;
		//virtual uint32_t get_format() const = 0;
		
		virtual void bind(uint32_t slot = 0) const = 0;
	};
}