/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
uint16_t power(int8_t a, int8_t exp) {
// calculates a^exp
    uint16_t i, r = a;
    for (i = 1; i < exp; i++)
        r *= a;
        return(r);
}

int main(void)
    {
        int8_t a;
        init_usb_uart( 9600 ); // Initialize USB serial at 9600 baud
        printf("\n\n x x^2 x^3 x^4\n");
        for (a = 0; a < 10; a++) {
            printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));
        }
        while(1){}
}
