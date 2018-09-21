/*
 * matrix.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: osboxes
 */
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "GPIOClass.h"

static bool STOP;
static GPIOClass *R1,*B1,*R2,*B2, *A,*C,*CLK,*OE;
static GPIOClass *G1,*G2,*B,*D,*LAT;

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

void matrix::initGPIO(void)
{
	//ASSIGN
	R1 = new GPIOClass("1");
	B1 = new GPIOClass("1");
	R2 = new GPIOClass("1");
	B2 = new GPIOClass("1");
	A = new GPIOClass("1");
	C = new GPIOClass("1");
	CLK = new GPIOClass("1");
	OE = new GPIOClass("1");

	G1 = new GPIOClass("1");
	G2 = new GPIOClass("1");
	B = new GPIOClass("1");
	D = new GPIOClass("1");
	LAT = new GPIOClass("1");

	//******************//

	R1->export_gpio();
	B1->export_gpio();
	R2->export_gpio();
	B2->export_gpio();
	A->export_gpio();
	C->export_gpio();
	CLK->export_gpio();
	OE->export_gpio();

	G1->export_gpio();
	G2->export_gpio();
	B->export_gpio();
	D->export_gpio();
	LAT->export_gpio();

	R1->setdir_gpio("out");
	B1->setdir_gpio("out");
	R2->setdir_gpio("out");
	B2->setdir_gpio("out");
	A->setdir_gpio("out");
	C->setdir_gpio("out");
	CLK->setdir_gpio("out");
	OE->setdir_gpio("out");

	G1->setdir_gpio("out");
	G2->setdir_gpio("out");
	B->setdir_gpio("out");
	D->setdir_gpio("out");
	LAT->setdir_gpio("out");
}

