#ifndef ONLINEGAMESCENE_H
#define ONLINEGAMESCENE_H

#include "..//Game/Scene/GameScene.h"
#include "NetworkingPackets.h"

class OnlineGameScene :
	public Scene
{
public:
	OnlineGameScene();
	~OnlineGameScene();
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void NotifyOfKeyDown(const SDL_Scancode key_);
	void NotifyOfKeyUp(const SDL_Scancode key_);
	void NetworkGameplayUpdate(NetworkingGameplayPacket packet);
};

#endif // !ONLINEGAMESCENE_H