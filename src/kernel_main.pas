{$mode fpc}
unit kernel_main;

interface

implementation

uses elf, efilib;

{ position independent x86_64 elf so relocator.
  This is a more or less direct port of the gnuefi elf relocator (reloc_x86_64.c) and
  designed to be compatible with the gnuefi crt0-efi-x86_64.S entry point.
}
function _relocate(
			ldbase: Int64;
			dyn: PElf64Dyn;
			image: TEFIHandle;
			systab: PEfiSystemTable
		): TEfiStatus; cdecl; [public, alias: '_relocate'];
var
	i				: Integer;
	rel				: PElf64Rel;
	addr			: PUInt64;
	relsz, relent	: Int64;
begin
	relsz := 0;
	relent := 0;
	rel := Nil;

	while dyn^.d_tag <> DT_NULL do
	begin
		case dyn^.d_tag of
		DT_RELA: rel := PElf64Rel(UInt64(dyn^.d_ptr) + ldbase);
		DT_RELASZ: relsz := dyn^.d_val;
		DT_RELAENT: relent := dyn^.d_val;
		end;
		inc(dyn);
	end;

	if (rel = Nil) and (relent = 0) then
		exit(EFI_SUCCESS);

	if (rel = Nil) or (relent = 0) then
		exit(EFI_LOAD_ERROR);

	{ Apply the relocations }
	while relsz > 0 do
	begin
		case rel^.r_info and $ffffffff of
		R_X86_64_RELATIVE: begin
			addr := PUInt64(ldbase + rel^.r_offset);
			addr^ := addr^ + ldbase;
		end;
		end;

		rel := PElf64Rel(PChar(rel) + relent);
		relsz := relsz - relent;
	end;

	exit(EFI_SUCCESS);
end;

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
