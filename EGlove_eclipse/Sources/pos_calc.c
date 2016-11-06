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
		        int16_t vgyroX,	int16_t vgyroY, int16_t vgyroZ,
				ADC_HandleTypeDef * vhandADC/*, int16_t vvalADC*/){
	vhand->accX = vaccX;
	vhand->accY = vaccY;
	vhand->accZ = vaccZ;
	vhand->accCount++;
	vhand->accCount %= ACC_CORRECTION_SIZE;
	vhand->corrAccDataX[vhand->accCount] = vaccX;
	vhand->corrAccDataY[vhand->accCount] = vaccY;
	vhand->corrAccDataZ[vhand->accCount] = vaccZ;
	vhand->leftButtonState = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);

//	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
//		if(abs(vhand->corrAccDataY[i]-vhand->corrAccDataY[vhand->accYCount])>ACC_CORRECTION_FACTOR)
//			break;
//			if(i==ACC_CORRECTION_SIZE-1){
//				vhand->sinGAccY = vaccY;
//				 if((float)vhand->sinGAccY/(INT16_MAX)*2>1)
//					 vhand->angleAccY = asin(1);
//				 else if((float)vhand->sinGAccY/(INT16_MAX)*2<-1)
//					 vhand->angleAccY = asin(-1);
//				 else{
//					 vhand->angleAccY = (asin((float)vhand->sinGAccY/(INT16_MAX)*2));
//					 vhand->angleGyroX = -vhand->angleAccY;
//				 }
//			}
//	}
//
//	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
//		if(abs(vhand->corrAccDataZ[i]-vhand->corrAccDataZ[vhand->accZCount])>ACC_CORRECTION_FACTOR + 100)
//			break;
//		if(i==ACC_CORRECTION_SIZE-1){
//				vhand->sinGAccZ = vaccZ;
//				 if((float)vhand->sinGAccZ/(INT16_MAX)*2>1)
//					 vhand->angleAccZ = asin(1);
//				 else if((float)vhand->sinGAccZ/(INT16_MAX)*2<-1)
//					 vhand->angleAccZ = asin(-1);
//				 else{
//					 vhand->angleAccZ = (asin((float)vhand->sinGAccZ/(INT16_MAX)*2));
//				 }
//			}
//	}
//
//	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
//		if(abs(vhand->corrAccDataX[i]-vhand->corrAccDataX[vhand->accXCount])>ACC_CORRECTION_FACTOR)
//			break;
//			if(i==ACC_CORRECTION_SIZE-1){
//				vhand->sinGAccX = vaccX;
//				 if((float)vhand->sinGAccX/(INT16_MAX)*2>1)
//					 vhand->angleAccX = asin(1);
//				 else if((float)vhand->sinGAccX/(INT16_MAX)*2<-1)
//					 vhand->angleAccX = asin(-1);
//				 else{
//					 vhand->angleAccX = (asin((float)vhand->sinGAccX/(INT16_MAX)*2));
//					 vhand->angleGyroY = vhand->angleAccX;
//				 }
//			}
//	}



	vhand->posX -= (((float)vgyroZ+ vhand->posXPrev + 170)/INT16_MAX*250*3.1415/180/TIMER_PRESCALER*1.19)*250;
	vhand->posY -= (((float)vgyroY+ vhand->posYPrev - 40)/INT16_MAX*250*3.1415/180/TIMER_PRESCALER*1.19 )*250;

	vhand->posXPrev = (float)vgyroZ;
	vhand->posYPrev = (float)vgyroY;

	if(vhand->posX > 1366)	vhand->posX = 1366;
	if(vhand->posY > 768)		vhand->posY = 768;
	if(vhand->posX < 0)	vhand->posX = 0;
	if(vhand->posY < 0)	vhand->posY = 0;

	// if (HAL_ADC_PollForConversion(vhandADC, 1) == HAL_OK)
	vhand->ADCCount++;
	vhand->ADCCount %= ADC_SCROLL_ARR_SIZE;

	if(!(vhand->ADCCount % 100 && ((vhand->valADCavg = HAL_ADC_GetValue(vhandADC)) > ADC_LOWER_LIMIT )
		&& vhand->valADCavg < ADC_UPPER_LIMIT)){
		vhand->valADCavgTemp0 = vhand->valADCavgTemp1;
		vhand->valADCavgTemp1 = vhand->valADCavg;
		if(vhand->valADCavgTemp0 < ADC_LOWER_LIMIT)
			vhand->valADCavgTempOUT = 0;
		vhand->valADCavgTempOUT = vhand->valADCavgTemp1 - vhand->valADCavgTemp0;
		HAL_ADC_Start(vhandADC);
	}

