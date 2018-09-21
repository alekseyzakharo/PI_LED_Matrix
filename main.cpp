#include <iostream>

#include "GPIOClass.h"

using namespace std;



int main()
{
	GPIOClass four("11");

	four.setdir_gpio("out");


	return 0;
}
