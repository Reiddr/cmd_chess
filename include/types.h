#ifndef TYPES_H
#define TYPES_H

#include <limits.h>

#if UCHAR_MAX == 255
typedef unsigned char uint8;
#else
#error "No suitable type found for uint8"
#endif

#if USHRT_MAX == 65535
typedef unsigned short uint16;
#else
#error "No suitable type found for uint16"
#endif

#endif /*TYPES_H*/
