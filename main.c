#include "common.h"
#include "file_proto.h"
#include "filesystem_proto.h"
#include "boot_serv.h"
#include "status.h"

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
    char                             a[52];
    EFI_HANDLE                       ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    //EFI_RUNTIME_SERVICES *RuntimeServices;
    char b[8];
    EFI_BOOT_SERVICES *BootServices;
} EFI_SYSTEM_TABLE;




EFI_SYSTEM_TABLE *gST;
EFI_BOOT_SERVICES *gBS;

int dfs(EFI_FILE_PROTOCOL *dir, int depth) {
    if(depth>3) return 0;
    while(1) {
        EFI_FILE_INFO finfo;
        UINTN size;
        size = sizeof(finfo);
        EFI_STATUS stat = dir->Read(dir, &size, &finfo);
        if(stat != EFI_SUCCESS) break;
        if(size == 0) break;

        // pass hidden files, '.' and '..'
        if(finfo.FileName[0] == '.') continue;

        for(int i=0; i<depth; i++)
            gST->ConOut->OutputString(gST->ConOut, L" ");
        gST->ConOut->OutputString(gST->ConOut, L"- ");
        gST->ConOut->OutputString(gST->ConOut, finfo.FileName);
        gST->ConOut->OutputString(gST->ConOut, L"\r\n");
        if(finfo.Attribute & EFI_FILE_DIRECTORY) {
            EFI_FILE_PROTOCOL *child;
            dir->Open(dir, &child, finfo.FileName, EFI_FILE_MODE_READ, NULL);
            dfs(child, depth+1);
            child->Close(child);
        }
    }
    return 0;
}


EFI_STATUS EFIAPI EfiMain (
        IN EFI_HANDLE ImageHandle,
        IN EFI_SYSTEM_TABLE *SystemTable
        )
{
    gST = SystemTable;
    gBS = gST->BootServices;

    gST->ConOut->OutputString(gST->ConOut, L"Hello.\r\n\r\n");
    EFI_GUID simpl_fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

    EFI_HANDLE *handles;
    UINTN no_handles;
    gBS->LocateHandleBuffer(ByProtocol, &simpl_fs_guid, NULL, &no_handles, &handles);

    for(int i=0; i<no_handles; i++) {
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simpl_fs_proto;
        gBS->OpenProtocol(handles[i], &simpl_fs_guid, (VOID**)&simpl_fs_proto, ImageHandle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);

        if(!simpl_fs_proto) {
            gST->ConOut->OutputString(gST->ConOut, L"EFI_SIMPLE_FILE_SYSTEM_PROTOCOL not found.\r\n\r\n");
            continue;
        }

        EFI_FILE_PROTOCOL *root;
        simpl_fs_proto->OpenVolume(simpl_fs_proto, &root);

        if(!root) {
            gST->ConOut->OutputString(gST->ConOut, L"Couldn't OpenVolume.\r\n\r\n");
            continue;
        }

        gST->ConOut->OutputString(gST->ConOut, L"/\r\n");
        dfs(root, 1);
        gST->ConOut->OutputString(gST->ConOut, L"\r\n");
        root->Close(root);
        gBS->CloseProtocol(handles[i], &simpl_fs_guid, ImageHandle, NULL);
    }
    gBS->FreePool(handles);

    while(1);
    return EFI_SUCCESS;
}
