#ifndef TIME_H
#define TIME_H

#include "common.h"

//*******************************************************
// Bit Definitions for EFI_TIME.Daylight. See below.
//*******************************************************
#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02
//*******************************************************
// Value Definition for EFI_TIME.TimeZone. See below.
//*******************************************************
#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

//*******************************************************
//EFI_TIME
//*******************************************************
// This represents the current time information
typedef struct {
    UINT16 Year; // 1900 ? 9999
    UINT8 Month; // 1 ? 12
    UINT8 Day; // 1 ? 31
    UINT8 Hour; // 0 ? 23
    UINT8 Minute; // 0 ? 59
    UINT8 Second; // 0 ? 59
    UINT8 Pad1;
    UINT32 Nanosecond; // 0 ? 999,999,999
    INT16 TimeZone; // -1440 to 1440 or 2047
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

#endif
