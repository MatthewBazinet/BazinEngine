#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

struct Light
{
vec3 position;
float ambient;
float diffuse;
float specular;
vec3 colour;
};

uniform sampler2D inputTexture;
uniform vec3 cameraPosition;
uniform Light lightSource;

out vec4 fColour;


void main()
{
//Ambient
vec3 ambient = lightSource.ambient * texture(inputTexture, TexCoords).rgb * lightSource.colour;
//Diffuse
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightSource.position - FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff * lightSource.diffuse) * texture(inputTexture, TexCoords).rgb * lightSource.colour;
//Specular
vec3 viewDir = normalize(cameraPosition - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = (spec * lightSource.specular) * lightSource.colour;
vec3 result = ambient + diffuse + specular;
fColour = vec4(result, 1.0f);
}