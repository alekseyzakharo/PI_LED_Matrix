/*
 * matrix.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: osboxes
 */
#include "matrix.h"
#include "GPIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

static bool STOP;
static GPIO *R1,*B1,*R2,*B2, *A,*C,*CLK,*OE;
static GPIO *G1,*G2,*B,*D,*LAT;
static GPIO *GND;


void *run(void *id) {
   while(!STOP)
   {

   }
   pthread_exit(NULL);
}

matrix::matrix(void)
{
	srand(time(NULL));
	STOP = false;
	//randomize the array
	initArray();
}

bool matrix::start(void)
{
	pthread_t thread[1];
	if(pthread_create(&thread[1], NULL, run, (void *)1))
		return false;
	return true;
}

void matrix::stop(void)
{
	STOP = true;
}

void matrix::initArray(void)
{
	for(int i =0;i < ROWS; i++)
	{
		for(int j = 0;j < COLUMNS;j++)
		{
			arr[i][j] = rand()%8;
		}
	}
}


