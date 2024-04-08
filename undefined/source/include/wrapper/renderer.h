#pragma once

#include <glad/glad.h>
#include <toolbox/Matrix4x4.h>
#include <toolbox/Vector3.h>

#include "engine_debug/renderer_debug.h"
#include "wrapper/service_type.h"
#include "utils/flag.h"

class Texture;
class Model;

class UNDEFINED_ENGINE Renderer : public ServiceType
{
public:
	/// <summary>
	/// Init the renderer
	/// </summary>
	void Init();

	/// <summary>
	/// Set the framebuffer color
	/// </summary>
	/// <param name="redBaseColor">: Red color</param>
	/// <param name="greenBaseColor">: Green color</param>
	/// <param name="blueBaseColor">: Blue color</param>
	void SetClearColor(float redBaseColor = 0.3f, float greenBaseColor = 0.3f, float blueBaseColor = 0.3f);
	/// <summary>
	/// Clear the framebuffer
	/// </summary>
	void ClearBuffer();
	
	/// <summary>
	/// Generate a texture
	/// </summary>
	/// <param name="texNumber">: Number of texture generated</param>
	/// <param name="ID">: Texture ID</param>
	void GenTexture(unsigned int texNumber, unsigned int* ID);
	/// <summary>
	/// Generate a VBO or a EBO
	/// </summary>
	/// <param name="index">: Index of the buffer</param>
	/// <param name="buffer">: Pointer to the buffer</param>
	void GenerateBuffer(int index, unsigned int* buffer);
	/// <summary>
	/// Generate a VAO
	/// </summary>
	/// <param name="index">: Index of the buffer</param>
	/// <param name="buffer">: Pointer to the buffer</param>
	void GenerateVertexArray(int index, unsigned int* buffer);
	/// <summary>
	/// Generate the mip map
	/// </summary>
	/// <param name="target">: MipMap target</param>
	void GenerateMipMap(unsigned int target);

	/// <summary>
	/// Active the texture given
	/// </summary>
	/// <param name="ID">: texture ID</param>
	void ActiveTexture(unsigned int ID);
	
	/// <summary>
	/// Bind a Texture to the actual active Texture
	/// </summary>
	/// <param name="ID">: Texture ID</param>
	/// <param name="type">: Texture type (by default is : 0x0DE1 = 3553U = GL_TEXTURE_2D)</param>
	void BindTexture(unsigned int ID, unsigned int type = 0x0DE1);
	/// <summary>
	/// Bind a Texture to a framebuffer
	/// </summary>
	/// <param name="framebufferTarget">: Framebuffer where you want to put the texture</param>
	/// <param name="attachement">: Color attachement used</param>
	/// <param name="ID">: Texture ID</param>
	/// <param name="type">: Texture type (by default : 0x0DE1 = 3553U = GL_TEXTURE_2D)</param>
	void BindTexture(int framebufferTarget, int attachement, unsigned int ID, int type = 0x0DE1);
	/// <summary>
	/// Bind the framebuffer given as the one used
	/// </summary>
	/// <param name="target">: Renderer Target</param>
	/// <param name="framebufferID">: Framebuffer ID</param>
	void BindFramebuffer(unsigned int target, unsigned int framebufferID);
	/// <summary>
	/// Bind the renderbuffer given as the one used
	/// </summary>
	/// <param name="renderbufferID">: Renderbuffer ID</param>
	void BindRenderbuffer(unsigned int renderbufferID);
	/// <summary>
	/// Bind the VAO, VBO and EBO given
	/// </summary>
	/// <param name="VAO">: VAO</param>
	/// <param name="VBO">: VBO</param>
	/// <param name="EBO">: EBO</param>
	void BindBuffers(unsigned int VAO, unsigned int VBO, unsigned int EBO);
	/// <summary>
	/// Bind the renderbuffer given to the framebuffer given
	/// </summary>
	/// <param name="framebufferTarget">: Framebuffer target</param>
	/// <param name="attachements">: attachements (e.g : COLOR, DEPTH, STENCIL or DEPTH and STENCIL)</param>
	/// <param name="renderbufferID">: Renderbuffer ID</param>
	void BindRenderbufferToFramebuffer(int framebufferTarget, int attachements, unsigned int renderbufferID);

	/// <summary>
	/// Attribute Pointers of data in the VAO
	/// </summary>
	/// <param name="index">: Index in the VAO</param>
	/// <param name="size">: number of components</param>
	/// <param name="type">: Type of data (e.g : GL_UNSIGNED_INT, GL_SHORT)</param>
	/// <param name="stride">: Offest between the next pointer in the VAO</param>
	/// <param name="pointer">: Offset of the first element that will be attribute</param>
	/// <param name="isNormalized">: Should the data be normalized (by default : false)</param>
	void AttributePointers(unsigned int index, int size, unsigned int type, int stride, const void* pointer, bool isNormalized = false);
	/// <summary>
	/// Set the data into a buffer (e.g : VBO or EBO)
	/// </summary>
	/// <param name="target">: Buffer target (e.g : VBO or EBO)</param>
	/// <param name="size">: Size of the data</param>
	/// <param name="data">: Pointer to the first element of the data</param>
	/// <param name="usage">: Type of data (e.g : GL_UNSIGNED_INT, GL_SHORT)</param>
	void SetBufferData(unsigned int target, int size, const void* data, unsigned int usage);
	/// <summary>
	/// Allocate the storage for the renderbuffer data
	/// </summary>
	/// <param name="format">: Format used for the data (e.g : GL_DEPTH24_STENCIL8, GL_DEPTH32F_STENCIL8, ...)</param>
	/// <param name="width">: Width of the renderbuffer</param>
	/// <param name="height">: Height of the renderbuffer</param>
	void SetRenderBufferStorageData(int format, float width, float height);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="target">: Texture type (e.g : GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, ...)</param>
	/// <param name="texParam">: Texture parameter (e.g : GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, ...)</param>
	/// <param name="texValue">: Value of texParam (e.g : GL_LINEAR, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, ...)</param>
	void SetTextureParameteri(unsigned int target, unsigned int texParam, unsigned int texValue);

	/// <summary>
	/// Draw the elements by using the indices 
	/// </summary>
	/// <param name="mode">: Drawing mode (e.g : GL_TRIANGLES, GL_LINES, ...)</param>
	/// <param name="size">: Number of indices</param>
	/// <param name="type">: Type of data that need to be draw (e.g : GL_UNSIGNED_INT, GL_SHORT)</param>
	/// <param name="indices">: Pointer to the start of the data in the EBO (0 for the begining)</param>
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

	void SetQuad(unsigned int VBO, unsigned int EBO, unsigned int VAO);
	inline std::shared_ptr<Model> CreateCube();

	// Pass the GL_TEST here
	template<class... Args>
	void EnableTest(Args... test);

	RendererDebug Debug;
};

template<class ...Args>
inline void Renderer::EnableTest(Args ...test)
{
	for (const int p : { test... })
	{
		glEnable(p);
	}
}
