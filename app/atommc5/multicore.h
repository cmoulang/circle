/*
 * multicore.h
 *
 *  Created on: May 5, 2020
 *      Author: chris
 */

#ifndef MULTICORE_H_
#define MULTICORE_H_

#include <circle/multicore.h>
#include <circle/screen.h>
#include <circle/memory.h>
#include <circle/types.h>
#include <circle/logger.h>
#include <circle/string.h>
#include "cyclic.h"
#include "clogobj.h"
#include "gpioutils.h"
#include "pl8if.h"

class CMulticore: public CMultiCoreSupport {
public:
	CMulticore(CMemorySystem *);
	virtual ~CMulticore();
	void Run(unsigned int);
	boolean Initialize(void);

private:
	Cpl8if m_p8if;
	static CMulticore* _this;
};

#endif /* MULTICORE_H_ */
