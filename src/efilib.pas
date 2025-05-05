{$mode fpc}
unit efilib;

{ Bindings for UEFI data structures and functions.
  Built with the UEFI Specifcation Version 2.6.

  Copyright (c) 2025, Marie Eckert
  Licensed under the BSD 3-Clause License, see:
    https://github.com/MarieEckert/fpc-efi-test
}

interface

{$include efitypes.inc}
{$include eficonstants.inc}

{$ifdef HAVE_GNUEFI_EFILIB_BINDINGS}
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
{$endif}

implementation

end.
