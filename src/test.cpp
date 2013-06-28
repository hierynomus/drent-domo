#include <iostream>

#include "GpioPin.hpp"

using namespace std;

int main() {
	cout << "Creating gpio pin gpio1[28]" << endl;
	GpioPin pin (1, 28);
	string in;
	cin >> in;
	return 0;
}