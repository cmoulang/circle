/*
 * multicore.cpp
 *
 *  Created on: May 5, 2020
 *      Author: chris
 */
#include "utils.h"
#include "multicore.h"
#include "clogobj.h"
#include "pl8if.h"
#include "joystick.h"

CMulticore* CMulticore::_this;

CMulticore::CMulticore(CMemorySystem* mem) :
		CMultiCoreSupport(mem) {

}

CMulticore::~CMulticore() {

}

boolean CMulticore::Initialize() {
	_this = this;
	return CMultiCoreSupport::Initialize();
}

extern volatile boolean keepGoing;
EXTERN_C void at_process();
EXTERN_C void at_initprocessor();

void CMulticore::Run(unsigned int core) {
	if (core == 2) {
		m_p8if.Run(0);
		keepGoing = false;
	} else if (core == 3) {
		at_initprocessor();
		while (1) {
			m_p8if.Next();
			at_process();
		}
	} else if (core == 1) {
		int nextout = 0;
		while (1) {
			CLogobj lo = CAsyncLogger::Get()->Dequeue(nextout);
			CLogger::Get()->Write("logMessage", LogNotice, lo.text);
		}
	} else if (core == 0) {
		CJoystick js;
		js.Run();
	}
}
