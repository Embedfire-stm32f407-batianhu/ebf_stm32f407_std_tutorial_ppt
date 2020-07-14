#include "stc89c51.h"


int main(void)
{
    uchar value;

	IAP_Init();
	IAP_EraseSector(0x2000);
	IAP_WriteData(0x2000, 0x55);
	value = IAP_ReadData(0x2000);
	P1 = value;

	while (1);
}