#ifndef SDLINIT_H
#define SDLINIT_H
class SDLInit
{
public:
	static void initSDLSound();
	SDLInit();
	~SDLInit();
private:
	bool m_SoundInitilized = false;
};
#endif