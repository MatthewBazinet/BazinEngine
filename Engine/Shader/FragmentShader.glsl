#version 450 core
#define MAX_NUM_OF_LIGHTS 10

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

struct Light
{
vec3 position[MAX_NUM_OF_LIGHTS];
float ambient[MAX_NUM_OF_LIGHTS];
float diffuse[MAX_NUM_OF_LIGHTS];
float specular[MAX_NUM_OF_LIGHTS];
vec3 colour[MAX_NUM_OF_LIGHTS];
};

uniform sampler2D inputTexture;
uniform vec3 cameraPosition;
uniform Light lightSource;

out vec4 fColour;


void main()
{
vec3 ambient[MAX_NUM_OF_LIGHTS];
vec3 diffuse[MAX_NUM_OF_LIGHTS];
vec3 specular[MAX_NUM_OF_LIGHTS];

for(int i = 0; i < MAX_NUM_OF_LIGHTS; i++)
{
//Ambient
ambient[i] = lightSource.ambient[i] * lightSource.colour[i];
//Diffuse
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightSource.position[i] - FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
diffuse[i] = (diff * lightSource.diffuse[i]) * lightSource.colour[i];
//Specular
vec3 viewDir = normalize(cameraPosition - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
specular[i] = (spec * lightSource.specular[i]) * lightSource.colour[i];
}

vec3 resultAmbient;
vec3 resultDiffuse;
vec3 resultSpecular;
for(int i = 0; i < MAX_NUM_OF_LIGHTS; i++)
{
resultAmbient+= ambient[i];
resultDiffuse+= diffuse[i];
resultSpecular+= specular[i];
}

fColour = vec4((resultAmbient + resultDiffuse) * texture(inputTexture, TexCoords).rgb + resultSpecular, 1.0f);
}