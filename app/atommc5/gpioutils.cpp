/*
 * gpio.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: chris
 */
#include "gpioutils.h"

u32 CGpioUtils::gpfsel0in;
u32 CGpioUtils::gpfsel1in;
u32 CGpioUtils::gpfsel2in;
u32 CGpioUtils::gpfsel0out;
u32 CGpioUtils::gpfsel1out;
u32 CGpioUtils::gpfsel2out;


const u32 CGpioUtils::addressBits = 1 << A2 | 1 << A1 | 1 << A0;

const u32 CGpioUtils::dataBits = 1 << D7 | 1 << D6 | 1 << D5 | 1 << D4 | 1 << D3
		| 1 << D2 | 1 << D1 | 1 << D0;

const u32 CGpioUtils::allBits = 1 << A2 | 1 << A1 | 1 << A0 | 1 << D7 | 1 << D6
		| 1 << D5 | 1 << D4 | 1 << D3 | 1 << D2 | 1 << D1 | 1 << D0 | 1 << P2
		| 1 << TUBE | 1 << RST | 1 << RW;


void CGpioUtils::SetIn(int g) {
	uintptr reg = ARM_GPIO_GPLEV0 + ((g) / 10) * 4;
	write32(reg, read32(reg) | (1 << (((g) % 10) * 3)));
}

void CGpioUtils::InitialiseGPIO() {
	u32 pins = allBits;
	for (int i = 0; i < 32; i++) {
		if (pins & 1) {
			SetIn(i);
		}
		pins = pins >> 1;
	}
	gpfsel0in = read32(ARM_GPIO_GPFSEL0 + 0) &  030077777777;
	gpfsel1in = read32(ARM_GPIO_GPFSEL0 + 4) &  037777777700;
	gpfsel2in = read32(ARM_GPIO_GPFSEL0 + 8) &  037777000077;
	gpfsel0out = read32(ARM_GPIO_GPFSEL0 + 0) | 001100000000;
	gpfsel1out = read32(ARM_GPIO_GPFSEL0 + 4) | 000000000011;
	gpfsel2out = read32(ARM_GPIO_GPFSEL0 + 8) | 000000111100;
}

void CGpioUtils::SendByte(u8 data) {
	u32 set = ((data & 0xf) << D0) | ((data & 0xf0) << (D4 - 4));
	u32 clr = ((~data & 0xf) << D0) | ((~data & 0xf0) << (D4 - 4));
	write32(ARM_GPIO_GPCLR0, clr);
	write32(ARM_GPIO_GPSET0, set);
}

void CGpioUtils::SetINP() {
	write32(ARM_GPIO_GPFSEL0 + 0, gpfsel0in);
	write32(ARM_GPIO_GPFSEL0 + 4, gpfsel1in);
	write32(ARM_GPIO_GPFSEL0 + 8, gpfsel2in);
}

void CGpioUtils::SetOUT() {
	write32(ARM_GPIO_GPFSEL0 + 0, gpfsel0out);
	write32(ARM_GPIO_GPFSEL0 + 4, gpfsel1out);
	write32(ARM_GPIO_GPFSEL0 + 8, gpfsel2out);
}

