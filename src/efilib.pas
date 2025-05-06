{$mode fpc}
unit efilib;

{ Bindings for UEFI data structures and functions.
  Built with the UEFI Specifcation Version 2.6.
}

{ Copyright (c) 2025, Marie Eckert

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

type
	TEfiLibError		= (eleOK, eleNoSystemTable, eleEfiCallFailure);
	TEfiLibErrorDetail	= UInt64;

	TMemoryPoolResult = record
		Status	: TEfiLibError;
		Detail	: TEfiLibErrorDetail;
		Pool	: TMemoryPool;
	end;

procedure Print(constref msg: PWideChar);

procedure PrintErrorStr(err: TEfiLibError);

procedure PrintHex(_int: UInt64);

procedure PrintError(constref msg: PWideChar; err: TEfiLibError; detail: UInt64);

function AllocateMemoryPool(const PoolSize: TUINTN): TMemoryPoolResult;

var
	SystemTable	: PEfiSystemTable	= Nil;
	ImageHandle	: TEfiHandle		= Nil;

implementation

procedure Print(constref msg: PWideChar);
begin
	SystemTable^.ConOut^.OutputString(SystemTable^.ConOut, msg);
end;

procedure PrintErrorStr(err: TEfiLibError);
begin
	case err of
	eleOK: Print('eleOK');
	eleNoSystemTable: Print('eleNoSystemTable');
	eleEfiCallFailure: Print('eleEfiCallFailure');
	else Print('unknownError');
	end;
end;

procedure PrintHex(_int: UInt64);
const
	MAX_DIGITS = 32;
	DIGITS: array of WideChar = ('0','1','2','3','4','5','6','7','8','9','A','B','C',
								 'D','E','F');
var
	wix, ix: Integer;
	b: UInt8;
	c: array [0..1] of WideChar;
	_str: array [0..MAX_DIGITS] of WideChar;
begin
	c[0] := '$';
	c[1] := WideChar($0000);

	Print(@c[0]);

	wix := High(_str);
	_str[wix] := WideChar($0000);
	Dec(wix);

	ix := 0;

	repeat
		_str[wix] := DIGITS[_int mod 16];
		_int := _int div 16;
		Inc(ix);
		Dec(wix);
	until (_int = 0) or (ix >= MAX_DIGITS);

	Print(PWideChar(_str) + wix);
end;

procedure PrintError(constref msg: PWideChar; err: TEfiLibError; detail: UInt64);
begin
	Print(msg);
	PrintErrorStr(err);
	Print(' ');
	PrintHex(detail);
	Print(''#13#10);
end;

function AllocateMemoryPool(const PoolSize: TUINTN): TMemoryPoolResult;
var
	pool: TMemoryPool;
begin
	if SystemTable = Nil then
	begin
		AllocateMemoryPool.Status := eleNoSystemTable;
		exit;
	end;

	AllocateMemoryPool.Detail :=
		SystemTable^.BootServices^.AllocatePool(
			EfiLoaderData,
			PoolSize,
			@pool.Buffer
		);

	if AllocateMemoryPool.Detail <> EFI_SUCCESS then
	begin
		AllocateMemoryPool.Status := eleEfiCallFailure;
		exit;
	end;

	pool.Size := PoolSize;
	AllocateMemoryPool.Pool := pool;
	AllocateMemoryPool.Status := eleOK;
end;

end.
