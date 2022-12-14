#include "plpch.h"
#include "ShaderLibrary.h"

namespace Pangolin {
    void ShaderLibrary::add(const Ref<Shader>& shader)
    {
        auto& name = shader->get_name();
        PL_CORE_ASSERT(!exists(name), "Shader already exists!");
        _shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& path)
    {
        auto shader = Shader::create(path);
        add(shader);
        return shader;
    }


    Ref<Shader> ShaderLibrary::get(const std::string& name)
    {
        PL_CORE_ASSERT(exists(name), "Shader not found!");
        return _shaders[name];
    }

    bool ShaderLibrary::exists(const std::string& name) const {
        return _shaders.find(name) != _shaders.end();
    }
}
