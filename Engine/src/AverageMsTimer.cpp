#pragma once

#include "Timers.h"
#include "SDL.h"

using namespace mp;

AveragingMsTimer::AveragingMsTimer(int averageOverX)
	:
	_lastCount        { 0 },
	_frequency        { 0 },
	_averageOverX     { averageOverX },
	_currentTick      { 0 },
	_currentMsAverage { 0 }
{
	_frequency = SDL_GetPerformanceFrequency();
	_lastCount = SDL_GetPerformanceCounter();
}

double AveragingMsTimer::Tick() {
	if (_currentTick++ == _averageOverX) {
		auto currentCount = SDL_GetPerformanceCounter();

		_currentMsAverage = 
			(double(currentCount - _lastCount) / double(_frequency))*1000/_averageOverX;

		_lastCount = currentCount;
		_currentTick = 0;
	}
	return _currentMsAverage;
}
