/*
 * joystick.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: chris
 */

#include "joystick.h"
#include "utils.h"

CJoystick* CJoystick::__this;

CJoystick::CJoystick() {
	CJoystick::__this = this;
}

CJoystick::~CJoystick() {
}

void CJoystick::Run() {
	boolean bFound = FALSE;

	for (unsigned nDevice = 1; 1; nDevice++) {
		CString DeviceName;
		DeviceName.Format("upad%u", nDevice);

		CUSBGamePadDevice *pGamePad =
				(CUSBGamePadDevice *) CDeviceNameService::Get()->GetDevice(
						DeviceName, FALSE);
		if (pGamePad == 0) {
			break;
		}

		const TGamePadState *pState = pGamePad->GetInitialState();
		assert(pState != 0);

		logMessage("Gamepad %u: %d Button(s) %d Hat(s)", nDevice,
				pState->nbuttons, pState->nhats);

		for (int i = 0; i < pState->naxes; i++) {
			logMessage("Gamepad %u: Axis %d: Minimum %d Maximum %d", nDevice,
					i + 1, pState->axes[i].minimum, pState->axes[i].maximum);
		}

		pGamePad->RegisterStatusHandler(GamePadStatusHandler);

		bFound = TRUE;
	}
}

void CJoystick::GamePadStatusHandler(unsigned nDeviceIndex,
		const TGamePadState *pState) {
	CString Msg;
	unsigned char portb = 0;
	Msg.Format("Gamepad %u: Buttons 0x%X", nDeviceIndex + 1, pState->buttons);
	if (pState->buttons) {
		portb |= JOY_JUMP;
	}

	CString Value;

	if (pState->naxes > 1) {
		Msg.Append(" Axes");

		int x = pState->axes[0].value & 0xFF;
		portb |= (x < JOY_LOW) ? JOY_LEFT : 0;
		portb |= (x > JOY_HIGH) ? JOY_RIGHT : 0;

		x = pState->axes[1].value & 0xFF;
		portb |= (x < JOY_LOW) ? JOY_UP : 0;
		portb |= (x > JOY_HIGH) ? JOY_DOWN : 0;

		for (int i = 0; i < pState->naxes; i++) {
			int x = pState->axes[i].value & 0xFF;
			Value.Format(" %x", x);
			Msg.Append(Value);
		}
	}

	if (pState->nhats > 0) {
		Msg.Append(" Hats");

		for (int i = 0; i < pState->nhats; i++) {
			Value.Format(" %x", pState->hats[i]);
			Msg.Append(Value);
		}
	}

	__this->portb = portb;
	logMessage(Msg);
}
