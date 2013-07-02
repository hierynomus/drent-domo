#ifndef KAKU_TRANSMITTER_H
#define KAKU_TRANSMITTER_H

#include "GpioPin.hpp"
#include <time.h>

class KakuTransmitter {
	GpioPin *pin;
	unsigned long address;
	unsigned int repeats;
	struct timespec waiter;

public:
	KakuTransmitter(unsigned long address, GpioPin *pin, unsigned int repeats);
	// ~KakuTransmitter();

	void switchGroup(bool turnOn);
	void switchUnit(unsigned short unit, bool turnOn);
	void dimUnit(unsigned short unit, unsigned short dimLevel);

private:
	void transmitStartPulse();
	void transmitTransmitterAddress();
	void transmitGroupSwitchUnit(bool isGroup, bool turnOn, unsigned short unit);
	void transmitUnitDimLevel(unsigned short unit, unsigned short dimLevel);
	void transmitUnitAddress(unsigned short unit);
	void transmitStopPulse();

	void writeBit(bool bit);
	void delayMicroseconds(unsigned int microseconds);
};

#endif
