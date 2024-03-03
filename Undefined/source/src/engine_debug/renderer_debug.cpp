#include "engine_debug/renderer_debug.h"

#include <iostream>

#include "logger/logger.h"

void RendererDebug::DebugInit()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback([](GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
    {
            if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            {
                return;
            }

            if (severity == GL_DEBUG_TYPE_ERROR)
            {
                Logger::Error("{}", message);
            }

            else
            {
                Logger::Warning("{}", message);
            }
    },
    nullptr
    );

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
