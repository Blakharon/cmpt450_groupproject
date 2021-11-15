#include <stdio.h>
#include "../defines.h"

extern volatile uint8_t * top;

void isr(void)
{
	printf("Interrupt\n");
	unsigned *common_val =  (unsigned*) 0x8f000000;
    *common_val = 1;  
	*top = 0x00;
	// printf("%d\n", *top);
	printf("Interrupt finished\n");
}
