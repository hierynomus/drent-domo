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
	ofstream pin;

public:
	GpioPin(string path, int mode);
	~GpioPin();
	void digitalWrite(int value);
	int digitalRead();
};
#endif