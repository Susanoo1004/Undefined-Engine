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
	
	void GenTexture(unsigned int texNumber, unsigned int* ID);
	void GenerateBuffer(int index, unsigned int* buffer);
	void GenerateVertexArray(int index, unsigned int* buffer);
	void GenerateMipMap(unsigned int target);

	void ActiveTexture(unsigned int ID);

	//0x0DE1 = 3553U = GL_TEXTURE_2D
	void BindTexture(unsigned int ID, unsigned int type = 0x0DE1);
	//0x0DE1 = 3553U = GL_TEXTURE_2D
	void BindTexture(int framebufferTarget, int attachement, unsigned int ID, int format = 0x0DE1);
	void BindFramebuffer(unsigned int target, unsigned int framebufferID);
	void BindRenderbuffer(unsigned int renderbufferID);
	void BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO);
	void BindRenderbuffersToFramebuffers(int framebufferTarget, int attachements, unsigned int renderbufferID);

	void AttributePointers(unsigned int index, int size, unsigned int type, int stride, const void* pointer, bool isNormalized = false);
	void SetBufferData(unsigned int target, int size, const void* data, unsigned int usage);
	void SetRenderBufferStorageData(int target, int format, float width, float height);
	void SetTextureParameteri(unsigned int target, unsigned int texParam, unsigned int texValue);

	void Draw(unsigned int mode, int size, unsigned int type, const void* indices);
	void Draw(unsigned int mode, int start, int end);

	unsigned int SetShader(int shaderType, const char* vShaderCode);
	unsigned int LinkShader(unsigned int ID, unsigned int vertex, unsigned int fragment);

	void UseShader(int ID);
	void UnUseShader();

	void SetUniform(unsigned int ID, const std::string& name, bool value) const;
	void SetUniform(unsigned int ID, const std::string& name, int value) const;
	void SetUniform(unsigned int ID, const std::string& name, float value) const;
	void SetUniform(unsigned int ID, const std::string& name, const Vector3& v) const;
	void SetUniform(unsigned int ID, const std::string& name, const Matrix4x4& m) const;

	void DeleteShader(unsigned int shader);

	void DeleteFramebuffers(int number, unsigned int* framebuffersID);
	void DeleteRenderbuffers(int number, unsigned int* renderbuffersID);
	void DeleteTexture(int number, unsigned int* ID);

	void CreateQuad(unsigned int VBO, unsigned int EBO, unsigned int VAO);

	RendererDebug Debug;
};
