#include "SkyBox.h"
#include <SDL_image.h>

bool SkyBox::loadSkyBoxTextures(const char* textureArray[]) {

	glGenTextures(1, &skyBoxTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextureID);

	for (int i = 0; i < sizeof(textureArray)/sizeof(textureArray[0]); i++)
	{
		SDL_Surface* textureSurface = IMG_Load(textureArray[i]);
		if (textureSurface == nullptr) {
			return false;
		}

		int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}

void SkyBox::Render() const {
	

}

bool SkyBox::OnCreate() {

	/*if (ObjLoader::loadOBJ("meshes/Cube.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("SkyBoxVert.glsl", "SkyBoxFrag.glsl");
	
	if (meshPtr == nullptr || shaderPtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}*/

	//bool status = loadSkyBoxTextures(["textures/posx.jpg", "textures/negx.jpg", "textures/posy.jpg", "textures/negy.jpg", "textures/posz.jpg", "textures/negz.jpg"]);

	//if (status == false);
	return false;
}

void SkyBox::OnDestroy() {}
void SkyBox::Update(const float deltaTime) {}
void SkyBox::HandleEvents(const SDL_Event& event) {}