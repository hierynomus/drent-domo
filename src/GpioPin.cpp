#include <iostream>
#include <fstream>

#include "GpioPin.hpp"

using namespace std;



GpioPing::GpioPin(unsigned short bank, unsigned short pinNr) {
	this->bank = bank;
	this->pinNr = pinNr;
	this->gpio = 32 * bank + pinNr;

	export();
}

GpioPin::~GpioPin() {
	cout << "Going to close..." << endl;
	unexport();
}

void GpioPin::setOutputMode(string highOrLow) {
	cout << "Setting pin gpio" << bank << "[" << nr << "] to output " << highOrLow << endl;

}

void GpioPin::setInputMode() {

}

void GpioPin::digitalWrite(int value) {
	cout << "Writing [" << value << "] to pin." << endl;
	pin << value;
	pin.flush();
}

int GpioPin::digitalRead() {
	return 1;
}

void export() {
	ofstream exportPath;
	exportPath.open("/sys/class/gpio/export");
	exportPath << gpio;
	exportPath.close();
}

void unexport() {
	ofstream unexportPath;
	unexportPath.open("/sys/class/gpio/unexport");
	unexportPath << gpio;
	unexportPath.close();
}