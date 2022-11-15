#pragma once

#include "VertexArray.h"

namespace Pangolin {
	class VoidVertexArray : public VertexArray {
	public:
		virtual ~VoidVertexArray() {};

		inline virtual void bind() const override {};
		inline virtual void unbind() const override {};

		inline virtual void add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer) override {};
		inline virtual void set_index_buffer(const Ref<IndexBuffer>& index_buffer) override {};
	};
}