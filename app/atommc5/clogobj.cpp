/*
 * clogobj.cpp
 *
 *  Created on: May 6, 2020
 *      Author: chris
 */
#include "clogobj.h"

CAsyncLogger *CAsyncLogger::s_pThis = 0;

CAsyncLogger::CAsyncLogger() {
	s_pThis = this;
}

CLogobj::CLogobj() {

}

CLogobj::CLogobj(const char* buff, int count) {
	strncpy(text, buff, count);
	text[count]=0;
}

CLogobj::CLogobj(const CLogobj & other) {
	strncpy(text, other.text, 100);
}
