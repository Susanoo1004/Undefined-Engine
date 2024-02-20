#include "engine_debug/renderer_debug.h"

#include <iostream>

void RendererDebug::DebugInit()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
            if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            {
                return;
            }

        std::cout << message << std::endl;
    },
    nullptr
    );

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
