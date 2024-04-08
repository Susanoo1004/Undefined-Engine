#version 450 core

layout (location = 0) out vec4 FragColor;

struct DirLight 
{
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

// LIGHT
#define NBR_OF_DIR_LIGHT 1

uniform vec3 viewPos;
uniform DirLight dirLights[NBR_OF_DIR_LIGHT];

// TEXTURE
uniform sampler2D texture0;

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture0, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture0, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(texture0, TexCoord));

    return  (ambient + diffuse + specular);
}

void main()
{
    vec3 result;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // dirlight
    for (int i = 0; i < NBR_OF_DIR_LIGHT; i++)
    {
        result += CalcDirLight(dirLights[i], norm, viewDir);
    }
    
    FragColor = vec4(result, 1.0);
}