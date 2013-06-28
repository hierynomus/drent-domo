#include <iostream>
#include <fstream>

#include "GpioPin.hpp"

using namespace std;



GpioPin::GpioPin(unsigned short bank, unsigned short pinNr) {
	this->bank = bank;
	this->pinNr = pinNr;
	this->gpio = 32 * bank + pinNr;
	sprintf(this->gpioValue, "/sys/class/gpio/gpio%d/value", gpio);
	sprintf(this->gpioDirection, "/sys/class/gpio/gpio%d/direction", gpio);

	exportPin();
}

GpioPin::~GpioPin() {
	unexportPin();
}

void GpioPin::setOutputMode(string highOrLow) {
	cout << "Setting pin gpio" << gpio << " to output " << highOrLow << endl;
	writeFile(gpioDirection, highOrLow);
}


void GpioPin::setInputMode() {

}

void GpioPin::digitalWrite(unsigned short value) {
	cout << "Writing [" << value << "] to pin." << endl;
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

void GpioPin::writeFile(char const *filePath, string value) {
	ofstream path;
	path.open(filePath);
	path << value;
	path.close();
}

void GpioPin::writeFile(char const *filePath, unsigned short value) {
	ofstream path;
	path.open(filePath);
	path << value;
	path.close();
}