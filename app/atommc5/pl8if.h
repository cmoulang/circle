/*
 * pl8if.h
 *
 *  Created on: Apr 30, 2020
 *      Author: chris
 */

#ifndef PL8IF_H_
#define PL8IF_H_

#include <circle/screen.h>
#include <circle/memory.h>
#include <circle/types.h>
#include <circle/logger.h>
#include <circle/spinlock.h>
#include "cyclic.h"
#include "gpioutils.h"

class Cpl8if {
public:
	Cpl8if();
	void Run(unsigned int);
	void Write(u8);
	unsigned int Read();
	unsigned char ReadDataPort();
	unsigned int ReadAddress();
	u32 Next();
	static Cpl8if* Get();
	int ResetIBOV();

	volatile int getIbf() const {
		return IBF;
	}

	volatile int getIbov() const {
		return IBOV;
	}

	volatile int getObf() const {
		return OBF;
	}

private:
	CSpinLock spinLock { TASK_LEVEL };

	volatile int interruptFlag { 0 };

	volatile int IBF { 0 };
	volatile int OBF { 0 };
	volatile int IBOV { 0 };

	volatile unsigned int latchedAddress { 0 };
	volatile unsigned char outputBuffer { 0 };
	volatile unsigned char inputBuffer { 0 };

	static Cpl8if* __this;
	int HandleExternalRead(u32);
	int HandleExternalWrite(u32);
};
#endif /* PL8IF_H_ */

