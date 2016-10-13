#ifndef POS_CALC
#define POS_CALC

#include "stm32f4xx_hal.h"

#define ACC_CORRECTION_SIZE 15
#define ACC_CORRECTION_FACTOR 100
#define TIMER_PRESCALER 10000

typedef struct {
	int accX;
	int accZ;
	float angleAccX;
	float angleAccZ;
	int sinGAccX;
	int sinGAccZ;
	int corrAccDataX[ACC_CORRECTION_SIZE];
	int corrAccDataZ[ACC_CORRECTION_SIZE];
	uint8_t accXCount, accZCount;

	int gyroY;
	int gyroZ;
	float angleGyroY;
	float angleGyroZ;

	int gravElemX;
	int gravElemZ;


	float posX;
	float posY;
}HandPos;

void fillHandPos(HandPos * vhand,int16_t vaccX,int16_t vaccZ,int16_t vgyroY,
		int16_t vgyroZ, int16_t * vtimerCount);
char* dataToSend(HandPos vhand);

#endif /* I2C_SPI_H_ */
