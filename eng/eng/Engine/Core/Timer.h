#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	//Singleton
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTick();
private:
	unsigned int prevTicks, currentTicks;
};

#endif