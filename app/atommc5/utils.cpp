#include "utils.h"
#include "clogobj.h"
#include "pl8if.h"
#include "ff.h"
#include "joystick.h"

unsigned char globalData[512];
unsigned char configByte=0xFF;
unsigned char blVersion=0xFF;
unsigned char CardType=1;
unsigned char portbDir=0;

EXTERN_C void WriteDataPort(unsigned char x) {
    Cpl8if::Get()->Write(x);
}

EXTERN_C int ReadIBF() {
    return Cpl8if::Get()->getIbf();
}

EXTERN_C unsigned char ReadPort() {
	return Cpl8if::Get()->ReadDataPort();
}

EXTERN_C int ReadAddress() {
	return Cpl8if::Get()->ReadAddress();
}

EXTERN_C void logMessage(const char* pMessage, ...) {
	CAsyncLogger::logMessage(pMessage);
}

EXTERN_C void get_fileinfo_special(FILINFO *filinfo) {
	logMessage("get_fileinfo_special");
}

EXTERN_C void WriteEeprom(int add, int val) {
	CAsyncLogger::logMessage("WriteEeprom address=%x value=%x", add, val);
}

EXTERN_C unsigned char ReadEeprom(int add) {
	CAsyncLogger::logMessage("ReadEeprom %x", add);
	return 0;
}

EXTERN_C unsigned char ReadJoystick() {
	return CJoystick::Get()->getPortb();
}
