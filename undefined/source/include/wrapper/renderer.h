#pragma once

#include <toolbox/Matrix4x4.h>
#include <toolbox/Vector3.h>

#include "engine_debug/renderer_debug.h"
#include "wrapper/service_type.h"
#include "utils/flag.h"

class UNDEFINED_ENGINE Renderer : public ServiceType
{
public:
	void Init();

	void SetClearColor(float redBaseColor = 0.3f, float greenBaseColor = 0.3f, float blueBaseColor = 0.3f);
	void ClearBuffer();
	

	void BindTexture(unsigned int ID);
	void BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO);

	unsigned int SetShader(int shaderType, const char* vShaderCode);
	unsigned int LinkShader(unsigned int ID, unsigned int vertex, unsigned int fragment);

	void UseShader(int ID);
	void UnUseShader();

	void SetUniform(unsigned int ID, const std::string& name, bool value) const;
	void SetUniform(unsigned int ID, const std::string& name, int value) const;
	void SetUniform(unsigned int ID, const std::string& name, float value) const;
	void SetUniform(unsigned int ID, const std::string& name, Vector3 v) const;
	void SetUniform(unsigned int ID, const std::string& name, Matrix4x4 m) const;

	void DeleteShader(unsigned int shader);

	RendererDebug Debug;
};

