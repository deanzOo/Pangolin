#include "plpch.h"

#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Pangolin {
	void OpenGLRendererAPI::init() {
		PL_PROFILE_FUNCTION();
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::set_clear_color(const glm::vec4& color)
	{
		PL_PROFILE_FUNCTION();
		
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		PL_PROFILE_FUNCTION();
		
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::clear()
	{
		PL_PROFILE_FUNCTION();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::draw_indexed(const Ref<VertexArray>& vertex_array, uint32_t index_count)
	{
		PL_PROFILE_FUNCTION();
		
		uint32_t count = index_count ? vertex_array->get_index_buffer()->get_count() : index_count;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
