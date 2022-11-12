#pragma once

#include <string>
#include <unordered_map>
#include "GamEngine/Core/Core.h"
#include "Shader.h"

namespace GamEngine {
	class ShaderLibrary {
	public:
		void add(const Ref<Shader>& shader);
		Ref<Shader> load(const std::string& path);

		Ref<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;
	};
}