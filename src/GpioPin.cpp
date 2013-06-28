#include <iostream>
#include <stdio.h>

#include "GpioPin.hpp"

using namespace std;



GpioPin::GpioPin(unsigned short bank, unsigned short pinNr) {
	this->bank = bank;
	this->pinNr = pinNr;
	this->gpio = 32 * bank + pinNr;
	sprintf(gpioValue, "/sys/class/gpio/gpio%d/value", gpio);
	sprintf(gpioDirection, "/sys/class/gpio/gpio%d/direction", gpio);

	exportPin();
}

GpioPin::~GpioPin() {
	unexportPin();
}

void GpioPin::setOutputMode(string highOrLow) {
	cout << "Setting pin gpio" << gpio << " to output " << highOrLow << endl;
	writeFile(gpioDirection, highOrLow.c_str());
}


void GpioPin::setInputMode() {

}

void GpioPin::digitalWrite(unsigned short value) {
	writeFile(gpioValue, value);
}

int GpioPin::digitalRead() {
	return 1;
}

void GpioPin::exportPin() {
	cout << "Opening pin gpio" << gpio << "..." << endl;
	writeFile("/sys/class/gpio/export", gpio);
}

void GpioPin::unexportPin() {
	cout << "Closing pin gpio" << gpio << "..." << endl;
	writeFile("/sys/class/gpio/unexport", gpio);
}

void GpioPin::writeFile(char const *filePath, const char * value) {
	FILE *f = NULL;
	f = fopen(filePath, "ab");
	fwrite(&value, sizeof(char), sizeof(value), f);
	fclose(f);
}

void GpioPin::writeFile(char const *filePath, unsigned short value) {
	FILE *f = NULL;
	f = fopen(filePath, "ab");
	fwrite(&value, sizeof(char), 1, f);
	fclose(f);
}