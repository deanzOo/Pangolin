#pragma once

#include <string>
#include "Pangolin/Core/Core.h"

namespace Pangolin {
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;
		virtual uint32_t get_renderer_id() const = 0;

		virtual void set_data(void* data, uint32_t size) = 0;
		
		virtual void bind(uint32_t slot = 0) const = 0;
	};
}