#include "wrapper/renderer.h"

void Renderer::WrapperInit(float redBaseColor, float greenBaseColor, float blueBaseColor)
{
	gladLoadGL();
	glClearColor(redBaseColor, greenBaseColor, blueBaseColor, 1.0f);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::SetClearColor(GLbitfield mask)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::BindTexture(unsigned int ID)
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
