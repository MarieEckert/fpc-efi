// vim: set filetype=pascal :

{ type definitions for interfacing with EFI.
  you probably shouldn't include this file directly, you should use the efilib
  unit.

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

{$ifndef EFILIB_EFITYPES_INC}
{$define EFILIB_EFITYPES_INC}

type
	{ Basic Types [Table 6] }
	TBoolean			= Byte;
	TINTN				= Int64;
	TUINTN				= UInt64;
	TEfiGuid			= array [0..15] of Byte;
	TEfiStatus			= TUINTN;
	TEfiHandle			= Pointer;
	TEfiEvent			= Pointer;
	TEfiLba				= UInt64;
	TEfiTpl				= TUINTN;
	TEfiMacAddress		= array [0..31] of Byte;
	TEfiIPv4Address		= array [0..3] of Byte;
	TEfiIPv6Address		= array [0..15] of Byte;
	TEfiIPAddress		= TEfiIPv6Address;
	TEfiPhysicalAddress	= UInt64;
	TEfiVirtualAddress	= UInt64;
	PEfiHandle			= ^TEfiHandle;
	PEfiGuid			= ^TEfiGuid;
	PEfiEvent			= ^TEfiEvent;
	PBoolean			= ^TBoolean;
	PChar8				= PChar;
	PChar16				= PWideChar;
	PINTN				= ^TINTN;
	PUINTN				= ^TUINTN;
	PPointer			= ^Pointer;
	PPChar8				= ^PChar8;
	PPChar16			= ^PChar16;
	PPEfiHandle			= ^PEfiHandle;
	PPEfiGuid			= ^PEfiGuid;
	PPPEfiGuid			= ^PPEfiGuid;

	{ Enumations }
	TEfiResetType		= (EfiResetCold,
						   EfiResetWarm,
						   EfiResetShutdown);
	TEfiAllocateType	= (AllocateAnyPages,
						   AllocateMaxAddress,
						   AllocateAddress,
						   MaxAllocateType);
	TEfiMemoryType		= (EfiReservedMemoryType,
						   EfiLoaderCode,
						   EfiLoaderData,
						   EfiBootServicesCode,
						   EfiBootServicesData,
						   EfiRuntimeServicesCode,
						   EfiRuntimeServicesData,
						   EfiConventionalMemory,
						   EfiUnusableMemory,
						   EfiACPIReclaimMemory,
						   EfiACPIMemoryNVS,
						   EfiMemoryMappedIO,
						   EfiMemoryMappedIOPortSpace,
						   EfiPalCode,
						   EfiPersistentMemory,
						   EfiMaxMemoryType);
	TEfiInterfaceType	= (EfiNativeInterface);
	TEfiLocateSearchType= (AllHandles,
						   ByRegisterNotify,
						   ByProtocol);
	TEfiTimerDelay		= (TimerCancel,
						   TimerPeriodic,
						   TiemrRelative);
	TEfiGraphicsPixelFormat =
						  (PixelRedGreenBlueReserved8BitPerColor,
						   PixelBlueGreenRedReserved8BitPerColor,
						   PixelBitMask,
						   PixelBltOnly,
						   PixelFormatMax);
	TEfiGraphicsOutputBltOperation =
						  (EfiBltVideoFill,
						   EfiBltVideoToBltBuffer,
						   EfiBltBufferToVideo,
						   EfiBltVideoToVideo,
						   EfiGraphicsOutputBltOperationMax);

{$packrecords c}

	PEfiSimpleTextInputProtocol			= ^TEfiSimpleTextInputProtocol;
	PEfiInputKey						= ^TEfiInputKey;
	PEfiSimpleTextOutputProtocol		= ^TEfiSimpleTextOutputProtocol;
	PEfiTime							= ^TEfiTime;
	PEfiTimeCapabilities				= ^TEfiTimeCapabilities;
	PEfiMemoryDescriptor				= ^TEfiMemoryDescriptor;
	PEfiCapsuleHeader					= ^TEfiCapsuleHeader;
	PPEfiCapsuleHeader					= ^PEfiCapsuleHeader;
	PEfiPhysicalAddress					= ^TEfiPhysicalAddress;
	PEfiDevicePathProtocol				= ^TEfiDevicePathProtocol;
	PPEfiDevicePathProtocol				= ^PEfiDevicePathProtocol;
	PEfiOpenProtocolInformationEntry	= ^TEfiOpenProtocolInformationEntry;
	PPEfiOpenProtocolInformationEntry	= ^PEfiOpenProtocolInformationEntry;
	PEfiResetType						= ^TEfiResetType;
	PEfiFileProtocol					= ^TEfiFileProtocol;
	PEfiSimpleFileSystemProtocol		= ^TEfiSimpleFileSystemProtocol;
	PEfiFileHandle						= PEfiFileProtocol;
	PPEfiFileProtocol					= ^PEfiFileProtocol;
	PEfiFileInfo						= ^TEfiFileInfo;
	PEfiDevicePath						= ^TEfiDevicePath;
	PEfiLoadedImageProtocol				= ^TEfiLoadedImageProtocol;
	PEfiGraphicsOutputBltPixel			= ^TEfiGraphicsOutputBltPixel;
	PEfiGraphicsOutputModeInformation	= ^TEfiGraphicsOutputModeInformation;
	PPEfiGraphicsOutputModeInformation	= ^PEfiGraphicsOutputModeInformation;
	PEfiGraphicsOutputProtocolMode		= ^TEfiGraphicsOutputProtocolMode;
	PEfiGraphicsOutputProtocol			= ^TEfiGraphicsOutputProtocol;
	PEfiRuntimeServices					= ^TEfiRuntimeServices;
	PEfiConfigurationTable				= ^TEfiConfigurationTable;
	PEfiBootServices					= ^TEfiBootServices;
	PEfiSystemTable						= ^TEfiSystemTable;

	{ procedural types }

	TEfiInputReset =
		function(
			This: PEfiSimpleTextInputProtocol;
			ExtendedVerification: TBoolean
		): TEfiStatus; MS_ABI_CDecl;

	TEfiInputReadKey =
		function(
			This: PEfiSimpleTextInputProtocol;
			Key: PEfiInputKey
		): TEfiStatus; MS_ABI_CDecl;

	TEfiTextReset = TEfiInputReset;

	TEfiTextString =
		function(
			This: PEfiSimpleTextOutputProtocol;
			_String: PChar16
		): TEfiStatus; MS_ABI_CDecl;

	TEfiTextTestString = TEfiTextString;

	TEfiTextQueryMode =
		function(
			This: PEfiSimpleTextOutputProtocol;
			ModeNumber: TUINTN;
			Columns: PUINTN;
			Rows: PUINTN):
		TEfiStatus; MS_ABI_CDecl;

	TEfiTextSetMode =
		function(
			This: PEfiSimpleTextOutputProtocol;
			ModeNumber: TUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiTextSetAttribute =
		function(
			This: PEfiSimpleTextOutputProtocol;
			Attribute: TUINTN):
		TEfiStatus; MS_ABI_CDecl;

	TEfiTextClearScreen =
		function(
			This: PEfiSimpleTextOutputProtocol
		): TEfiStatus; MS_ABI_CDecl;

	TEfiTextSetCursorPosition =
		function(
			This: PEfiSimpleTextOutputProtocol;
			Column: TUINTN;
			Row: TUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiTextEnableCursor =
		function(
			This: PEfiSimpleTextOutputProtocol;
			Visible: Boolean
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetTime =
		function(
			Time: PEfiTime;
			Capabilities: PEfiTimeCapabilities
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSetTime =
		function(
			Time: PEfiTime
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetWakeupTime =
		function(
			Enabled: PBoolean;
			Pending: PBoolean;
			Time: PEfiTime
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSetWakeupTime =
		function(
			Enable: TBoolean;
			Time: PEfiTime
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSetVirtualAddressMap =
		function(
			MemoryMapSize: TUINTN;
			DescriptorSize: TUINTN;
			DescriptorVersion: UInt32;
			VirtualMap: PEfiMemoryDescriptor
		): TEfiStatus; MS_ABI_CDecl;

	TEfiConvertPointer =
		function(
			DebugDesposition: TUINTN;
			Address: PPointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetVariable =
		function(
			VariableName: PChar16;
			VendorGuid: PEfiGuid;
			Attributes: PUInt32;
			DataSize: PUINTN;
			Data: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetNextVariableName =
		function(
			VariableNameSize: PUINTN;
			VariableName: PChar16;
			VendorGuid: PEfiGuid
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSetVariable =
		function(
			VariableName: PChar16;
			VendorGuid: PEfiGuid;
			Attributes: UInt32;
			DataSize: TUINTN;
			Data: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetNextHighMonoCount =
		function(
			HighCount: PUInt32
		): TEfiStatus; MS_ABI_CDecl;

	TEfiResetSystem =
		function(
			ResetType: TEfiResetType;
			ResetStatus: TEfiStatus; DataSize: TUINTN;
			ResetData: PChar16
		): TEfiStatus; MS_ABI_CDecl;

	TEfiUpdateCapsule =
		function(
			CapsuleHeaderArray: PPEfiCapsuleHeader;
			CapsuleCount: TUINTN;
			ScatterGatherList: TEfiPhysicalAddress
		): TEfiStatus; MS_ABI_CDecl;

	TEfiQueryCapsuleCapabilities =
		function(
			CapsuleHeaderArray: PPEfiCapsuleHeader;
			CapsuleCount: TUINTN;
			MaximumCapsuleSize: PUInt64;
			ResetType: PEfiResetType
		): TEfiStatus; MS_ABI_CDecl;

	TEfiQueryVariableInfo =
		function(
			Attributes: UInt32;
			MaximumVariableStorageSize: PUInt64;
			RemainingVariableStorageSize: PUInt64;
			MaximumVariableSize: PUInt64
		): TEfiStatus; MS_ABI_CDecl;

	TEfiRaiseTPL =
		function(
			NewTpl: TEfiTPL
		): TEfiTPL; MS_ABI_CDecl;

	TEfiRestoreTPL =
		procedure(
			OldTpl: TEfiTPL
		); MS_ABI_CDecl;

	TEfiAllocatePages =
		function(
			_Type: TEfiAllocateType;
			MemoryType: TEfiMemoryType;
			Pages: TUINTN;
			Memory: PEfiPhysicalAddress
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFreePages =
		function(
			Memory: PEfiPhysicalAddress;
			Pages: TUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetMemoryMap =
		function(
			MemoryMapSize: PUINTN;
			MemoryMap: PEfiMemoryDescriptor;
			MapKey: PUINTN;
			DescriptorSize: PUINTN;
			DescriptorVersion: PUInt32
		): TEfiStatus; MS_ABI_CDecl;

	TEfiAllocatePool =
		function(
			PoolType: TEfiMemoryType;
			Size: TUINTN;
			Buffer: PPointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFreePool =
		function(
			Buffer: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiEventNotify =
		procedure(
			Event: TEfiEvent;
			Context: Pointer
		); MS_ABI_CDecl;

	TEfiCreateEvent =
		function(
			_Type: UInt32;
			NotifyTpl: TEfiTPL;
			NotifyFunction: TEfiEventNotify;
			Event: PEfiEvent
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSetTimer =
		function(
			Event: TEfiEvent;
			_Type: TEfiTimerDelay;
			TriggerTime: UInt64
		): TEfiStatus; MS_ABI_CDecl;

	TEfiWaitForEvent =
		function(
			NumberOfEvents: TUINTN;
			Event: PEfiEvent;
			Index: PUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSignalEvent =
		function(
			Event: TEfiEvent
		): TEfiStatus; MS_ABI_CDecl;

	TEfiCloseEvent =
		function(
			Event: TEfiEvent
		): TEfiStatus; MS_ABI_CDecl;

	TEfiCheckEvent =
		function(
			Event: TEfiEvent
		): TEfiStatus; MS_ABI_CDecl;

	TEfiInstallProtocolInterface =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			InterfaceType: TEfiInterfaceType;
			_Interface: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiReinstallProtocolInterface =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			OldInterface: Pointer;
			NewInterface: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiUninstallProtocolInterface =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			_Interface: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiHandleProtocol =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			_Interface: PPointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiRegisterProtocolNotify =
		function(
			Protocol: PEfiGuid;
			Event: TEfiEvent;
			Registration: PPointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiLocateHandle =
		function(
			SearchType: TEfiLocateSearchType;
			Protocol: PEfiGuid;
			SearchKey: Pointer;
			BufferSize: PUINTN;
			Buffer: PEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiLocateDevicePath =
		function(
			Protocol: PEfiGuid;
			DevicePath: PPEfiDevicePathProtocol;
			Device: PEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiInstallConfigurationTable =
		function(
			Guid: PEfiGuid;
			Table: Pointer
		): TEfistatus; MS_ABI_CDecl;

	TEfiImageLoad =
		function(
			BootPolicy: TBoolean;
			ParentImageHandle: TEfiHandle;
			DevicePath: PEfiDevicePathProtocol;
			SourceBuffer: Pointer;
			SourceSize: TUINTN;
			ImageHandle: PEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiImageStart =
		function(
			ImageHandle: TEfiHandle;
			ExitDataSize: PUINTN;
			ExitData: PPChar16
		): TEfiStatus; MS_ABI_CDecl;

	TEfiExit =
		function(
			ImageHandle: TEfiHandle;
			ExitStatus: TEfiStatus;
			ExitDataSize: TUINTN;
			ExitData: PChar16
		): TEfiStatus; MS_ABI_CDecl;

	TEfiImageUnload =
		function(
			ImageHandle: TEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiExitBootServices =
		function(
			ImageHandle: TEfiHandle;
			MapKey: TUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGetNextMonotonicCount =
		function(
			Count: PUInt64
		): TEfiStatus; MS_ABI_CDecl;

	TEfiStall =
		function(
			Microseconds: TUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiSetWatchdogTimer =
		function(
			Timeout: TUINTN;
			WatchdogCode: UInt64;
			DataSize: TUINTN;
			WatchdogData: PChar16
		): TEfiStatus; MS_ABI_CDecl;

	TEfiConnectController =
		function(
			ControllerHandle: TEfiHandle;
			DriverImageHandle: PEfiHandle;
			RemainingDevicePath: PEfiDevicePathProtocol;
			Recursive: TBoolean
		): TEfiStatus; MS_ABI_CDecl;

	TEfiDisconnectController =
		function(
			ControllerHandle:  TEfiHandle;
			DriverImageHandle: TEfiHandle;
			ChildHandle: TEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiOpenProtocol =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			_Interface: PPointer;
			AgentHandle: TEfiHandle;
			ControllerHandle: TEfiHandle;
			Attributes: UInt32
		): TEfiStatus; MS_ABI_CDecl;

	TEfiCloseProtocol =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			AgentHandle: TEfiHandle;
			ControllerHandle: TEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiOpenProtocolInformation =
		function(
			Handle: TEfiHandle;
			Protocol: PEfiGuid;
			EntryBuffer:
			PPEfiOpenProtocolInformationEntry;
			EntryCount: PUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiProtocolsPerHandle =
		function(
			Handle: TEfiHandle;
			ProtocolBuffer: PPPEfiGuid;
			ProtocolBufferCount: PUINTN
		): TEfiStatus; MS_ABI_CDecl;

	TEfiLocateHandleBuffer =
		function(
			SearchType: TEfiLocateSearchType;
			Protocol: PEfiGuid;
			SearchKey: Pointer;
			NoHandles: PUINTN;
			Buffer: PPEfiHandle
		): TEfiStatus; MS_ABI_CDecl;

	TEfiLocateProtocol =
		function(
			Protocol: PEfiGuid;
			Registration: Pointer;
			_Interface: PPointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiInstallMultipleProtocolInterfaces =
		function(
			Handle: PEfiHandle
		): TEfiStatus; MS_ABI_CDecl; varargs;

	TEfiUninstallMultipleProtocolInterfaces =
		function(
			Handle: TEfiHandle
		): TEfiStatus; MS_ABI_CDecl; varargs;

	TEfiCalculateCrc32 =
		function(
			Data: Pointer;
			DataSize: PUINTN;
			Crc32: PUInt32
		): TEfiStatus; MS_ABI_CDecl;

	TEfiCopyMem =
		procedure(
			Destination: Pointer;
			Source: Pointer;
			Length: TUINTN
		); MS_ABI_CDecl;

	TEfiSetMem =
		procedure(
			Buffer: Pointer;
			Size: TUINTN;
			Value: UInt8
		); MS_ABI_CDecl;

	TEfiCreateEventEx =
		function(
			_Type: UInt32;
			NotifyTpl: TEfiTPL;
			NotifyFunction: TEfiEventNotify;
			NotifyContext: Pointer;
			EventGroup: PEfiGuid;
			Event: PEfiEvent
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileOpen =
		function(
			This: PEfiFileProtocol;
			NewHandle: PPEfiFileProtocol;
			FileName: PChar16;
			OpenMode: UInt64;
			Attributes: UInt64
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileClose =
		function(
			This: PEfiFileProtocol
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileDelete =
		function(
			This: PEfiFileProtocol
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileRead =
		function(
			This: PEfiFileProtocol;
			BufferSize: PUINTN;
			Buffer: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileWrite =
		function(
			This: PEfiFileProtocol;
			BufferSize: PUINTN;
			Buffer: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileGetPosition =
		function(
			This: PEfiFileProtocol;
			Position: PUInt64
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileSetPosition =
		function(
			This: PEfiFileProtocol;
			Position: PUInt64
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileGetInfo =
		function(
			This: PEfiFileProtocol;
			InformationType: PEfiGuid;
			BufferSize: PUINTN;
			Buffer: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileSetInfo =
		function(
			This: PEfiFileProtocol;
			InformationType: PEfiGuid;
			BufferSize: TUINTN;
			Buffer: Pointer
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileFlush =
		function(
			This: PEfiFileProtocol
		): TEfiStatus; MS_ABI_CDecl;

	TEfiFileOpenEx	= Pointer;
	TEfiFileReadEx	= Pointer;
	TEfiFileWriteEx	= Pointer;
	TEfiFileFlushEx	= Pointer;

	TEfiSimpleFileSystemProtocolOpenVolume =
		function(
			This: PEfiSimpleFileSystemProtocol;
			Root: PPEfiFileProtocol
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGraphicsOutputProtocolQueryMode =
		function(
			This: PEfiGraphicsOutputProtocol;
			ModeNumber: UInt32;
			SizeOfInfo: PUINTN;
			Info: PPEfiGraphicsOutputModeInformation
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGraphicsOutputProtocolSetMode =
		function(
			This: PEfiGraphicsOutputProtocol;
			ModeNumber: UInt32
		): TEfiStatus; MS_ABI_CDecl;

	TEfiGraphicsOutputProtocolBlt =
		function(
			This: PEfiGraphicsOutputProtocol;
			BltBuffer: PEfiGraphicsOutputBltPixel;
			BltOperation: TEfiGraphicsOutputBltOperation;
			SourceX: TUINTN;
			SourceY: TUINTN;
			DestinationX: TUINTN;
			DestinationY: TUINTN;
			Width: TUINTN;
			Height: TUINTN;
			Delta: TUINTN
		): TEfiStatus; MS_ABI_CDecl;

	{ records }

	TEfiTableHeader = record
		Signature	: UInt64;
		Revision	: UInt32;
		HeaderSize	: UInt32;
		CRC32		: UInt32;
		Reserved	: UInt32;
	end;

	TEfiCapsuleHeader = record
		CapsuleGuid		 : TEfiGuid;
		HeaderSize		 : UInt32;
		Flags			 : UInt32;
		CapsuleImageSize : UInt32;
	end;

	TEfiConfigurationTable = record
		VendorGuid	: TEfiGuid;
		VendorTable	: Pointer;
	end;

	TEfiOpenProtocolInformationEntry = record
		AgentHandle		 : TEfiHandle;
		ControllerHandle : TEfiHandle;
		Attributes		 : UInt32;
		OpenCount		 : UInt32;
	end;

	TEfiDevicePathProtocol = record
		_Type	: UInt8;
		SubType	: UInt8;
		Length	: array [0..1] of UInt8;
	end;

	TEFIMemoryDescriptor = record
		_Type			: TEFIMemoryType;
		PhysicalStart	: TEFIPhysicalAddress;
		VirtualStart	: TEFIVirtualAddress;
		NumberOfPages	: UInt64;
		Attribute		: UInt64;
	end;

	TEfiTime = record
		Year		: UInt16; { 1900 – 9999 }
		Month		: UInt8;  { 1 – 12 }
		Day			: UInt8;  { 1 – 31 }
		Hour		: UInt8;  { 0 – 23 }
		Minute		: UInt8;  { 0 – 59 }
		Second		: UInt8;  { 0 – 59 }
		Pad1		: UInt8;
		Nanosecond	: UInt32; { 0 – 999,999,999 }
		TimeZone	: Int16;  { -1440 to 1440 or 2047 }
		Daylight	: UInt8;
		Pad2		: UInt8;
	end;

	TEfiTimeCapabilities = record
		Resolution	: UInt32;
		Accuracy	: UInt32;
		SetsToZero	: TBoolean;
	end;

	TEfiSimpleTextInputProtocol = record
		Reset			: TEfiInputReset;
		ReadKeyStroke	: TEfiInputReadKey;
		WaitForKey		: TEfiEvent;
	end;

	TEfiInputKey = record
		ScanCode	: UInt16;
		UnicodeChar	: Char16;
	end;

	TSimpleTextOutputMode = record
		MaxMode			: Int32;
		{ current settings }
		Mode			: Int32;
		Attribute		: Int32;
		CursorColumn	: Int32;
		CursorRow		: Int32;
		CursorVisible	: TBoolean;
	end;

	PSimpleTextOutputMode = ^TSimpleTextOutputMode;

	TEfiSimpleTextOutputProtocol = record
		Reset				: TEfiTextReset;
		OutputString		: TEfiTextString;
		TestString			: TEfiTextTestString;
		QueryMode			: TEfiTextQueryMode;
		SetMode				: TEfiTextSetMode;
		SetAttribute		: TEfiTextSetAttribute;
		ClearScreen			: TEfiTextClearScreen;
		SetCursorPosition	: TEfiTextSetCursorPosition;
		EnableCursor		: TEfiTextEnableCursor;
		Mode				: PSimpleTextOutputMode;
	end;

	TEfiSimpleFileSystemProtocol = record
		Revision	: UInt64;
		OpenVolume	: TEfiSimpleFileSystemProtocolOpenVolume;
	end;

	TEfiFileProtocol = record
		Revision	: UInt64;
		Open		: TEfiFileOpen;
		Close		: TEfiFileClose;
		Delete		: TEfiFileDelete;
		Read		: TEfiFileRead;
		Write		: TEfiFileWrite;
		GetPosition	: TEfiFileGetPosition;
		SetPosition	: TEfiFileSetPosition;
		GetInfo		: TEfiFileGetInfo;
		SetInfo		: TEfiFileSetInfo;
		Flush		: TEfiFileFlush;
		OpenEx		: TEfiFileOpenEx;
		ReadEx		: TEfiFileReadEx;
		WriteEx		: TEfiFileWriteEx;
		FlushEx		: TEfiFileFlushEx;
	end;

	TEfiFileInfo = record
		Size				: UInt64;
		FileSize			: UInt64;
		PhysicalSize		: UInt64;
		CreateTime			: TEfiTime;
		LastAccessTime		: TEfiTime;
		ModificationTime	: TEfiTime;
		Attribute			: UInt64;
		{ In C, there is a flexible CHAR16 array member here, you just have to
		  imagine that here :3 }
	end;

	TEfiDevicePath = record
		_Type	: UInt8;
		SubType	: UInt8;
		Length	: array [0..1] of UInt8;
	end;

	TEfiLoadedImageProtocol = record
		Revision			: UInt32;
		ParentHandle		: TEfiHandle;
		SystemTable			: PEfiSystemTable;
		DeviceHandle		: TEfiHandle;
		FilePath			: TEfiDevicePath;
		Reserved			: Pointer;
		LoadedOptionsSize	: UInt32;
		LoadOptions			: Pointer;
		ImageBase			: Pointer;
		ImageSize			: UInt64;
		ImageCodeType		: TEfiMemoryType;
		ImageDataType		: TEfiMemoryType;
	end;

	TEfiPixelBitmask = record
		RedMask			: UInt8;
		GreenMask		: UInt8;
		BlueMask		: UInt8;
		ReservedMask	: UInt8;
	end;

	TEfiGraphicsOutputBltPixel = record
		Blue		: UInt8;
		Green		: UInt8;
		Red			: UInt8;
		Reserved	: UInt8;
	end;

	TEfiGraphicsOutputModeInformation = record
		Version					: UInt32;
		HorizontalResolution	: UInt32;
		VerticalResolution		: UInt32;
		PixelFormat				: TEfiGraphicsPixelFormat;
		PixelInformation		: TEfiPixelBitmask;
		PixelsPerScanLine		: UInt32;
	end;

	TEfiGraphicsOutputProtocolMode = record
		MaxMode			: UInt32;
		Mode			: UInt32;
		Info			: PEfiGraphicsOutputModeInformation;
		SizeOfInfo		: TUINTN;
		FrameBufferBase	: TEfiPhysicalAddress;
		FrameBufferSize	: TUINTN;
	end;

	TEfiGraphicsOutputProtocol = record
		QueryMode	: TEfiGraphicsOutputProtocolQueryMode;
		SetMode		: TEfiGraphicsOutputProtocolSetMode;
		Blt			: TEfiGraphicsOutputProtocolBlt;
		Mode		: PEfiGraphicsOutputProtocolMode;
	end;

	TEfiRuntimeServices = record
		Hdr							: TEfiTableHeader;
		{ Time Services }
		GetTime						: TEfiGetTime;
		SetTime						: TEfiSetTime;
		GetWakeupTime				: TEfiGetWakeupTime;
		SetWakeupTime				: TEfiSetWakeupTime;
		{ Virtual Memory Services }
		SetVirtualAddressMap		: TEfiSetVirtualAddressMap;
		ConvertPointer				: TEfiConvertPointer;
		{ Variable Services }
		GetVariable					: TEfiGetVariable;
		GetNextVariableName			: TEfiGetNextVariableName;
		SetVariable					: TEfiSetVariable;
		{ Miscellaneous Services }
		GetNextHighMonotonicCount	: TEfiGetNextHighMonoCount;
		ResetSystem					: TEfiResetSystem;
		{ UEFI 2.0 Capsule Services }
		UpdateCapsule				: TEfiUpdateCapsule;
		QueryCapsuleCapabilities	: TEfiQueryCapsuleCapabilities;
		{ Miscellaneous UEFI 2.0 Service }
		QueryVariableInfo			: TEfiQueryVariableInfo;
	end;

	TEfiBootServices = record
		Hdr									: TEfiTableHeader;
		{ Task Priority Services }
		RaiseTPL							: TEfiRaiseTpl;
		RestoreTPL							: TEfiRestoreTpl;
		{ Memory Services }
		AllocatePages						: TEfiAllocatePages;
		FreePages							: TEfiFreePages;
		GetMemoryMap						: TEfiGetMemoryMap;
		AllocatePool						: TEfiAllocatePool;
		FreePool							: TEfiFreePool;
		{ Event & Timer Services }
		CreateEvent							: TEfiCreateEvent;
		SetTimer							: TEfiSetTimer;
		WaitForEvent						: TEfiWaitForEvent;
		SignalEvent							: TEfiSignalEvent;
		CloseEvent							: TEfiCloseEvent;
		CheckEvent							: TEfiCheckEvent;
		{ Protocol Handler Services }
		InstallProtocolInterface			: TEfiInstallProtocolInterface;
		ReinstallProtocolInterface			: TEfiReinstallProtocolInterface;
		UninstallProtocolInterface			: TEfiUninstallProtocolInterface;
		HandleProtocol						: TEfiHandleProtocol;
		Reserved							: Pointer;
		RegisterProtocolNotify				: TEfiRegisterProtocolNotify;
		LocateHandle						: TEfiLocateHandle;
		LocateDevicePath					: TEfiLocateDevicePath;
		InstallConfigurationTable			: TEfiInstallConfigurationTable;
		{ Image Services }
		LoadImage							: TEfiImageLoad;
		StartImage							: TEfiImageStart;
		Exit								: TEfiExit;
		UnloadImage							: TEfiImageUnload;
		ExitBootServices					: TEfiExitBootServices;
		{ Miscellaneous Services }
		GetNextMonotonicCount				: TEfiGetNextMonotonicCount;
		Stall								: TEfiStall;
		SetWatchdogTimer					: TEfiSetWatchdogTimer;
		{ DriverSupport Services }
		ConnectController					: TEfiConnectController;
		DisconnectController				: TEfiDisconnectController;
		{ Open and Close Protocol Services }
		OpenProtocol						: TEfiOpenProtocol;
		CloseProtocol						: TEfiCloseProtocol;
		OpenProtocolInformation				: TEfiOpenProtocolInformation;
		{ Library Services }
		ProtocolsPerHandle					: TEfiProtocolsPerHandle;
		LocateHandleBuffer					: TEfiLocateHandleBuffer;
		LocateProtocol						: TEfiLocateProtocol;
		InstallMultipleProtocolInterfaces	:
									TEfiInstallMultipleProtocolInterfaces;
		UninstallMultipleProtocolInterfaces	:
									TEfiUninstallMultipleProtocolInterfaces;
		{ 32-bit CRC Services }
		CalculateCrc32						: TEfiCalculateCrc32;
		{ Miscellaneous Services }
		CopyMem								: TEfiCopyMem;
		SetMem								: TEfiSetMem;
		CreateEventEx						: TEfiCreateEventEx;
	end;

	TEfiSystemTable = record
		Hdr					 : TEfiTableHeader;
		FirmwareVendor		 : PChar16;
		FirmwareRevision	 : UInt32;
		ConsoleInHandle		 : TEfiHandle;
		ConIn				 : PEfiSimpleTextInputProtocol;
		ConsoleOutHandle	 : TEfiHandle;
		ConOut				 : PEfiSimpleTextOutputProtocol;
		StandardErrorHandle	 : TEfiHandle;
		StdErr				 : PEfiSimpleTextOutputProtocol;
		RuntimeServices		 : PEfiRuntimeServices;
		BootServices		 : PEfiBootServices;
		NumberOfTableEntries : TUINTN;
		ConfigurationTable	 : PEfiConfigurationTable;
	end;

{$packrecords default}

{$endif}
