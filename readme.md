This project us the measurement card of TM-003 which has two power pin, 2 output pin and 1 clear inout pin.
This power is 0 - 3.3V
The clear input will set the ouput to zero when it is connected to voltage zero.
The output has a clock output and data output. The clock output as following:
pulse                       unit
aTime[0] = 133933           μs
aTime[1] = 371              μs
aTime[2] = 369              μs
aTime[3] = 369              μs
aTime[4] = 731              μs
aTime[5] = 368              μs
aTime[6] = 366              μs
aTime[7] = 370              μs
aTime[8] = 740              μs
aTime[9] = 369              μs
aTime[10] = 371             μs
aTime[11] = 372             μs
aTime[12] = 743             μs
aTime[13] = 373             μs
aTime[14] = 359             μs
aTime[15] = 371             μs
aTime[16] = 742             μs
aTime[17] = 370             μs
aTime[18] = 369             μs
aTime[19] = 371             μs
aTime[20] = 792             μs
aTime[21] = 373             μs
aTime[22] = 371             μs
aTime[23] = 372             μs
From the data we can find the following:
the word use 20 bit for number, the 21 bit is sign bit. 133933 μs seperate one 20 bits word. use long pulse to seperate 4 bits.
We use interrupt to get the rise edge and to calculate the number.
The xbed LPC1687 has been used to read the TM-003 board for length measurement.
