{$mode fpc}
unit kernel_main;

interface

implementation

uses efilib;

function efi_main(ImageHandle: TEfiHandle; SystemTable: PEfiSystemTable):
	TEfiStatus; cdecl; [public, alias: 'efi_main'];
begin
	InitializeLib(ImageHandle, SystemTable);
	Print('Test %s'#13#10, PWideChar('test'));
	exit(EFI_SUCCESS);
end;

end.
