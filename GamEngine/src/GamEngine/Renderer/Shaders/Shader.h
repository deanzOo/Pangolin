#pragma once

namespace GamEngine {
	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& get_name() const = 0;

		static Ref<Shader> create(const std::string& path);
		static Ref<Shader> create(const std::string& name, const std::string& path);
	};
}