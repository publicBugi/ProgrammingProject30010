//struct time {
//	int time_hseconds;
//	int time_sec;
//	int time_min;
//	int time_hour;
//	char change;
//};
//
//void initTime(struct time *clk) {
//	clk->time_hseconds = 0;
//	clk->time_sec = 0;
//	clk->time_min = 0;
//	clk->time_hour = 0;
//	clk->change = 0;
//}
//
//void incrementTime(struct time *clk) {
//	clk->time_hseconds++;
//	clk->time_sec += clk->time_hseconds > 100 ? 1 : 0;
//	clk->change += clk->time_hseconds > 100 ? 1 : 0;
//	clk->time_min += clk->time_sec > 59 ? 1 : 0;
//	clk->time_hour += clk->time_min > 59 ? 1 : 0;
//}
//
//volatile struct time clk;
//
//RCC->APB1ENR |= RCC_APB1Periph_TIM2; 	// Clock line for timer 2
//TIM2->CR1 = 0x00000001; 				// Configure [0 0 0 0 UIF 0 CKD ARPE CMS DIR OPM UDIS CEN]
//TIM2->ARR = 0x0009C3FF;					// Relead Value = 63999 = 1/100 Second.
//TIM2->PSC = 0x00000000;					// Preset = 0;
//
//TIM2->DIER |= 0x0001;					// Timer 2 Interrupts Enabled
//NVIC_SetPriority(TIM2_IRQn, 0);
//NVIC_EnableIRQ(TIM2_IRQn);
//
//void TIM2_IRQHandler(void);
//	{
//	 Interrupt function!
//	incrementTime(struct time &clk);
//	TIM2->SR &= ~0x0001; // End the interrupt.
//	}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// Copy To Main loop
// Init clk.
//initTime(&clk);
// Update PuTTy everytime 2nd digit changes.
//if (clk.change == 1) {
//	gotoXY(1,1);
//	printf("%d:%d:%d:%d", clk.time_hour, clk.time_min, clk.time_sec, clk.time_hseconds);
//}
//
//
//int prevJoystick = 0;
//struct time splitTime1;
//struct time splitTime2;
//
//if (readJoystick != prevJoystick) {	// Has Joystick changed?
//	switch (readJoystick) {				// What did it change to?
//
//		case 0 : 	// Center - Start/Stop
//			TIM2->CR1 = ~TIM2->CR1 & 0x00000001;
//			break;
//		case 1 :	// Left - Split time 1
//			__disable_irq();
//			struct time splitTime1 = clk;
//			__enable_irq();
//			break;
//		case 2 :	// Right - Split time 2
//			__disable_irq();
//			struct time splitTime2 = clk;
//			__enable_irq();
//			break;
//		case 3 :	// Down - Stop Clock, Reset time.
//			TIM2->CR1 = 0x00000000;
//			initTime(&clk);
//			break;
//	}
//}
//
