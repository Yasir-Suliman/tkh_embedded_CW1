#include <stdio.h>
#include <util/delay.h>

void DIO_init();
void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction);
void DIO_SetPinState(unsigned char port, int pin, unsigned char state);
