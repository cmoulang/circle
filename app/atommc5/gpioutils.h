/*
 * gpio.h
 *
 *  Created on: Apr 27, 2020
 *      Author: chris
 */
#ifndef GPIOUTILS_H_
#define GPIOUTILS_H_

#include <circle/bcm2835.h>
#include <circle/memio.h>

#define RW 18
#define P2 7
#define TUBE 17
#define RST 4

#define A0 27
#define A2 3
#define A1 2

#define D7 25
#define D6 24
#define D5 23
#define D4 22
#define D3 11
#define D2 10
#define D1 9
#define D0 8

class CGpioUtils {
public:
    static void SetIn(int g);
    static void InitialiseGPIO();
    static void SetINP();
    static void SetOUT();
    static void SendByte(u8 data);

    static inline u8 GetData(u32 bits){
		return ((bits >> D0) & 0xf) | ((bits >> (D4 - 4)) & 0xf0);
    }

    static inline u16 GetAddress(u32 bits) {
		return ((bits >> 1) & 0x6) | ((bits >> A0) & 0x1);
	}

	static const u32 addressBits;
	static const u32 dataBits;
	static const u32 allBits;

	static const u32 CMD_REG = 0;							// 0
	static const u32 LATCH_REG = 1 << A0;					// 1
	static const u32 READ_DATA_REG = 1 << A1;				// 2
	static const u32 WRITE_DATA_REG = 1 << A0 | 1 << A1;		// 3
	static const u32 STATUS_REG = 1 << A2;					// 4

private:
    static u32 gpfsel0in;
    static u32 gpfsel1in;
    static u32 gpfsel2in;
    static u32 gpfsel0out;
    static u32 gpfsel1out;
    static u32 gpfsel2out;
};

#endif /* GPIOUTILS_H_ */
