{$mode fpc}
unit kernel_main;

interface

procedure kernel_start;

implementation

uses efilib;

procedure efi_main(ImageHandle: TEfiHandle; SystemTable: PEfiSystemTable); cdecl; [public, alias: 'efi_main'];
begin
	InitializeLib(ImageHandle, SystemTable);
	kernel_start;
end;

procedure kernel_start;
begin
	Print('Test %s'#13#10, PWideChar('test'));
end;

end.
