#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include<glm/glm.hpp>

class LightSource
{
public:
	LightSource();
	LightSource(glm::vec3 position_, float ambient_, float diffuse_, float specular_, glm::vec3 colour_);
	~LightSource();

	inline glm::vec3 GetPosition() { return position; };
	inline float GetAmbient() { return ambient; };
	inline float GetDiffuse() { return diffuse; };
	inline float GetSpecular() { return specular; };
	inline glm::vec3 GetColour() { return colour; };

	inline void SetPosition(glm::vec3 position_) { position = position_; };
	inline void SetAmbient(float ambient_) { ambient = ambient_; };
	inline void SetDiffuse(float diffuse_) { diffuse = diffuse_; };
	inline void SetSpecular(float specular_) { specular; };
	inline void SetColour(glm::vec3 colour_) { colour = colour_; };

	
private:
	glm::vec3 position;
	float ambient, diffuse, specular;
	glm::vec3 colour;

};

#endif // !LIGHTSOURCE_H
