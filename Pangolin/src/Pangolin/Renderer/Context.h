#pragma once

namespace Pangolin {
	class Context {
	public:
		virtual ~Context() = default;

		virtual void init() = 0;
		virtual void swap_buffers() = 0;
	};
}