#ifndef COMMON_H
#define COMMON_H

#define IN
#define OUT
#define OPTIONAL
#define EFIAPI

#define NULL 0

typedef unsigned char BOOLEAN;
typedef unsigned long long UINTN;
typedef unsigned long long UINT64;
typedef unsigned long UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;

typedef short INT16;

typedef unsigned char CHAR8;
typedef unsigned short CHAR16;
typedef unsigned long long EFI_STATUS;
typedef void *EFI_HANDLE;
typedef void VOID;

typedef VOID* EFI_EVENT;

typedef struct {
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct {
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8  Data4[8];
} EFI_GUID;

#endif
