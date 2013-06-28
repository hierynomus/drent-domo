#include <iostream>

#include "GpioPin.hpp"
#include "KakuTransmitter.hpp"
#include <time.h>

using namespace std;

int main(int argc, char **argv) {
	cout << "Creating gpio pin gpio1[28]" << endl;
	GpioPin pin (1, 28);

	KakuTransmitter tx (42, &pin, 3);
	pin.setOutputMode("low");
	cout << "Turning lamp on..." << endl;

	timespec start, end;

	clock_gettime(CLOCK_REALTIME, &start);
	tx.switchUnit(1, true);
	clock_gettime(CLOCK_REALTIME, &end);

	cout << "Sending bittrain cost: " << end.tv_nsec - start.tv_nsec << " nanoseconds" << endl;
	string in;
	cout << "Press key to turn lamp off:";
	cin >> in;
	tx.switchUnit(1, false);

	return 0;
}