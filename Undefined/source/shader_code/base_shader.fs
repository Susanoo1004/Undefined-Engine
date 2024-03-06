#version 450 core

out vec4 FragColor;

struct DirLight {
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

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;
uniform sampler2D texture9;

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
    vec3 ambient = light.ambient * vec3(texture(texture1, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(texture1, TexCoord));
    return  (ambient + diffuse + specular);
}

void main()
{
    vec3 result;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // dirlight
    for (int i = 0; i < NBR_OF_DIR_LIGHT; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    
    FragColor = vec4(result, 1.0);
}