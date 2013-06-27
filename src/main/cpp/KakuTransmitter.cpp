#include "KakuTransmitter.hpp"
#include "GpioPin.hpp"

#include <time.h>

using namespace std;

#define T 244

KakuTransmitter::KakuTransmitter(unsigned long address, GpioPin *pin, unsigned int repeats) {
	this->address = address;
	this->pin = pin;
	this->repeats = (1 << repeats) - 1;
	this->waiter.tv_sec = 0;
}

void KakuTransmitter::switchGroup(bool turnOn) {
	for (int r = repeats; r >= 0; r--) {
		transmitStartPulse();
		transmitTransmitterAddress();
		transmitGroupSwitchUnit(true, turnOn, 0);
		transmitStopPulse();
	}
}

void KakuTransmitter::switchUnit(unsigned short unit, bool turnOn) {
	for (int r = repeats; r >= 0; r--) {
		transmitStartPulse();
		transmitTransmitterAddress();
		transmitGroupSwitchUnit(false, turnOn, unit);
		transmitStopPulse();
	}
}

void KakuTransmitter::dimUnit(unsigned short unit, unsigned short dimLevel) {
	for (int r = repeats; r >= 0; r--) {
		transmitStartPulse();
		transmitTransmitterAddress();
		transmitUnitDimLevel(unit, dimLevel);
		transmitStopPulse();
	}
}

void KakuTransmitter::transmitGroupSwitchUnit(bool group, bool turnOn, unsigned short unit) {
	writeBit(group);
	writeBit(turnOn);
	transmitUnitAddress(unit);
}

void KakuTransmitter::transmitUnitDimLevel(unsigned short unit, unsigned short dimLevel) {
		// Switch type 'dim'
		pin->digitalWrite(HIGH);
		delayMicroseconds(T);
		pin->digitalWrite(LOW);
		delayMicroseconds(T);
		pin->digitalWrite(HIGH);
		delayMicroseconds(T);
		pin->digitalWrite(LOW);
		delayMicroseconds(T);

		transmitUnitAddress(unit);

		for (short j=3; j>=0; j--) {
		   writeBit(dimLevel & 1<<j);
		}

}

void KakuTransmitter::transmitTransmitterAddress() {
	for (short b = 25; b >= 0; b--) {
		writeBit((address >> b) & 1);
	}
}

void KakuTransmitter::transmitUnitAddress(unsigned short unit) {
	for (short b = 3; b >= 0; b--) {
		writeBit((unit >> b) & 1);
	}
}

/**
 *           _
 * 'Start': | |__________ (T,10T)
 */
void KakuTransmitter::transmitStartPulse() {
	pin->digitalWrite(HIGH);
	delayMicroseconds(T);
	pin->digitalWrite(LOW);
	delayMicroseconds(10 * T);
}

/**
 *          _
 * 'Stop': | |________________________________________ (T,40T)
 */
void KakuTransmitter::transmitStopPulse() {
	pin->digitalWrite(HIGH);
	delayMicroseconds(T);
	pin->digitalWrite(LOW);
	delayMicroseconds(40 * T);
}

/**
 *         _   _
 * '0':   | |_| |_____ (T,T,T,5T)
 *         _       _
 * '1':   | |_____| |_ (T,5T,T,T)
 */
void KakuTransmitter::writeBit(bool bit) {
	if (bit) {
		// Send '1' bit
		pin->digitalWrite(HIGH);
		delayMicroseconds(T);
		pin->digitalWrite(LOW);
		delayMicroseconds(5 * T);
		pin->digitalWrite(HIGH);
		delayMicroseconds(T);
		pin->digitalWrite(LOW);
		delayMicroseconds(T);
	} else {
		// Send '0'bit
		pin->digitalWrite(HIGH);
		delayMicroseconds(T);
		pin->digitalWrite(LOW);
		delayMicroseconds(T);
		pin->digitalWrite(HIGH);
		delayMicroseconds(T);
		pin->digitalWrite(LOW);
		delayMicroseconds(5 * T);
	}
}

void KakuTransmitter::delayMicroseconds(unsigned int microseconds) {
	waiter.tv_nsec = microseconds * 1000L;
	nanosleep(&waiter, (struct timespec *) NULL);
}
