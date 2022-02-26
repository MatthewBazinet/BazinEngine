#ifndef HURTBOXVISUAL_H
#define HURTBOXVISUAL_H
#include "Engine/Rendering/3D/Model.h"
#include "HurtBox.h"

class HurtBoxVisual: public Model
{	
public:
	HurtBoxVisual(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~HurtBoxVisual();
	void Render(Camera* camera_) override;
	void EnableVisual() { isEnabled = true; };
	void DisableVisual(){ isEnabled = false; };
	bool isEnabled;
};
#endif
