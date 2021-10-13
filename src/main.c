
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "IR_interface.h"


void voidDetermineKey(u8 Copy_u8Key)
{
	switch(Copy_u8Key)
	{
		case ONE		:	MGPIO_voidSetPinValue(GPIOA, PIN1, HIGH);	break;
		case TWO		:	MGPIO_voidSetPinValue(GPIOA, PIN2, HIGH);	break;
		case THREE		:	MGPIO_voidSetPinValue(GPIOA, PIN3, HIGH);	break;
		case STOP		:	MGPIO_voidSetPinValue(GPIOA, PIN1, LOW);
		                    MGPIO_voidSetPinValue(GPIOA, PIN2, LOW);
	                      	MGPIO_voidSetPinValue(GPIOA, PIN3, LOW);    break;

	}
}
void main (void)
{
	/* RCC Initialize */
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(APB2, IOPA); /* GPIOA Enable Clock */

	MGPIO_voidSetPinDirection(GPIOA,PIN0,INPUT_FLOATING); /* A0 Input Floating        */
	MGPIO_voidSetPinDirection(GPIOA,PIN1,OUTPUT_SPEED_2MHZ_PP); /* A1 OUTPUT_SPEED_2MHZ_PP        */
	MGPIO_voidSetPinDirection(GPIOA,PIN2,OUTPUT_SPEED_2MHZ_PP); /* A2 OUTPUT_SPEED_2MHZ_PP        */
	MGPIO_voidSetPinDirection(GPIOA,PIN3,OUTPUT_SPEED_2MHZ_PP); /* A3 OUTPUT_SPEED_2MHZ_PP        */

	/* EXTI Initializtion */
	MEXTI_voidSetCallBack(HIR_voidGetFrame, LINE0);
	MEXTI_voidInit(); /* A0 EXTI0 Enabled / Falling Edge */

	/* Enable EXTI0 from NVIC */
	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(6); /* EXTI0 */

	/* SysTick Init */
	MSTK_voidInit();


	HIR_voidSetCallBack(voidDetermineKey);


}
