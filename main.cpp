#include <iostream>
#include "GPIO.h"

using namespace std;

int main()
{
	GPIO four("11");

	four.export_GPIO();
	cout<< four.get_GPIO();

	return 0;
}
