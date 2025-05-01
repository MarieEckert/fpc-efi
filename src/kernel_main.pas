{$mode fpc}
unit kernel_main;

interface

implementation

uses efilib;

procedure efi_main(ImageHandle: TEfiHandle; SystemTable: PEfiSystemTable);
	cdecl; [public, alias: 'efi_main'];
begin
	InitializeLib(ImageHandle, SystemTable);
	Print('Test %s'#13#10, PWideChar('test'));
end;

end.
