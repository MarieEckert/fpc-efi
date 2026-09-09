{$mode fpc}
unit efilib;

{$scopedenums on}
{$writeableconst off}
{$typedaddress on}

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
	TEfiLibMemoryMap = record
		Size				: TUINTN;
		Map					: PEfiMemoryDescriptor;
		Key					: TUINTN;
		DescriptorSize		: TUINTN;
		DescriptorVersion	: UInt32;
	end;

	{ Result / Return Types }
	TEfiLibError		= (OK,
						   NoSystemTable,
						   EfiCallFailure,
						   NilValue);
	TEfiLibErrorDetail	= UInt64;

	TMemoryPoolResult = record
		Status	: TEfiLibError;
		Detail	: TEfiLibErrorDetail;
		Pool	: TMemoryPool;
	end;

	TVolumeResult = record
		Status	: TEfiLibError;
		Detail	: TEfiLibErrorDetail;
		Point	: UInt64; { debug! remove? }
		Volume	: PEfiFileProtocol;
	end;

	TFileInfoResult = record
		Status		: TEfiLibError;
		Detail		: TEfiLibErrorDetail;
		FileInfo	: PEfiFileInfo;
	end;

	TLoadFileResult = record
		Status		: TEfiLibError;
		Detail		: TEfiLibErrorDetail;
		Msg			: PWideChar;

		Handle		: PEfiFileHandle;
		Buffer		: TMemoryPool;
	end;

	TMemoryMapResult = record
		Status		: TEfiLibError;
		Detail		: TEfiLibErrorDetail;
		MemoryMap	: TEfiLibMemoryMap;
	end;

	TGOPResult = record
		Status		: TEfiLibError;
		Detail		: TEfiLibErrorDetail;
		GOP			: PEfiGraphicsOutputProtocol;
	end;

{ Printing Functions }

procedure Print(constref msg: PWideChar);

procedure PrintErrorStr(err: TEfiLibError);

procedure PrintHex(_int: UInt64);

procedure PrintError(
	constref msg: PWideChar;
	err: TEfiLibError; detail: UInt64
);

{ Memory }

function AllocPool(const PoolSize: TUINTN): TMemoryPoolResult;

procedure FreePool(var Pool: TMemoryPool);

function GetMemoryMap: TMemoryMapResult;

{ File I/O Utilities }

function GetVolume(Image: TEfiHandle): TVolumeResult;

function GetFileInfo(
	FHnd: PEfiFileHandle
): TFileInfoResult;

function LoadFile(
	const Path: PWideChar;
	const Volume: PEfiFileProtocol
): TLoadFileResult;

{ function FileInfoGetName(const Info: PEfiFileInfo): PChar16; }

{ GOP }

function GetGOP: TGOPResult;

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
	TEfiLibError.OK: Print('OK');
	TEfiLibError.NoSystemTable: Print('NoSystemTable');
	TEfiLibError.EfiCallFailure: Print('EfiCallFailure');
	TEfiLibError.NilValue: Print('NilValue');
	else Print('unknownError');
	end;
end;

procedure PrintHex(_int: UInt64);
const
	MAX_DIGITS = 32;
	DIGITS: array of WideChar = ('0','1','2','3','4','5','6','7',
								 '8','9','A','B','C','D','E','F');
var
	wix, ix: Integer;
	c: array [0..1] of WideChar;
	_str: array [0..MAX_DIGITS] of WideChar;
begin
	c[0] := '$';
	c[1] := WideChar($0000);

	Print(@c[0]);

	wix := High(_str);
	_str[wix] := WideChar($0000);
	Dec(wix);

	for ix := wix downto 0 do _str[ix] := '0';

	ix := 0;

	repeat
		_str[wix] := DIGITS[_int mod 16];
		_int := _int div 16;
		Inc(ix);
		Dec(wix);
	until (_int = 0) or (ix >= MAX_DIGITS);

	Print(PWideChar(_str) + wix);
end;

