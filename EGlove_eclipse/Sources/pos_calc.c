/*
 * pos_calc.c
 *
 *  Created on: 9 pa? 2016
 *      Author: Mariusz
 */

#include "pos_calc.h"
#include <math.h>
#include <limits.h>


void fillHandPos(HandPos * vhand,int16_t vaccX,int16_t vaccZ,int16_t vgyroY,
		int16_t vgyroZ, int16_t * vtimerCount){
	(*vhand).accX = vaccX;
	(*vhand).accZ = vaccZ;
	(*vhand).accXCount++;
	(*vhand).accZCount++;
	(*vhand).accXCount %= ACC_CORRECTION_SIZE;
	(*vhand).accZCount %= ACC_CORRECTION_SIZE;
	(*vhand).corrAccDataX[(*vhand).accXCount] = vaccX;
	(*vhand).corrAccDataZ[(*vhand).accZCount] = vaccZ;// - INT16_MAX>>1;

	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
		if(abs((*vhand).corrAccDataX[i]-(*vhand).corrAccDataX[(*vhand).accXCount])>ACC_CORRECTION_FACTOR)
			break;
			if(i==ACC_CORRECTION_SIZE-1){
				(*vhand).sinGAccX = vaccX;
				(*vhand).angleAccX = asin(((float)(*vhand).sinGAccX)/INT16_MAX);
			}
	}

	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
		if(abs((*vhand).corrAccDataZ[i]-(*vhand).corrAccDataZ[(*vhand).accZCount])>ACC_CORRECTION_FACTOR)
			break;
			if(i==ACC_CORRECTION_SIZE-1){
				(*vhand).sinGAccZ = vaccZ;
				(*vhand).angleAccZ = asin(((float)(*vhand).sinGAccZ)/INT16_MAX);
			}
	}
	(*vhand).angleAccX = asin(((float)(*vhand).sinGAccX)/INT16_MAX);
	(*vhand).angleAccZ = asin((float)(*vhand).sinGAccZ/INT16_MAX);


	(*vhand).gyroY = vgyroY;
	(*vhand).gyroZ = vgyroZ;
	//(*vhand).angleGyroY -= (float)vgyroY/INT16_MAX;//*(*vtimerCount)/10;


	(*vhand).posX-=(float)(*vhand).accX*(*vtimerCount);
	(*vhand).posY-=(float)(*vhand).accZ*(*vtimerCount);
	*vtimerCount = 0;
}
char* dataToSend(HandPos vhand);

