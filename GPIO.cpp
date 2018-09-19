/*
 * GPIO.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: osboxes
 */

#include "GPIO.h"
#include <fstream>

GPIO::GPIO()
{
	//set default value 0
	gpioNum = "0";
}

GPIO::GPIO(string num)
{
	gpioNum = num;
}

bool GPIO::export_GPIO(void)
{
	ofstream myfile ("/sys/class/gpio/export");
	if (myfile.is_open())
	{
		myfile << gpioNum;
		myfile.close();
		return true;
	}
	else
		return false;
}

string GPIO::get_GPIO(void)
{
	return gpioNum;
}
