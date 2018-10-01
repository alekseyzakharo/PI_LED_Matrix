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
static float DELAY_IN_S = 0;
static float DELAY_IN_NS = 5000;

static int MATRIX_SIZE = 32;


static GPIOClass *R1,*B1,*R2,*B2, *A,*C,*CLK,*OE;
static GPIOClass *G1,*G2,*B,*D,*LAT;

const string R1_GPIO = "18";
const string B1_GPIO = "23";
const string R2_GPIO = "24";
const string B2_GPIO = "25";
const string A_GPIO = "12";
const string C_GPIO = "16";
const string CLK_GPIO = "20";
const string OE_GPIO = "21";

const string G1_GPIO = "5";
const string G2_GPIO = "6";
const string B_GPIO = "13";
const string D_GPIO = "19";
const string LAT_GPIO = "26";


static void matrixRefresh();
static void integerToBitArray(int* arr, int input, int size);
static void matrixClock();
static void matrixLatch();
static void matrixSetColorTop(int color);
static void matrixSetColorBottom(int color);
static void matrixSetPixel(int x, int y, int color);
static void matrixSetRow(int rowNum);


void *run(void *id) {
   while(!STOP)
   {
	   matrixRefresh();
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
			screen[i][j] = rand()%8;
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




static void matrixRefresh()
{
    for (int rowNum = 0; rowNum < MATRIX_SIZE/2; rowNum++)
    {
        // Turn Power On
        //lseek(fileDesc_oe, 0, SEEK_SET);
        //write(fileDesc_oe, "1", 1);
    	OE->setval_gpio("1");


        // Set Current Row
        matrixSetRow(rowNum);

        for (int colNum = 0; colNum < MATRIX_SIZE; colNum++)
        {
            //pthread_mutex_lock(&ledThreadMutex);
            matrixSetColorTop(screen[colNum][rowNum]);
            matrixSetColorBottom(screen[colNum][rowNum + MATRIX_SIZE/2]);
            //pthread_mutex_unlock(&ledThreadMutex);

            matrixClock();
        }

        matrixLatch();

        // Turn Power Off
        //lseek(fileDesc_oe, 0, SEEK_SET);
        //write(fileDesc_oe, "0", 1);

        OE->setval_gpio("0");

        // Refresh Delay
        nanosleep((const struct timespec[]){{DELAY_IN_S, DELAY_IN_NS}}, NULL);
    }
}

static void integerToBitArray(int* arr, int input, int size)
{
    for (int i = 0; i < size; i++)
    {
    	arr[i] = input & ((int) pow(2, i));
    	arr[i] = arr[i] >> i;
    }
}

// Bit-Bang GPIO Clock Pin
static void matrixClock()
{
//    lseek(fileDesc_clk, 0, SEEK_SET);
//    write(fileDesc_clk, "1", 1);
//    lseek(fileDesc_clk, 0, SEEK_SET);
//    write(fileDesc_clk, "0", 1);
	CLK->setval_gpio("1");
	CLK->setval_gpio("0");
}

// Bit-Bang GPIO Latch Pin
static void matrixLatch()
{
//    lseek(fileDesc_latch, 0, SEEK_SET);
//    write(fileDesc_latch, "1", 1);
//
//    lseek(fileDesc_latch, 0, SEEK_SET);
//    write(fileDesc_latch, "0", 1);
	LAT->setval_gpio("1");
	LAT->setval_gpio("0");
}

// Set Top Pixel Color
static void matrixSetColorTop(int color)
{
    int arr[3] = {0, 0, 0};
    integerToBitArray(arr, color, 3);

    // Set RGB GPIO Pin Values
    char red1_val[2];
    sprintf(red1_val, "%d", arr[0]);
//    lseek(fileDesc_red1, 0, SEEK_SET);
//    write(fileDesc_red1, red1_val, 1);
    string r1val = red1_val[0];
    R1->setval_gpio(r1val);

    char green1_val[2];
    sprintf(green1_val, "%d", arr[1]);
//    lseek(fileDesc_green1, 0, SEEK_SET);
//    write(fileDesc_green1, green1_val, 1);
    string g1val = green1_val[0];
    G1->setval_gpio(g1val);

    char blue1_val[2];
    sprintf(blue1_val, "%d", arr[2]);
//    lseek(fileDesc_blue1, 0, SEEK_SET);
//    write(fileDesc_blue1, blue1_val, 1);
    string b1val = blue1_val[0];
	B1->setval_gpio(b1val);
}

// Set Bottom Pixel Color
static void matrixSetColorBottom(int color)
{
    int arr[3] = {0, 0, 0};
    integerToBitArray(arr, color, 3);

    // Set RGB GPIO Pin Values
    char red2_val[2];
    sprintf(red2_val, "%d", arr[0]);
//    lseek(fileDesc_red2, 0, SEEK_SET);
//    write(fileDesc_red2, red2_val, 1);
    string r2val = red2_val[0];
	R2->setval_gpio(r2val);

    char green2_val[2];
    sprintf(green2_val, "%d", arr[1]);
//    lseek(fileDesc_green2, 0, SEEK_SET);
//    write(fileDesc_green2, green2_val, 1);
    string g2val = green2_val[0];
	G2->setval_gpio(g2val);

    char blue2_val[2];
    sprintf(blue2_val, "%d", arr[2]);
//    lseek(fileDesc_blue2, 0, SEEK_SET);
//    write(fileDesc_blue2, blue2_val, 1);
    string b2val = blue2_val[0];
	B2->setval_gpio(b2val);
}


// Set Current LED Screen Matrix Row
static void matrixSetRow(int rowNum)
{
    int arr[4] = {0, 0, 0, 0};
    integerToBitArray(arr, rowNum, 4);

    // Set ABCD GPIO Pin Values
    char a_val[2];
    sprintf(a_val, "%d", arr[0]);
//    lseek(fileDesc_a, 0, SEEK_SET);
//    write(fileDesc_a, a_val, 1);

    char b_val[2];
    sprintf(b_val, "%d", arr[1]);
//    lseek(fileDesc_b, 0, SEEK_SET);
//    write(fileDesc_b, b_val, 1);

    char c_val[2];
    sprintf(c_val, "%d", arr[2]);
//    lseek(fileDesc_c, 0, SEEK_SET);
//    write(fileDesc_c, c_val, 1);

	char d_val[2];
    sprintf(d_val, "%d", arr[3]);
//    lseek(fileDesc_d, 0, SEEK_SET);
//    write(fileDesc_d, d_val, 1);
}








