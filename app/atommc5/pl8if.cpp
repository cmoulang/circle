/*
 * pl8if.cpp
 *
 *  Created on: Apr 30, 2020
 *      Author: chris
 */

#include "pl8if.h"

#include "utils.h"

Cpl8if::Cpl8if() {
	__this = this;
}

Cpl8if* Cpl8if::__this;

Cpl8if* Cpl8if::Get() {
	return __this;
}

void Cpl8if::Write(u8 data) {
	spinLock.Acquire();
	OBF = 1; // Output buffer is full
	outputBuffer = data; // debug

	write32(ARM_GPIO_GPCLR0, CGpioUtils::dataBits);
	u32 set = (data * ((1 << D0) | (1 << (D4 - 4)))) & CGpioUtils::dataBits;
	write32(ARM_GPIO_GPSET0, set);

	spinLock.Release();
}

int Cpl8if::HandleExternalRead(u32 x) {
	u32 address = CGpioUtils::GetAddress(x);
	this->OBF = 0;
	CGpioUtils::SetOUT();

	while (!(x & (1 << P2))) {
		x = read32(ARM_GPIO_GPLEV0);
	};

	do {
		x = read32(ARM_GPIO_GPLEV0);
	} while ((x & (1 << P2)));
    return address != 0;
}

int Cpl8if::HandleExternalWrite(u32 x) {
	CGpioUtils::SetINP();
	u32 address = CGpioUtils::GetAddress(x);

	while (!(x & (1 << P2))) {
		x = read32(ARM_GPIO_GPLEV0);
	};

	u32 prev = x;
	do {
		prev = x;
		x = read32(ARM_GPIO_GPLEV0);
	} while ((x & (1 << P2)));

	if (this->IBF) {
		// Input Buffer is full - set overflow flag
		// The data is discarded
		this->IBOV = 1;
	} else {
		spinLock.Acquire();
		this->IBF = 1;
		this->inputBuffer = CGpioUtils::GetData(prev);
		this->latchedAddress = address;
		spinLock.Release();
	}
	return 1;
}

int Cpl8if::ResetIBOV() {
	spinLock.Acquire();
	int retval = IBOV;
	IBOV = 0;
	spinLock.Release();
	return retval;
}

unsigned int Cpl8if::Read() {
	spinLock.Acquire();
	this->IBF = 0;
	unsigned int retval = this->inputBuffer | (this->latchedAddress << 8);
	spinLock.Release();
	return retval;
}

unsigned char Cpl8if::ReadDataPort() {
	spinLock.Acquire();
	this->IBF = 0;
	unsigned int retval = this->inputBuffer;
	spinLock.Release();
	return retval;
}

unsigned int Cpl8if::ReadAddress() {
	return this->latchedAddress;
}

void Cpl8if::Run(unsigned int x) {
	CGpioUtils::InitialiseGPIO();
	logMessage("p8if running..");
	while (1) {
		u32 x = read32(ARM_GPIO_GPLEV0);
		if (!(x & (1 << TUBE))) {
			int doInterrupt = 0;
			if (x & (1 << RW)) {
				doInterrupt = HandleExternalRead(x);
				x = read32(ARM_GPIO_GPLEV0);
			}
			if (!(x & (1 << TUBE)) && !(x & (1 << RW))) {
				doInterrupt = HandleExternalWrite(x);
			}
			if (doInterrupt) {
				this->interruptFlag = 1;
			}
		}
		if (!(x & (1 << RST))) {
			break;
		}
	}

	logMessage("p8if EXITING..");
}

u32 Cpl8if::Next() {
	interruptFlag = 0;
	while (!interruptFlag) {

	}
	return 0;
}
