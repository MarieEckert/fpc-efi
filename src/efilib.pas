{$mode fpc}
unit efilib;

{ incomplete bindings to gnu-efi's efilib.h }

{$packrecords c}

interface

type
	TBoolean		= Byte;
	TINTN			= Int64;
	TUINTN			= UInt64;
	TEFIGuid		= array [0..15] of Byte;
	TEfiStatus		= TUINTN;
	TEfiHandle		= Pointer;
	TEfiEvent		= Pointer;
	TEfiLba			= UInt64;
	TEfiTpl			= TUINTN;
	TEfiMacAddress	= array [0..31] of Byte;
	TEfiIPv4Address	= array [0..3] of Byte;
	TEfiIPv6Address	= array [0..15] of Byte;
	TEfiIPAddress	= TEfiIPv6Address;
	PEfiSystemTable	= Pointer;
	PChar8			= PChar;
	PChar16			= PWideChar;

procedure InitializeLib(ImageHandle: TEfiHandle; EfiSystemTable: PEfiSystemTable); cdecl; external 'c' name 'InitializeLib';

procedure InitializeUnicodeSupport(LangCode: PChar8); cdecl; external 'c' name 'InitializeUnicodeSupport';

procedure EFIDebugVariable; cdecl; external 'c' name 'EFIDebugVariable';

procedure Exit(ExitStatus: TEfiStatus; ExitDataSize: TUINTN; ExitData: PChar16); cdecl; external 'c' name 'Exit';

procedure Print(fmt: PChar16); cdecl; varargs; external 'c' name 'Print';

implementation

end.
