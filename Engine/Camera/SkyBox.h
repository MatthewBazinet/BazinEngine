#ifndef SKYBOX_H
#define SKYBOX_H
#include <glew.h>
#include "../Engine/Rendering/3D/GameObject.h"

union SDL_Event;

class SkyBox : public GameObject
{

private:
	GLuint skyBoxTextureID;
	bool loadSkyBoxTextures(const char* textureArray[]);

public:
	void Render() const;
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void HandleEvents(const SDL_Event& event);
};
#endif