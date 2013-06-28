#include <iostream>

#include "GpioPin.hpp"

using namespace std;

int main() {
	string in;
	GpioPin p ("test.txt", GPIO_OUTPUT);
	p.digitalWrite(HIGH);
	cout << "Press a key: ";
	cin >> in;
	p.digitalWrite(HIGH);
	return 0;
}