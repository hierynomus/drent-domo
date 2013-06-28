#ifndef PIN_H
#define PIN_H

#define HIGH 1
#define LOW 0

#define GPIO_INPUT 1
#define GPIO_OUTPUT 0

#include <iostream>
#include <fstream>

using namespace std;

class GpioPin {
	unsigned short bank;
	unsigned short pinNr;
	unsigned short gpio;

public:
	GpioPin(unsigned short bank, unsigned short pinNr);
	~GpioPin();
	void setOutputMode(string highOrLow);
	void setInputMode();
	void digitalWrite(int value);
	int digitalRead();

private:
	void export();
	void unexport();
};
#endif