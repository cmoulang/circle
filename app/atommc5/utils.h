#ifndef __UTILS_H
#define __UTILS_H

#if defined(__cplusplus)
#define EXTERN_C extern "C"
#else
#define EXTERN_C /* */
#endif

EXTERN_C void logMessage(const char*, ...);

#endif
