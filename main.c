#include <efi.h>
#include <efilib.h>

void kernel_start(void);

EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  InitializeLib(ImageHandle, SystemTable);
  Print(L"Hello, world!\n");
  kernel_start();
  return EFI_SUCCESS;
}