//	if(vhand->ADCCount == 1){
//		vhand->valADCavg = 0;
//		for(int i = 1; i<ADC_SCROLL_ARR_SIZE ; i++){
//			vhand->valADCavg += (vhand->valADC[i] - vhand->valADC[i-1]);
//		}
//	}
	//vhand->valADCavg /= ADC_SCROLL_ARR_SIZE;

//	vhand->velX +=(((float)(/*vhand->accYRot*/vaccY + vhand->velXPrev)))/INT16_MAX/TIMER_PRESCALER;
//	vhand->velY +=((float)(/*vhand->accZRot*/vaccZ + vhand->velYPrev)/2 - INT16_MAX/2)/INT16_MAX/TIMER_PRESCALER;
//	vhand->velXPrev = vaccY;//vhand->accYRot;
//	vhand->velYPrev = vaccZ;//vhand->accZRot;
//
//	vhand->velXAvgArr[vhand->accXCount] = vhand->velX;
//	vhand->velYAvgArr[vhand->accYCount] = vhand->velY;
//	for(int i=0;i<ACC_CORRECTION_SIZE;i++){
//		vhand->velXAvg+=vhand->velXAvgArr[i];
//		vhand->velYAvg+=vhand->velYAvgArr[i];
//		if(i == ACC_CORRECTION_SIZE-1){
//			vhand->velXAvg /= ACC_CORRECTION_SIZE;
//			vhand->velYAvg /= ACC_CORRECTION_SIZE;
//		}
//	}
//
//	vhand->posX+=(float)(vhand->velX + vhand->posXPrev)/2/TIMER_PRESCALER;
//	vhand->posY+=(float)(vhand->velY + vhand->posYPrev)/2/TIMER_PRESCALER;
//	vhand->posXPrev = vhand->velX;
//	vhand->posYPrev = vhand->velY;

}
char* dataToSend(HandPos vhand);
void rotateCoordinate(int16_t vaccA, int16_t vaccB,int16_t *vaccARot, int16_t *vaccBRot, float vangleRotAxis){
	*vaccARot = cos(vangleRotAxis)*vaccA + sin(vangleRotAxis)*vaccB;
	*vaccBRot = -sin(vangleRotAxis)*vaccA + cos(vangleRotAxis)*vaccB;
}

void fillDataToSend(char *arr,int16_t arrSize,HandPos * vhand){
for(int i = 0;;){
		if(i>=arrSize)
			break;
		if(i==0)arr[i]='G';
		if(i==1)arr[i]='X';
		if(i==6)arr[i]='Y';
		if(i==11)arr[i]='L';
		if(i==13)arr[i]='V';
		if(i>=18)arr[i]='A';
		i++;
		if(i==2)
			for(int j=0;j<4;j++){
				int16_t k = (int16_t)(vhand->posX/pow(10,3-j))%10;
				itoa(abs(k),arr+i,10);
				i++;
			};
		if(i==7)
			for(int j=0;j<4;j++){
				int16_t k = (int16_t)(vhand->posY/pow(10,3-j))%10;
				itoa(abs(k),arr+i,10);
				i++;
			};
		if(i==12){
			itoa(abs(vhand->leftButtonState),arr+i,10);
			i++;
		}
		if(i==14)
		for(int j=0;j<4;j++){
			int m = j;
			if(j>0&&vhand->valADCavgTempOUT<0)
				m--;
			int k = (int16_t)(vhand->valADCavgTempOUT/pow(10,2-m))%10;

			if(j==0&&vhand->valADCavgTempOUT<0){
				arr[i]='-';
				itoa(abs(k),arr+i+1,10);
				i++;j++;
			}
			else if(j==0&&vhand->valADCavgTempOUT>=0){
				arr[i]='0';
				itoa(abs(k),arr+i+1,10);
				i++;j++;
			}
			else{
				i++;
				itoa(abs(k),arr+i,10);
			}
//			int16_t k = (int16_t)(vhand->valADCavgTempOUT/pow(10,3-j))%10;
//			itoa(abs(k),arr+i,10);
//			i++;
		};

	}
}
