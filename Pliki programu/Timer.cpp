#include "Timer.h"
#include <iostream>

using namespace std;

//poczatkowy pomiar czasu
void Timer::start() {
	startTime = high_resolution_clock::now();
}

//koncowy pomiar czasu
void Timer::stop() {
	endTime = high_resolution_clock::now();
}

//oblicznie uplynietego czasu
double Timer::timeCount() {
	return duration_cast<microseconds>(endTime - startTime).count();
}