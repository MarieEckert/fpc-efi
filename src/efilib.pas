{$mode fpc}
unit efilib;

{ incomplete bindings to gnu-efi's efilib.h }

interface

{$include efitypes.inc}
{$include eficonstants.inc}

procedure InitializeLib(ImageHandle: TEfiHandle;
						EfiSystemTable: PEfiSystemTable);
	cdecl; external 'c' name 'InitializeLib';

procedure InitializeUnicodeSupport(LangCode: PChar8);
	cdecl; external 'c' name 'InitializeUnicodeSupport';

procedure EFIDebugVariable;
	cdecl; external 'c' name 'EFIDebugVariable';

procedure EfiExit(ExitStatus: TEfiStatus; ExitDataSize: TUINTN;
				  ExitData: PChar16);
	cdecl; external 'c' name 'Exit';

procedure Print(fmt: PChar16);
	cdecl; varargs; external 'c' name 'Print';

implementation

end.
