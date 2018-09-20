/*
 * GPIO.h
 *
 *  Created on: Sep 19, 2018
 *      Author: osboxes
 */
#include <string>

#ifndef GPIO_H_
#define GPIO_H_

using namespace std;

class GPIO
{
	public:
		GPIO();
		GPIO(string num);

		bool export_GPIO(void);
		bool unexport_GPIO(void);

		string get_GPIO(void);
	private:

		string gpioNum;
};

#endif /* GPIO_H_ */
