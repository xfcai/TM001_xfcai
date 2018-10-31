// Do not remove the include below
#include "mApp04.h"
#define setbit(x, y) x|=(1<<y)
#define clrbit(x, y) x&=~(1<<y)
Timer fastT;
Timer slowT;
Timer normalT;

float tValue;

DigitalIn clearZero(P2_8);	//The On Board UBT button
DigitalOut led(LED4);
DigitalOut led1(LED1);
// Define p6 as interrupt Input of Clock
InterruptIn S_CLK(p6);
DigitalIn S_DATA(p5);
DigitalOut S_CLEAR_ZERO(p7);

int aTime[25];
int pDownCount;
int pUpCount;
int nib5, nib4, nib3, nib2, nib1, nib0;
int memValue;
int memReadValue;
float mRealValue;
bool memPulseUp;
bool memPulseDown;
bool memClockStart;

void ISR1(){		// Define Interrupt function
//	normalT.stop();
	aTime[pUpCount] = normalT.read_us();
	normalT.reset();
//	normalT.start();
	led1 = !led1;
	pUpCount++;


	if (pUpCount <= 20){
		if (pUpCount < 5){
			if (S_DATA.read() == 1)
				setbit(nib0, (pUpCount - 1));
			else
				clrbit(nib0, (pUpCount - 1));
		}
		if (pUpCount > 4 and pUpCount < 9 ){
			if (S_DATA.read() == 1)
				setbit(nib1, (pUpCount - 5));
			else
				clrbit(nib1, (pUpCount - 5));
		}
		if (pUpCount > 8 and pUpCount < 13 ){
			if (S_DATA.read() == 1)
				setbit(nib2, ( pUpCount - 9));
			else
				clrbit(nib2, ( pUpCount - 9));
		}
		if (pUpCount > 12 and pUpCount < 17 ){
			if (S_DATA.read() == 1)
				setbit(nib3, (pUpCount - 13));
			else
				clrbit(nib3, (pUpCount - 13));
		}
		if (pUpCount > 16 and pUpCount < 21 ){
			if (S_DATA.read() == 1)
				setbit(nib4, (pUpCount - 17));
			else
				clrbit(nib4, (pUpCount - 17));
		}
		if (pUpCount > 20 and pUpCount < 25 ){
			if (S_DATA.read() == 1)
				setbit(nib5, (pUpCount - 21));
			else
				clrbit(nib5, (pUpCount - 21));
		}




		if (S_DATA.read() == 1)
			setbit(memValue, pUpCount - 1);
		else
			clrbit(memValue, pUpCount - 1);
	}
	if (pUpCount == 21) {
		memValue = 0x000FFFFF & memValue;
		if (S_DATA.read() == 0)
			clrbit(memValue, 31);
		else
			setbit(memValue, 31);
	}
	if (pUpCount >= 24){
		memReadValue = memValue;
		mRealValue = memReadValue * 0.01;
	}
}

int main() 
{ 
	S_CLK.rise(&ISR1);
	slowT.start();
	normalT.start();
	pDownCount = 0;
//	memReadValue = 0x007F007F;
	while(1) 
	{ 
		if (clearZero == 1)
			S_CLEAR_ZERO = 1;
		else
			S_CLEAR_ZERO = 0;
		if ((S_CLK.read() == 1) and (memPulseUp == 0))
			fastT.start();
		memPulseUp = S_CLK.read();
		if (fastT.read_ms() > 80){
			fastT.reset();
			memClockStart = true;
			pUpCount = 0;
		}


		if (slowT.read() >= 1){
			led=!led;
			printf("The real value is %.4f\r\n", mRealValue);
			printf("The pUpCount = %d \r\n", pUpCount);
			printf("The memReadValue = %X, %d \r\n", memReadValue, memReadValue);
			printf("The nib0 = %x\r\n", nib0);
			printf("The nib1 = %x\r\n", nib1);
			printf("The nib2 = %x\r\n", nib2);
			printf("The nib3 = %x\r\n", nib3);
			printf("The nib4 = %x\r\n", nib4);
			printf("The nib5 = %x\r\n", nib5);
			printf("The aTime[%d] = %d\r\n",pDownCount, aTime[pDownCount]);
			pDownCount++;
			if (pDownCount > 23)
				pDownCount = 0;
			slowT.reset();

		}
	} 
}
//  Auto Added by "SMeshLink SMeshStudio"

