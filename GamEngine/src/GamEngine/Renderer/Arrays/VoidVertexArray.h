#pragma once

#include "VertexArray.h"

namespace GamEngine {
	class VoidVertexArray : public VertexArray {
	public:
		virtual ~VoidVertexArray() {};

		inline virtual void bind() const override {};
		inline virtual void unbind() const override {};

		inline virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override {};
		inline virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) override {};
	};
}