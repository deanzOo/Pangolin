#include "gepch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <filesystem>
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace Pangolin {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		else if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		GE_CORE_ASSERT(false, "Unkown shader type ({0})", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		std::unordered_map<GLenum, ShaderComponents> sources = load_from_path(path);

		GLuint program = glCreateProgram();
		GE_CORE_ASSERT(sources.size() == 2, "Only support for exactly 2 shader sources currently");
		std::array<GLenum, 2> gl_shader_ids;;
		int shader_id = 0;
		std::string shader_name;
		for (auto& kv : sources) {
			GLenum type = kv.first;
			const std::string& raw_source = kv.second.src;
			shader_name = kv.second.name;

			GLuint shader = glCreateShader(type);

			const GLchar* source = raw_source.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
			GE_CORE_ASSERT(is_compiled, "Shader Compilation failure!");
			if (is_compiled == GL_FALSE)
			{
				GLint max_length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

				std::vector<GLchar> info_log(max_length);
				glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

				glDeleteShader(shader);

				GE_CORE_ERROR("{0}", info_log.data());

				break;
			}
			glAttachShader(program, shader);
			gl_shader_ids[shader_id++] = shader;
		}
		_name = shader_name;

		glLinkProgram(program);

		GLint is_linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> info_log(max_length);
			glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

			glDeleteProgram(program);
			for (auto id : gl_shader_ids)
				glDeleteShader(id);

			GE_CORE_ASSERT(is_linked, "Program Link failure! ({0})", info_log.data());

			return;
		}

		for (auto id : gl_shader_ids)
			glDetachShader(program, id);

		_renderer_id = program;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& path): OpenGLShader(path)
	{
		_name = name;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_renderer_id);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(_renderer_id);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}


	void OpenGLShader::upload_uniform_int(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::upload_uniform_float(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform1f(location, value);
	}
	
	void OpenGLShader::upload_uniform_float2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::upload_uniform_float3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::upload_uniform_float4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::upload_uniform_mat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::upload_uniform_mat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(_renderer_id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::read_file(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		GE_CORE_ASSERT(in, "Could not open file '{0}'", filepath);
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
		return result;
	}

	std::unordered_map<GLenum, ShaderComponents> OpenGLShader::load_from_path(const std::string& path) {
		std::unordered_map<GLenum, ShaderComponents> shader_sources;

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			std::string filepath = entry.path().string();

			std::string filename = filepath.substr(filepath.find_last_of("/") + 1);

			int format_dot_count = std::count(filename.begin(), filename.end(), '.');
			GE_CORE_ASSERT(format_dot_count == 2, "Shader asset naming convention: '<shader_name>.<shader_type>.glsl' instead receieved '{0}'", filename);

			size_t name_end_index = filename.find_first_of(".");
			size_t type_end_index = filename.find_last_of(".");
			size_t type_len = type_end_index - 1 - name_end_index;

			std::string name = filename.substr(0, name_end_index);
			std::string type = filename.substr(name_end_index + 1, type_len);
			std::string extension = filename.substr(type_end_index + 1);

			ShaderComponents shader_components;
			shader_components.name = name;
			shader_components.src = read_file(filepath);

			shader_sources[ShaderTypeFromString(type)] = shader_components;
		}

		return shader_sources;
	}

}