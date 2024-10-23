#pragma once

#include <iostream>

struct PAIR {
	std::string second;
	int32_t delay;

	PAIR(std::string second, int32_t delay): second(second), delay(delay) {}

	PAIR() : second("NULL"), delay(NULL) {}

	void add(std::string inputSecond, int32_t inputDelay) {
		second = inputSecond;
		delay = inputDelay;
	}
};
