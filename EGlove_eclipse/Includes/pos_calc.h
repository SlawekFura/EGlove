#ifndef POS_CALC
#define POS_CALC

#include "stm32f4xx_hal.h"

typedef struct {
	int accX;
	int accZ;
	int gyroY;
	int gyroZ;
	uint8_t accXCount, accYCount;

	int posX;
	int posY;
}HandPos;

void fillHandPos(int accX,int accZ,int gyroY,int gyroZ);
char* dataToSend(HandPos vhand);

#endif /* I2C_SPI_H_ */
