#pragma once

#include <string>
#include <toolbox/Matrix4x4.h>

#include "resources/resource.h"
#include "utils/flag.h"

class UNDEFINED_ENGINE Shader : public Resource
{
public:
    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void Use();
    // unUse/desactivate the shader
    void UnUse();
    // set Vertex Shader
    unsigned int SetVertexShader(unsigned int vertex, const char* vShaderCode);
    // set Fragment Shader
    unsigned int SetFragmentShader(unsigned int fragment, const char* fShaderCode);
    // Link 
    void Link(unsigned int vertex, unsigned int fragment);
    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, Vector3 v) const;
    void SetMat4(const std::string& name, Matrix4x4 m) const;

    void Load(const char* vertexPath, const char* fragmentPath);

    // the program ID
    unsigned int ID = 0;
};

