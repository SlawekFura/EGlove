#ifndef POS_CALC
#define POS_CALC

#include "stm32f4xx_hal.h"

#define ACC_CORRECTION_SIZE 20
#define ACC_CORRECTION_FACTOR 70
#define TIMER_PRESCALER 125

typedef struct {
	int16_t accX;
	int16_t accY;
	int16_t accZ;
	int16_t accXRot;
	int16_t accYRot;
	int16_t accZRot;
	float angleAccY;
	float angleAccX;
	float angleAccZ;

	int16_t sinGAccX;
	int16_t sinGAccY;
	int16_t sinGAccZ;
	int16_t corrAccDataX[ACC_CORRECTION_SIZE];
	int16_t corrAccDataY[ACC_CORRECTION_SIZE];
	int16_t corrAccDataZ[ACC_CORRECTION_SIZE];
	uint8_t accXCount, accYCount, accZCount;

	int16_t gyroX;
	int16_t gyroY;
	int16_t gyroZ;
	float angleGyroX;
	float angleGyroY;
	float angleGyroZ;

	int16_t gravElemX;
	int16_t gravElemZ;

	float velX, velXPrev, velXAvg, velXAvgArr[ACC_CORRECTION_SIZE];
	float velY, velYPrev, velYAvg, velYAvgArr[ACC_CORRECTION_SIZE];
	float posX, posXPrev;
	float posY, posYPrev;
}HandPos;

void fillHandPos(HandPos * vhand,int16_t vaccX,int16_t vaccY,int16_t vaccZ,int16_t vgyroX, int16_t vgyroY,
		int16_t vgyroZ);
char* dataToSend(HandPos vhand);
void rotateCoordinate(int16_t vaccA, int16_t vaccB,int16_t *vaccARot, int16_t *vaccBRot, float vangleRotAxis);

#endif /* I2C_SPI_H_ */
