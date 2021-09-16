<<<<<<< HEAD
=======

>>>>>>> 3ad7d5ecbea8ba3bbda71d840ebb5785ac9e210f
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Engine/Rendering/3D/GameObject.h"
<<<<<<< HEAD

=======
enum class 
>>>>>>> 3ad7d5ecbea8ba3bbda71d840ebb5785ac9e210f
class Character : GameObject
{
public:
	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
	void Run(bool isBegin);

<<<<<<< HEAD
	void Move(glm::vec2 input);
=======
	void Move(glm:vec2 input);
>>>>>>> 3ad7d5ecbea8ba3bbda71d840ebb5785ac9e210f

private:
	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();



	float health;
	float meter;
};

#endif