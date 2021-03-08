/*
 * logobj.h
 *
 *  Created on: May 6, 2020
 *      Author: chris
 */

#include <string.h>
#include <circle/string.h>
#include "cyclic.h"


#ifndef LOGOBJ_H_
#define LOGOBJ_H_

class CLogobj {
public:
	char text[100];
	CLogobj();
	CLogobj(const char* buff, int count);
	CLogobj(const CLogobj & other);
};

class CAsyncLogger {
public:
	CAsyncLogger();
	static void logMessage(const char* pMessage, ...) {
        va_list var;
        va_start (var, pMessage);
        CString Message;
                Message.FormatV (pMessage, var);

		Get()->buffer.Enqueue(CLogobj((const char*)Message, Message.GetLength()));
	}
	static CAsyncLogger* Get() {
        return s_pThis;
	}
	CLogobj Dequeue(int &nextout) {
		return buffer.Dequeue(nextout);
	};
private:
	static CAsyncLogger  *s_pThis;
	CCyclic<CLogobj, 1000> buffer;
};

#endif /* LOGOBJ_H_ */