procedure PrintError(
	constref msg: PWideChar;
	err: TEfiLibError; detail: UInt64
);
begin
	Print(msg);
	PrintErrorStr(err);
	Print(' ');
	PrintHex(detail);
	Print(''#13#10);
end;

function AllocPool(const PoolSize: TUINTN): TMemoryPoolResult;
var
	pool: TMemoryPool;
begin
	if SystemTable = Nil then
	begin
		AllocPool.Status := TEfiLibError.NoSystemTable;
		exit;
	end;

	AllocPool.Detail :=
		SystemTable^.BootServices^.AllocatePool(
			TEfiMemoryType.EfiLoaderData,
			PoolSize + 4096,
			@pool.Buffer
		);

	if AllocPool.Detail <> EFI_SUCCESS then
	begin
		AllocPool.Status := TEfiLibError.EfiCallFailure;
		exit;
	end;

	pool.Buffer += 4096 - (UInt64(pool.Buffer) mod 4096);

	pool.Size := PoolSize;
	AllocPool.Pool := pool;
	AllocPool.Status := TEfiLibError.OK;
end;

procedure FreePool(var Pool: TMemoryPool);
begin
	if Pool.Buffer = Nil then exit;
	SystemTable^.BootServices^.FreePool(Pool.Buffer);
end;

function GetMemoryMap: TMemoryMapResult;
var
	memoryMap	: TEfiLibMemoryMap = (
		Size: 0; Map: Nil; Key: 0; DescriptorSize: 0; DescriptorVersion: 0
	);
	allocResult	: TMemoryPoolResult;
begin
	GetMemoryMap.Detail := SystemTable^.BootServices^.GetMemoryMap(
		@memoryMap.Size,
		 memoryMap.Map,
		@memoryMap.Key,
		@memoryMap.DescriptorSize,
		@memoryMap.DescriptorVersion
	);

	if GetMemoryMap.Detail <> EFI_BUFFER_TOO_SMALL then
	begin
		GetMemoryMap.Status := TEfiLibError.EfiCallFailure;
		exit;
	end;

	memoryMap.Size += memoryMap.DescriptorSize * 2;
	allocResult := AllocPool(memoryMap.Size);

	if allocResult.Status <> TEfiLibError.OK then
	begin
		GetMemoryMap.Status := allocResult.Status;
		GetMemoryMap.Detail := allocResult.Detail;
		exit;
	end;

	memoryMap.Map := allocResult.Pool.Buffer;

	GetMemoryMap.Detail := SystemTable^.BootServices^.GetMemoryMap(
		@memoryMap.Size,
		 memoryMap.Map,
		@memoryMap.Key,
		@memoryMap.DescriptorSize,
		@memoryMap.DescriptorVersion
	);

	if GetMemoryMap.Detail <> EFI_SUCCESS then
	begin
		GetMemoryMap.Status := TEfiLibError.EfiCallFailure;
		FreePool(allocResult.Pool);
		exit;
	end;

	GetMemoryMap.Status := TEfiLibError.OK;
	GetMemoryMap.MemoryMap := memoryMap;
end;

function GetVolume(image: TEfiHandle): TVolumeResult;
var
	loadedImage	: PEfiLoadedImageProtocol;
	lipGuid		: TEfiGuid;
	ioVolume	: PEfiSimpleFileSystemProtocol;
	fsGuid		: TEfiGuid;
	volume		: PEfiFileProtocol;
begin
	loadedImage := Nil;
	lipGuid := EFI_LOADED_IMAGE_PROTOCOL_GUID;
	fsGuid := EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

	GetVolume.Detail := SystemTable^.BootServices^.LocateProtocol(
		PEfiGuid(@lipGuid[0]),
		Nil,
		PPointer(@loadedImage)
	);

	if GetVolume.Detail <> EFI_SUCCESS then
	begin
		GetVolume.Status := TEfiLibError.EfiCallFailure;
		GetVolume.Point := 0;
		exit;
	end;

	GetVolume.Detail := SystemTable^.BootServices^.HandleProtocol(
		image,
		PEfiGuid(@lipGuid[0]),
		PPointer(@loadedImage)
	);

	if GetVolume.Detail <> EFI_SUCCESS then
	begin
		GetVolume.Status := TEfiLibError.EfiCallFailure;
		GetVolume.Point := 1;
		exit;
	end;

	GetVolume.Detail := SystemTable^.BootServices^.HandleProtocol(
		loadedImage^.DeviceHandle,
		PefiGuid(@fsGuid[0]),
		PPointer(@ioVolume)
	);

	if GetVolume.Detail <> EFI_SUCCESS then
	begin
		GetVolume.Status := TEfiLibError.EfiCallFailure;
		GetVolume.Point := 2;
		exit;
	end;

	GetVolume.Detail := ioVolume^.OpenVolume(
		ioVolume,
		@volume
	);

	if GetVolume.Detail <> EFI_SUCCESS then
	begin
		GetVolume.Status := TEfiLibError.EfiCallFailure;
		GetVolume.Point := 3;
		exit;
	end;

	GetVolume.Status := TEfiLibError.OK;
	GetVolume.Volume := volume;
end;

function GetFileInfo(
			FHnd: PEfiFileHandle
		): TFileInfoResult;
var
	poolRes	: TMemoryPoolResult;
	status	: TEfiStatus;
begin
	poolRes := AllocPool(sizeof(TEfiFileInfo) + 128);
	if poolRes.Status <> TEfiLibError.OK then
	begin
		GetFileInfo.Status := poolRes.Status;
		GetFileInfo.Detail := poolRes.Detail;
		exit;
	end;

	GetFileInfo.Status := TEfiLibError.OK;
	GetFileInfo.FileInfo := poolRes.Pool.Buffer;

	while True do
	begin
		status := FHnd^.GetInfo(
			FHnd,
			@EFI_FILE_INFO_GUID,
			@poolRes.Pool.Size,
			GetFileInfo.FileInfo
		);

		if status = EFI_SUCCESS then
			break;

		if status <> EFI_BUFFER_TOO_SMALL then
		begin
			FreePool(poolRes.pool);
			GetFileInfo.Status := TEfiLibError.EfiCallFailure;
			GetFileInfo.Detail := status;
			exit;
		end;

		FreePool(poolRes.pool);

		poolRes := AllocPool(poolRes.Pool.Size + 64);
		if poolRes.Status <> TEfiLibError.OK then
		begin
			GetFileInfo.Status := poolRes.Status;
			GetFileInfo.Detail := poolRes.Detail;
			exit;
		end;
	end;
end;

function LoadFile(
	const Path: PWideChar;
	const Volume: PEfiFileProtocol
): TLoadFileResult;
var
	finfResult	: TFileInfoResult;
	allocResult	: TMemoryPoolResult;
begin
	LoadFile.Detail := Volume^.Open(
		Volume,
		@LoadFile.Handle,
		Path,
		EFI_FILE_MODE_READ,
		EFI_FILE_READ_ONLY or EFI_FILE_HIDDEN or EFI_FILE_SYSTEM
	);
	if LoadFile.Detail <> EFI_SUCCESS then
	begin
		LoadFile.Status := TEfiLibError.EfiCallFailure;
		LoadFile.Msg := 'Volume^.Open failed: ';
		exit;
	end;

	finfResult := efilib.GetFileInfo(LoadFile.Handle);
	if finfResult.Status <> TEfiLibError.Ok then
	begin
		LoadFile.Status := finfResult.Status;
		LoadFile.Detail := finfResult.Detail;
		LoadFile.Msg := 'GetFileInfo failed: ';
		LoadFile.Handle^.Close(LoadFile.Handle);
		exit;
	end;

	allocResult := efilib.AllocPool(finfResult.FileInfo^.FileSize);
	if allocResult.Status <> TEfiLibError.Ok then
	begin
		LoadFile.Status := allocResult.Status;
		LoadFile.Detail := allocResult.Detail;
		LoadFile.Msg := 'AllocPool failed: ';
		LoadFile.Handle^.Close(LoadFile.Handle);
	end;

	LoadFile.Buffer := allocResult.Pool;

	LoadFile.Detail := LoadFile.Handle^.Read(
		LoadFile.Handle,
		@LoadFile.Buffer.Size,
		LoadFile.Buffer.Buffer
	);
	if LoadFile.Detail <> EFI_SUCCESS then
	begin
		LoadFile.Status := TEfiLibError.EfiCallFailure;
		LoadFile.Msg := 'Handle^.Read failed: ';
		LoadFile.Handle^.Close(LoadFile.Handle);
	end;

	LoadFile.Status := TEfiLibError.Ok;
	LoadFile.Msg := 'Ok';
end;

function GetGOP: TGOPResult;
begin
	GetGOP.Status := TEfiLibError.OK;
	GetGOP.Detail := SystemTable^.BootServices^.LocateProtocol(
		@EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID,
		Nil,
		PPointer(@GetGOP.GOP)
	);

	if GetGOP.Detail <> EFI_SUCCESS then
	begin
		GetGOP.Status := TEfiLibError.EfiCallFailure;
		exit;
	end;
end;

end.
