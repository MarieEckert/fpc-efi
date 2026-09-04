{$mode fpc}
unit kernel_main;

interface

implementation

uses elf_relocate, efilib;

function _entry(ImageHandle: TEfiHandle; SystemTable: PEfiSystemTable):
	TEfiStatus; cdecl; [public, alias: '_entry'];
var
	allocResult: TMemoryPoolResult;
begin
	efilib.ImageHandle := ImageHandle;
	efilib.SystemTable := SystemTable;
	allocResult := efilib.AllocateMemoryPool(1024*1024*1024*1024);
	if allocResult.Status <> eleOK then
	begin
		efilib.PrintError('[E] AllocateMemoryPool failed: ', allocResult.Status, allocResult.Detail);
		exit;
	end;
	SystemTable^.BootServices^.Stall(5 * 1000 * 1000);
	exit(EFI_SUCCESS);
end;

end.
