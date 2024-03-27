#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 vp;
uniform int entityID;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;
out int EntityID;

void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0f));
   Normal = aNormal;
   TexCoord = aTexCoord;
   EntityID = entityID;

   gl_Position = vp * model * vec4(FragPos, 1.0);
}
