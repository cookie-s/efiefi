#include "common.h"

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL) (
        IN EFI_GUID *Protocol,
        IN VOID *Registration OPTIONAL,
        OUT VOID **Interface
        );

typedef struct {
    EFI_TABLE_HEADER Hdr;
    //
    // Task Priority Services
    //
    //EFI_RAISE_TPL RaiseTPL; // EFI 1.0+
    //EFI_RESTORE_TPL RestoreTPL; // EFI 1.0+
    char a[8*2];
    //
    // Memory Services
    //
    //EFI_ALLOCATE_PAGES AllocatePages; // EFI 1.0+
    //EFI_FREE_PAGES FreePages; // EFI 1.0+
    //EFI_GET_MEMORY_MAP GetMemoryMap; // EFI 1.0+
    //EFI_ALLOCATE_POOL AllocatePool; // EFI 1.0+
    //EFI_FREE_POOL FreePool; // EFI 1.0+
    char b[8*5];
    //
    // Event & Timer Services
    //
    //EFI_CREATE_EVENT CreateEvent; // EFI 1.0+
    //EFI_SET_TIMER SetTimer; // EFI 1.0+
    //EFI_WAIT_FOR_EVENT WaitForEvent; // EFI 1.0+
    //EFI_SIGNAL_EVENT SignalEvent; // EFI 1.0+
    //EFI_CLOSE_EVENT CloseEvent; // EFI 1.0+
    //EFI_CHECK_EVENT CheckEvent; // EFI 1.0+
    char c[8*6];
    //
    // Protocol Handler Services
    //
    //EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface; // EFI 1.0+
    //EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
    //EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+
    //EFI_HANDLE_PROTOCOL HandleProtocol; // EFI 1.0+
    //VOID* Reserved; // EFI 1.0+
    //EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify; // EFI 1.0+
    //EFI_LOCATE_HANDLE LocateHandle; // EFI 1.0+
    //EFI_LOCATE_DEVICE_PATH LocateDevicePath; // EFI 1.0+
    //EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable; // EFI 1.0+
    char d[8*9];
    //
    // Image Services
    //
    //EFI_IMAGE_LOAD LoadImage; // EFI 1.0+
    //EFI_IMAGE_START StartImage; // EFI 1.0+
    //EFI_EXIT Exit; // EFI 1.0+
    //EFI_IMAGE_UNLOAD UnloadImage; // EFI 1.0+
    //EFI_EXIT_BOOT_SERVICES ExitBootServices; // EFI 1.0+
    char e[8*5];
    //
    // Miscellaneous Services
    //
    //EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount; // EFI 1.0+
    //EFI_STALL Stall; // EFI 1.0+
    //EFI_SET_WATCHDOG_TIMER SetWatchdogTimer; // EFI 1.0+
    char f[8*3];
    //
    // DriverSupport Services
    //
    //EFI_CONNECT_CONTROLLER ConnectController; // EFI 1.1
    //EFI_DISCONNECT_CONTROLLER DisconnectController;// EFI 1.1+
    char g[8*2];
    //
    // Open and Close Protocol Services
    //
    //EFI_OPEN_PROTOCOL OpenProtocol; // EFI 1.1+
    //EFI_CLOSE_PROTOCOL CloseProtocol; // EFI 1.1+
    //EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation; // EFI 1.1+
    char h[8*3];
    //
    // Library Services
    //
    //EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle; // EFI 1.1+
    //EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer; // EFI 1.1+
    char i1[8*2];
    EFI_LOCATE_PROTOCOL LocateProtocol; // EFI 1.1+
    //EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces; // EFI 1.1+
    //EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces; // EFI 1.1+
    char i2[8*2];
    //
    // 32-bit CRC Services
    //
    //EFI_CALCULATE_CRC32 CalculateCrc32; // EFI 1.1+
    char j[8*1];
    //
    // Miscellaneous Services
    //
    //EFI_COPY_MEM CopyMem; // EFI 1.1+
    //EFI_SET_MEM SetMem; // EFI 1.1+
    //EFI_CREATE_EVENT_EX CreateEventEx; // UEFI 2.0+
    char k[8*3];
} EFI_BOOT_SERVICES;
