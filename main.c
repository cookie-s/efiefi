#include "common.h"
#include "boot_serv.h"
#include "http_binding_def.h"
#include "tcp_def.h"

#define EFI_SUCCESS 0

#define EFI_HTTP_SERVICE_BINDING_PROTOCOL_GUID \
{0xbdc8e6af, 0xd9bc, 0x4379,\
    {0xa7, 0x2a, 0xe0, 0xc4, 0xe7, 0x5d, 0xae, 0x1c}}

#define EFI_HTTP_PROTOCOL_GUID \
{0x7A59B29B, 0x910B, 0x4171,\
    {0x82, 0x42, 0xA8, 0x5A, 0x0D, 0xF2, 0x5B, 0x5B}}

#define EFI_TCP4_SERVICE_BINDING_PROTOCOL_GUID \
{0x00720665,0x67EB,0x4a99,\
    {0xBA,0xF7,0xD3,0xC3,0x3A,0x1C,0x7C,0xC9}}

#define EFI_TCP4_PROTOCOL_GUID \
{0x65530BC7,0xA359,0x410f,\
    {0xB0,0x10,0x5A,0xAD,0xC7,0xEC,0x2B,0x62}}

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING) (
        IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
        IN CHAR16                                   *String
        );
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void             *a;
    EFI_TEXT_STRING  OutputString;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    char a[52];
    EFI_HANDLE                       ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    //EFI_RUNTIME_SERVICES *RuntimeServices;
    char b[8];
    EFI_BOOT_SERVICES *BootServices;
} EFI_SYSTEM_TABLE;

EFI_STATUS EFIAPI EfiMain (
        IN EFI_HANDLE ImageHandle,
        IN EFI_SYSTEM_TABLE *SystemTable
        )
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"hogehogehoge");
    EFI_GUID tcp_guid = EFI_TCP4_SERVICE_BINDING_PROTOCOL_GUID;
    EFI_SERVICE_BINDING_PROTOCOL *tcp_binding;
    SystemTable->BootServices->LocateProtocol(&tcp_guid, NULL, (VOID**)&tcp_binding);

    EFI_TCP4_PROTOCOL *tcp;
    tcp_binding->CreateChild(tcp_binding, (VOID*)&tcp);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, tcp == 0 ? L"hogehogehoge" : L"fuga");
    //EFI_GUID http_proto_guid = EFI_HTTP_SERVICE_BINDING_PROTOCOL_GUID;
    //EFI_GUID http_proto_guid = EFI_HTTP_PROTOCOL_GUID;
    //EFI_SERVICE_BINDING_PROTOCOL *http_binding;
    //SystemTable->BootServices->LocateProtocol(&http_proto_guid, NULL, (VOID**)&http_binding);
    //SystemTable->ConOut->OutputString(SystemTable->ConOut, http_binding == 0 ? L"hogehogehoge" : L"fuga");

    //EFI_HTTP_PROTOCOL http_proto;
    //http_binding->CreateChild(http_binding, (VOID*)&http_proto);
    //SystemTable->ConOut->OutputString(SystemTable->ConOut, (CHAR16*)&http_proto);
    return EFI_SUCCESS;
}
