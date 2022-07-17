#pragma once

#include <cstdint>

namespace mp {

	struct Stats {
		Stats() {
			memset(this, 0, sizeof(Stats));
		}
		uint8_t _str;
		uint8_t _int;
		uint8_t _wis;
		uint8_t _chr;
	};

}
