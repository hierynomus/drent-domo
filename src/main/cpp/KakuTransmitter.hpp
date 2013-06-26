#ifndef KAKU_TRANSMITTER_H
#define KAKU_TRANSMITTER_H

#include "GpioPin.hpp"

class KakuTransmitter {
public:
	KakuTransmitter(unsigned long address, Pin *pin);
};
#endif
