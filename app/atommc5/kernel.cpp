//
// kernel.cpp
//
#include "kernel.h"
#include "multicore.h"
#include "pl8if.h"

static const char FromKernel[] = "kernel";

CKernel::CKernel(void) :
		m_Screen(m_Options.GetWidth(), m_Options.GetHeight()), m_Timer(
				&m_Interrupt), m_Logger(m_Options.GetLogLevel(), &m_Timer), m_USBHCI(
				&m_Interrupt, &m_Timer), m_EMMC(&m_Interrupt, &m_Timer,
				&m_ActLED)
// TODO: add more member initializers here
{
}

CKernel::~CKernel(void) {
}

boolean CKernel::Initialize(void) {
	boolean bOK = TRUE;

	if (bOK) {
		bOK = m_Screen.Initialize();
	}

	if (bOK) {
		bOK = m_Serial.Initialize(115200);
	}

	if (bOK) {
		CDevice *pTarget = m_DeviceNameService.GetDevice(
				m_Options.GetLogDevice(), FALSE);
		if (pTarget == 0) {
			pTarget = &m_Screen;
		}

		bOK = m_Logger.Initialize(pTarget);
	}

	if (bOK) {
		bOK = m_Interrupt.Initialize();
	}

	if (bOK) {
		bOK = m_Timer.Initialize();
	}

	if (bOK) {
		bOK = m_USBHCI.Initialize();
	}

	if (bOK) {
		bOK = m_EMMC.Initialize();
	}

	return bOK;
}

volatile boolean keepGoing=true;

TShutdownMode CKernel::Run(void) {
	m_Logger.Write(FromKernel, LogNotice,
			"Compile time: " __DATE__ " " __TIME__);

	CAsyncLogger asyncLogger;
	CMulticore multicore(&m_Memory);
	multicore.Initialize();

	m_Logger.Write(FromKernel, LogNotice, "Started...");

	multicore.Run(0);
	while (keepGoing) {
	};

	return ShutdownReboot;
}
