/*
 * pos_calc.c
 *
 *  Created on: 9 pa? 2016
 *      Author: Mariusz
 */

#include "pos_calc.h"
#include <math.h>
#include <limits.h>


void fillHandPos(HandPos * vhand,int16_t vaccX,int16_t vaccY,int16_t vaccZ,
		        int16_t vgyroX,	int16_t vgyroY, int16_t vgyroZ){
	(*vhand).accX = vaccX;
	(*vhand).accY = vaccY;
	(*vhand).accZ = vaccZ;
	(*vhand).accXCount++;
	(*vhand).accYCount++;
	(*vhand).accZCount++;
	(*vhand).accXCount %= ACC_CORRECTION_SIZE;
	(*vhand).accYCount %= ACC_CORRECTION_SIZE;
	(*vhand).accZCount %= ACC_CORRECTION_SIZE;
	(*vhand).corrAccDataX[(*vhand).accXCount] = vaccY;
	(*vhand).corrAccDataY[(*vhand).accYCount] = vaccY;
	(*vhand).corrAccDataZ[(*vhand).accZCount] = vaccZ;// - INT16_MAX>>1;

	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
		if(abs((*vhand).corrAccDataY[i]-(*vhand).corrAccDataY[(*vhand).accYCount])>ACC_CORRECTION_FACTOR)
			break;
			if(i==ACC_CORRECTION_SIZE-1){
				(*vhand).sinGAccY = vaccY;
				 if((float)(*vhand).sinGAccY/(INT16_MAX)*2>1)
					 (*vhand).angleAccY = asin(1);
				 else if((float)(*vhand).sinGAccY/(INT16_MAX)*2<-1)
					 (*vhand).angleAccY = asin(-1);
				 else{
					 (*vhand).angleAccY = (asin((float)(*vhand).sinGAccY/(INT16_MAX)*2));
					// (*vhand).angleGyroX = (*vhand).angleAccY;
				 }
			}
	}

	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
		if(abs((*vhand).corrAccDataZ[i]-(*vhand).corrAccDataZ[(*vhand).accZCount])>ACC_CORRECTION_FACTOR + 100)
			break;
		if(i==ACC_CORRECTION_SIZE-1){
				(*vhand).sinGAccZ = vaccZ;
				 if((float)(*vhand).sinGAccZ/(INT16_MAX)*2>1)
					 (*vhand).angleAccZ = asin(1);
				 else if((float)(*vhand).sinGAccZ/(INT16_MAX)*2<-1)
					 (*vhand).angleAccZ = asin(-1);
				 else{
					 (*vhand).angleAccZ = (asin((float)(*vhand).sinGAccZ/(INT16_MAX)*2));
				 }
			}
	}

	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
		if(abs((*vhand).corrAccDataX[i]-(*vhand).corrAccDataX[(*vhand).accXCount])>ACC_CORRECTION_FACTOR)
			break;
			if(i==ACC_CORRECTION_SIZE-1){
				(*vhand).sinGAccX = vaccY;
				 if((float)(*vhand).sinGAccX/(INT16_MAX)*2>1)
					 (*vhand).angleAccX = asin(1);
				 else if((float)(*vhand).sinGAccX/(INT16_MAX)*2<-1)
					 (*vhand).angleAccX = asin(-1);
				 else{
					 (*vhand).angleAccX = (asin((float)(*vhand).sinGAccX/(INT16_MAX)*2));
				//	 (*vhand).angleGyroY = (*vhand).angleAccX;
				 }
			}
	}

	(*vhand).angleGyroX += ((float)vgyroX+(*vhand).angleGyroX + 110)/INT16_MAX*250*3.1415/180/TIMER_PRESCALER*1.19;
	(*vhand).angleGyroY += ((float)vgyroY+(*vhand).angleGyroY-35)/INT16_MAX*250*3.1415/180/TIMER_PRESCALER*1.19;
	(*vhand).angleGyroZ += ((float)vgyroZ+(*vhand).angleGyroZ + 100)/INT16_MAX*250*3.1415/180/TIMER_PRESCALER*1.19;

	rotateCoordinate(vaccY ,vaccZ, &(*vhand).accYRot, &(*vhand).accZRot,(*vhand).angleGyroX);
	rotateCoordinate((*vhand).accZRot ,vaccX, &(*vhand).accZRot, &(*vhand).accXRot,(*vhand).angleGyroY);

	//(*vhand).posX-=(float)(*vhand).accX
	//(*vhand).posY-=(float)(*vhand).accZ*(*vtimerCount);
}
char* dataToSend(HandPos vhand);
void rotateCoordinate(int16_t vaccA, int16_t vaccB,int16_t *vaccARot, int16_t *vaccBRot, float vangleRotAxis){
	*vaccARot = cos(vangleRotAxis)*vaccA + sin(vangleRotAxis)*vaccB;
	*vaccBRot = -sin(vangleRotAxis)*vaccA + cos(vangleRotAxis)*vaccB;
}
