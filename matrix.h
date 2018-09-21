/*
 * matrix.h
 *
 *  Created on: Sep 19, 2018
 *      Author: osboxes
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#define ROWS 32
#define COLUMNS 32

class matrix
{
	public:
		matrix(void);

		//return true if thread started successfully, false other wise
		bool start(void);
		//stop thread
		void stop(void);

	private:
		char arr[32][32];


		void initArray(void);
		void initGPIO(void);

};




#endif /* MATRIX_H_ */
