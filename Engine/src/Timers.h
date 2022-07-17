#pragma once

namespace mp {

	class AveragingMsTimer {

		unsigned long long _lastCount;
		unsigned long long _frequency;
		int      _averageOverX;
		int      _currentTick;
		double   _currentMsAverage;

	public:
		AveragingMsTimer(int averageOverX);

		double Tick();
	};

}
