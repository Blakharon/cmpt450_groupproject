#include <stdio.h>
#include "../defines.h"

extern volatile uint8_t * top;

void isr(void)
{
//	printf("Interrupt\n");
	//stage += 1;
	*top = 0x00;
	// printf("%d\n", *top);
	printf("\n Accelerator finished \n");
}
