#include "gepch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <filesystem>
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace GamEngine {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		else if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		GE_CORE_ASSERT(false, "Unkown shader type " + type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		std::unordered_map<GLenum, std::string> sources = load_from_path(path);

		GLuint program = glCreateProgram();
		std::vector<unsigned int> gl_shader_ids(sources.size());
		for (auto& kv : sources) {
			unsigned int type = kv.first;
			const std::string& raw_source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* source = raw_source.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
			if (is_compiled == GL_FALSE)
			{
				GLint max_length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

				std::vector<GLchar> info_log(max_length);
				glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

				glDeleteShader(shader);

				GE_CORE_ERROR("{0}", info_log.data());
				GE_CORE_ASSERT(is_compiled, "Shader Compilation failure!");

				break;
			}
			glAttachShader(program, shader);
			gl_shader_ids.push_back(shader);
		}

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

			GE_CORE_ERROR("{0}", info_log.data());
			GE_CORE_ASSERT(is_linked, "Program Link failure!");

			return;
		}

		for (auto id : gl_shader_ids)
			glDetachShader(program, id);

		_renderer_id = program;
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
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		GE_CORE_ASSERT(in, "Could not open file " + filepath);
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::load_from_path(const std::string& path) {
		std::unordered_map<GLenum, std::string> shader_sources;

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			std::string filepath = entry.path().string();

			char* path = strtok(const_cast<char*>(filepath.c_str()), ".");
			std::string str_path(path, strlen(path));

			char* type = strtok(nullptr, ".");
			std::string str_type(type, strlen(type));

			char* extension = strtok(nullptr, ".");
			std::string str_extension(extension, strlen(extension));

			std::string fullpath = str_path + "." + str_type + "." + str_extension;
			
			shader_sources[ShaderTypeFromString(type)] = read_file(fullpath);
		}

		return shader_sources;
	}

}