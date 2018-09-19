#include <iostream>
#include "GPIO.h"

using namespace std;

int main()
{
	GPIO four = new GPIO("4");

	cout<< four.get_GPIO();

	return 0;
}
