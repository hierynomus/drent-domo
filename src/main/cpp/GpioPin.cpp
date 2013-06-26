#include <iostream>
#include <fstream>

#include "GpioPin.hpp"

using namespace std;

GpioPin::GpioPin(string path, int mode) {
	cout << "Going to open " << path << endl;
	pin.open(path.c_str());
}

GpioPin::~GpioPin() {
	cout << "Going to close..." << endl;
	pin.close();
}

void GpioPin::digitalWrite(int value) {
	cout << "Writing [" << value << "] to pin." << endl;
	pin << value;
	pin.flush();
}

int GpioPin::digitalRead() {
	return 1;
}