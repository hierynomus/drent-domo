#ifndef PIN_H
#define PIN_H

#define HIGH 1
#define LOW 0

#define GPIO_INPUT "in"
#define GPIO_OUTPUT_LOW "low"
#define GPIO_OUTPUT_HIGH "high"

#define	GPIO_EXPORT_FILE "/sys/class/gpio/export"
#define	GPIO_UNEXPORT_FILE "/sys/class/gpio/unexport"
#define GPIO_FILE_PREFIX "/sys/class/gpio/gpio"
#define	GPIO_VALUE_POSTFIX "/value"
#define	GPIO_DIRECTION_POSTFIX "/direction"


#include <iostream>
#include <fstream>

using namespace std;

enum GPIO_ERRORS
{
	GPIO_GENERR 	= -1,
	GPIO_FILEERR 	= -2,
	GPIO_RDYERR		= -3
};

class GpioPin {
	unsigned short m_gpio;
	string m_sGpio;
	int m_pinFd;
	int m_directionFd;

public:
	GpioPin(unsigned short gpio);
	GpioPin(unsigned short bank, unsigned short pinNr);
	~GpioPin();
	void digitalWrite(unsigned short value);
	int digitalRead();

private:
	int activate();
	int exportPin();
	void setMode(string mode);
	int openPin();
	int openDirection();
	void closePin();
	int unexportPin();
	int writeFile(string filePath, string value);
};
#endif