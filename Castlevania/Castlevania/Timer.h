#pragma once

#include <Windows.h>

class Timer
{
	int start;
	int limitedTime;

public:
	Timer(int limitedTime) { this->limitedTime = limitedTime; start = 0; }
	
	void Start() { start = GetTickCount(); }
	void Stop() { start = 0; }
	bool IsTimeUp() { return GetTickCount() - start > limitedTime; }

	int GetStartTime() { return start; }
	int GetLimitedTime() { return limitedTime; }
};

