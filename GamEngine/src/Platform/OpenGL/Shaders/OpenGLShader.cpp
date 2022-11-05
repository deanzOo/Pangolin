#include "gepch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

namespace GamEngine {
	OpenGLShader::OpenGLShader(const std::string& vertex_src, const std::string& fragment_src) {
		// Create an empty vertex shader handle
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertex_src.c_str();
		glShaderSource(vertex_shader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertex_shader);

		GLint is_compiled = 0;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
		if (is_compiled == GL_FALSE)
		{
			GLint max_length = 0;
			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

			// The maxLength includes the NULL character
			std::vector<GLchar> info_log(max_length);
			glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertex_shader);

			// Use the infoLog as you see fit.
			GE_CORE_ERROR("{0}", info_log.data());
			GE_CORE_ASSERT(is_compiled, "Vertex Shader Compilation failure!");

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragment_src.c_str();
		glShaderSource(fragment_shader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragment_shader);

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
		if (is_compiled == GL_FALSE)
		{
			GLint max_length = 0;
			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

			// The maxLength includes the NULL character
			std::vector<GLchar> info_log(max_length);
			glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragment_shader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertex_shader);

			// Use the infoLog as you see fit.
			GE_CORE_ERROR("{0}", info_log.data());
			GE_CORE_ASSERT(is_compiled, "Fragment Shader Compilation failure!");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_renderer_id = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_renderer_id, vertex_shader);
		glAttachShader(m_renderer_id, fragment_shader);

		// Link our program
		glLinkProgram(m_renderer_id);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint is_linked = 0;
		glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &max_length);

			// The maxLength includes the NULL character
			std::vector<GLchar> info_log(max_length);
			glGetProgramInfoLog(m_renderer_id, max_length, &max_length, &info_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_renderer_id);
			// Don't leak shaders either.
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			// Use the infoLog as you see fit.
			GE_CORE_ERROR("{0}", info_log.data());
			GE_CORE_ASSERT(is_linked, "Program Link failure!");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_renderer_id, vertex_shader);
		glDetachShader(m_renderer_id, fragment_shader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_renderer_id);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_renderer_id);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

}