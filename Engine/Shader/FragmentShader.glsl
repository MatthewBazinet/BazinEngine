#version 450 core
#define MAX_NUM_OF_LIGHTS 10

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

struct Light
{
vec3 position[MAX_NUM_OF_LIGHTS];
float ambient[MAX_NUM_OF_LIGHTS];
float diffuse[MAX_NUM_OF_LIGHTS];
float specular[MAX_NUM_OF_LIGHTS];
vec3 colour[MAX_NUM_OF_LIGHTS];
};

struct Material 
{
	sampler2D diffuseMap;

	float shininess; //Ns
	float transparency; //d

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks
};

uniform vec3 cameraPosition;
uniform Light lightSource;
uniform Material material;

out vec4 fColour;


void main()
{
vec3 ambient[MAX_NUM_OF_LIGHTS];
vec3 diffuse[MAX_NUM_OF_LIGHTS];
vec3 specular[MAX_NUM_OF_LIGHTS];

for(int i = 0; i < MAX_NUM_OF_LIGHTS; i++)
{
//Ambient
ambient[i] = lightSource.ambient[i] * material.ambient * lightSource.colour[i];
//Diffuse
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightSource.position[i] - FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
diffuse[i] = (diff * material.diffuse) * lightSource.colour[i];
//Specular
vec3 viewDir = normalize(cameraPosition - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
specular[i] = (spec * material.specular) * lightSource.colour[i];
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

fColour = vec4((resultAmbient + resultDiffuse) * texture(material.diffuseMap, TexCoords).rgb + resultSpecular, material.transparency);
}