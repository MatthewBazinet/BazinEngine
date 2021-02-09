#ifndef TIMER_H
#define TIMER_H
class Timer
{
	//Delete the copy and move operators
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;
};
#endif

