#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>

#include "GpioPin.hpp"

using namespace std;

GpioPin::GpioPin(unsigned short bank, unsigned short pinNr) {
	m_gpio = 32 * bank + pinNr;
	m_sGpio = static_cast<ostringstream*>(&(ostringstream() << m_gpio))->str();

	exportPin();
	openDirection();
	openPin();
}

GpioPin::~GpioPin() {
	close(m_pinFd);
	close(m_directionFd);
	unexportPin();
}

void GpioPin::digitalWrite(unsigned short value) {
	if (value == HIGH) {
		write(m_pinFd, "1\n", 2);
	} else {
		write(m_pinFd, "0\n", 2);
	}
}

int GpioPin::digitalRead() {
	return 1;
}

int GpioPin::openDirection() {
	string dirfile_str = GPIO_FILE_PREFIX + m_sGpio + GPIO_DIRECTION_POSTFIX;
	m_directionFd = open(dirfile_str.c_str(), O_RDWR);
	if (m_directionFd < 0) {
		return GPIO_FILEERR;
	}
	return 0;
}

int GpioPin::exportPin() {
	cout << "Opening pin gpio" << m_gpio << "..." << endl;
	string export_str = GPIO_EXPORT_FILE;
	return writeFile(export_str, m_sGpio);
}

void GpioPin::setMode(string mode) {
	cout << "Setting pin gpio" << m_gpio << " to mode " << mode << endl;

	lseek(m_directionFd, 0L, SEEK_SET);
	write(m_directionFd, mode.c_str(), mode.size());
}

int GpioPin::openPin() {
	string pinPath = GPIO_FILE_PREFIX + m_sGpio + GPIO_VALUE_POSTFIX;
	m_pinFd = open(pinPath.c_str(), O_RDWR);
	if (!m_pinFd) {
		return GPIO_FILEERR;
	}
	return 0;
}

int GpioPin::unexportPin() {
	cout << "Closing pin gpio" << m_gpio << "..." << endl;
	return writeFile(GPIO_UNEXPORT_FILE, m_sGpio);
}

int GpioPin::writeFile(string filePath, string value) {
	ofstream f(filePath.c_str());
	if (!f) {
		return GPIO_FILEERR;
	}
	f << value;
	f.close();
	return 0;
}
