/*
 * matrix.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: osboxes
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "global.h"
#include "matrix.h"
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
	R1 = new GPIOClass(R1_GPIO);
	B1 = new GPIOClass(B1_GPIO);
	R2 = new GPIOClass(R2_GPIO);
	B2 = new GPIOClass(B1_GPIO);
	A = new GPIOClass(A_GPIO);
	C = new GPIOClass(C_GPIO);
	CLK = new GPIOClass(CLK_GPIO);
	OE = new GPIOClass(OE_GPIO);

	G1 = new GPIOClass(G1_GPIO);
	G2 = new GPIOClass(G2_GPIO);
	B = new GPIOClass(B_GPIO);
	D = new GPIOClass(D_GPIO);
	LAT = new GPIOClass(LAT_GPIO);

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

