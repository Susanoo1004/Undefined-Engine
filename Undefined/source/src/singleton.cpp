#include "singleton.h"

WrapperGLFW* Singleton::wrapperGLFW;
WrapperRHI* Singleton::wrapperRHI;

void Singleton::Init()
{
	wrapperGLFW = new WrapperGLFW();
	wrapperRHI = new WrapperRHI();
}

void Singleton::Destroy()
{
	delete wrapperGLFW;
	delete wrapperRHI;
}
