#ifndef EVENTLISTENER
#define EVENTLISTENER

#include "MouseEventListener.h"
#include "KeyboardEventListener.h"

class EventListener {
public:
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener) = delete;
	EventListener& operator=(EventListener&&) = delete;
	EventListener() = delete;
	~EventListener();

	static void Update();


};


#endif // !EVENTLISTENER
