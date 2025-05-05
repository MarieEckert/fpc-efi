{$mode fpc}
unit elf;

{ elf helper functions, like _locate }

interface

uses
	efilib;

type
	TElf64XWord		= UInt64;
	TElf64SXWord	= Int64;
	TElf64Addr		= UInt64;

{$packrecords c}
	TElf64Dyn = packed record
		d_tag	: TElf64SXWord;
		case Byte of
			0: (d_val	: TElf64XWord);
			1: (d_ptr	: TElf64Addr);
	end;

	TElf64Rel = packed record
		r_offset	: TElf64Addr;
		r_info		: TElf64XWord;
	end;
{$pakcrecords default}

	PElf64Dyn = ^TElf64Dyn;
	PElf64Rel = ^TElf64Rel;

const
	DT_NULL				= 0;
	DT_NEEDED			= 1;
	DT_PLTRELSZ			= 2;
	DT_PLTGOT			= 3;
	DT_HASH				= 4;
	DT_STRTAB			= 5;
	DT_SYMTAB			= 6;
	DT_RELA				= 7;
	DT_RELASZ			= 8;
	DT_RELAENT			= 9;
	DT_STRSZ			= 10;
	DT_SYMENT			= 11;
	DT_INIT				= 12;
	DT_FINI				= 13;
	DT_SONAME			= 14;
	DT_RPATH			= 15;
	DT_SYMBOLIC			= 16;
	DT_REL				= 17;
	DT_RELSZ			= 18;
	DT_RELENT			= 19;
	DT_PTRREL			= 20;
	DT_DEBUG			= 21;
	DT_TEXTREL			= 22;
	DT_JMPREL			= 23;
	DT_BIND_NOW			= 24;
	DT_INIT_ARRAY		= 25;
	DT_FINI_ARRAY		= 26;
	DT_INIT_ARRAYSZ		= 27;
	DT_FINI_ARRAYSZ		= 28;
	DT_RUNPATH			= 29;
	DT_FLAGS			= 30;
	DT_ENCODING			= 32;
	DT_PREINIT_ARRAY	= 32;
	DT_PREINIT_ARRAYSZ	= 33;
	DT_NUM				= 34;
	DT_LOOS				= $6000000d;
	DT_HIOS				= $6ffff000;
	DT_LOPROC			= $70000000;
	DT_HIPROC			= $7fffffff;

	R_X86_64_NONE		= 0;
	R_X86_64_64			= 1;
	R_X86_64_PC32		= 2;
	R_X86_64_GOT32		= 3;
	R_X86_64_PLT32		= 4;
	R_X86_64_COPY		= 5;
	R_X86_64_GLOB_DAT	= 6;
	R_X86_64_JUMP_SLOT	= 7;
	R_X86_64_RELATIVE	= 8;
	R_X86_64_GOTPCREL	= 9;
	R_X86_64_32			= 10;
	R_X86_64_32S		= 11;
	R_X86_64_16			= 12;
	R_X86_64_PC16		= 13;
	R_X86_64_8			= 14;
	R_X86_64_PC8		= 15;
	R_X86_64_DTPMOD64	= 16;
	R_X86_64_DTPOFF64	= 17;
	R_X86_64_TPOFF64	= 18;
	R_X86_64_TLSGD		= 19;
	R_X86_64_TLSLD		= 20;
	R_X86_64_DTPOFF32	= 21;
	R_X86_64_GOTTPOFF	= 22;
	R_X86_64_TPOFF32	= 23;
	R_X86_64_NUM		= 24;
implementation

end.
