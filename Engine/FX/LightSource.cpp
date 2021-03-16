#include "LightSource.h"

LightSource::LightSource() : LightSource(glm::vec3(0,0,0),1,1,1,glm::vec3(1,1,1))
{
}

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, float specular_, glm::vec3 colour_)
{
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	specular = specular_;
	colour = colour_;
}

LightSource::~LightSource()
{
}
