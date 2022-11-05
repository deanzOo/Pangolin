#pragma once

namespace GamEngine {
	class Buffer {
	public:
		virtual ~Buffer() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}