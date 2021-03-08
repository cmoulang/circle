/*
 * joystick.h
 *
 *  Created on: Jun 4, 2020
 *      Author: chris
 */

#include <circle/devicenameservice.h>
#include <circle/usb/usbhcidevice.h>
#include <circle/usb/usbgamepad.h>

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define JOY_RIGHT 0x1
#define JOY_LEFT 0x2
#define JOY_DOWN 0x4
#define JOY_UP 0x8
#define JOY_JUMP 0x10

#define JOY_LOW 0x40
#define JOY_HIGH 0xC0

class CJoystick {
public:
	CJoystick();
	virtual ~CJoystick();

	volatile unsigned char getPortb() const {
		return portb;
	}

	void Run();

	static CJoystick* Get() {
		return __this;
	}

private:
	volatile unsigned char portb;

	static CJoystick* __this;


	static void GamePadStatusHandler(unsigned nDeviceIndex,
			const TGamePadState *pState);
};

#endif /* JOYSTICK_H_ */
