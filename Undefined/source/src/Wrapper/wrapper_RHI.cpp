#include "Wrapper/wrapper_RHI.h"

void WrapperRHI::WrapperInit(float redBaseColor, float greenBaseColor, float blueBaseColor)
{
	gladLoadGL();
	glClearColor(redBaseColor, greenBaseColor, blueBaseColor, 1.0f);
	glEnable(GL_DEPTH_TEST);

}

void WrapperRHI::SetClearColor(GLbitfield mask)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
