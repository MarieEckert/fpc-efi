// vim: set filetype=pascal :

{ type definitions for interfacing with EFI.
  you probably shouldn't include this file directly, you should use the efilib
  unit.
}

{$define EFILIB_EFITYPES_INC}

type
	{ Basic Types [Table 6] }
	TBoolean			= Byte;
	TINTN				= Int64;
	TUINTN				= UInt64;
	TEFIGuid			= array [0..15] of Byte;
	TEFIStatus			= TUINTN;
	TEFIHandle			= Pointer;
	TEFIEvent			= Pointer;
	TEFILba				= UInt64;
	TEFITpl				= TUINTN;
	TEFIMacAddress		= array [0..31] of Byte;
	TEFIIPv4Address		= array [0..3] of Byte;
	TEFIIPv6Address		= array [0..15] of Byte;
	TEFIIPAddress		= TEFIIPv6Address;
	PEFISystemTable		= Pointer;
	PEFIGuid			= ^TEFIGuid;
	PBoolean			= ^TBoolean;
	PChar8				= PChar;
	PChar16				= PWideChar;
	PINTN				= ^TINTN;
	PUINTN				= ^TUINTN;
	PPointer			= ^Pointer;
	TEFIPhysicalAddress	= UInt64;
	TEFIVirtualAddress	= UInt64;

	{ Enumations }
	TEFIResetType	= (EfiResetCold, EfiResetWarm, EfiResetShutdown);


	{$packrecords c}

	PEFISimpleTextInputProtocol = ^TEFISimpleTextInputProtocol;
	PEFIInputKey = ^TEFIInputKey;
	PEFISimpleTextOutputProtocol = ^TEFISimpleTextOutputProtocol;
	PEFITime = ^TEFITime;
	PEFITimeCapabilities = ^TEFITimeCapabilities;
	PEFIMemoryDescriptor = ^TEFIMemoryDescriptor;
	PEFICapsuleHeader = ^TEFICapsuleHeader;
	PPEFICapsuleHeader = ^PEFICapsuleHeader;
	PEFIPhysicalAddress = ^TEFIPhysicalAddress;
	PEFIResetType = ^TEFIResetType;
	PEFIRuntimeServices = ^TEFIRuntimeServices;
	PEFIConfigurationTable = ^TEFIConfigurationTable;

	TEFIInputReset = function(This: PEFISimpleTextInputProtocol;
							   ExtendedVerification: TBoolean): TEFIStatus;
							   cdecl;

	TEFIInputReadKey = function(This: PEFISimpleTextInputProtocol;
								 Key: PEFIInputKey): TEFIStatus; cdecl;

	TEFITextReset = TEFIInputReset;

	TEFITextString = function(This: PEFISimpleTextOutputProtocol;
							  _String: PChar16): TEFIStatus; cdecl;

	TEFITextTestString = TEFITextString;

	TEFITextQueryMode = function(This: PEFISimpleTextOutputProtocol;
								 ModeNumber: TUINTN; Columns: PUINTN;
								 Rows: PUINTN): TEFIStatus; cdecl;

	TEFITextSetMode = function(This: PEFISimpleTextOutputProtocol;
							   ModeNumber: TUINTN): TEFIStatus; cdecl;

	TEFITextSetAttribute = function(This: PEFISimpleTextOutputProtocol;
									Attribute: TUINTN): TEFIStatus; cdecl;

	TEFITextClearScreen = function(This: PEFISimpleTextOutputProtocol):
								   TEFIStatus; cdecl;

	TEFITextSetCursorPosition = function(This: PEFISimpleTextOutputProtocol;
										 Column: TUINTN; Row: TUINTN):
										 TEFIStatus; cdecl;

	TEFITextEnableCursor = function(This: PEFISimpleTextOutputProtocol;
									Visible: Boolean): TEFIStatus; cdecl;

	TEFIGetTime = function(Time: PEFITime; Capabilities: PEFITimeCapabilities):
						   TEFIStatus; cdecl;

	TEFISetTime = function(Time: PEFITime): TEFIStatus; cdecl;

	TEFIGetWakeupTime = function(Enabled: PBoolean; Pending: PBoolean;
								 Time: PEFITime): TEFIStatus; cdecl;

	TEFISetWakeupTime = function(Enable: TBoolean; Time: PEFITime): TEFIStatus;
								 cdecl;

	TEFISetVirtualAddressMap = function(MemoryMapSize: TUINTN;
										DescriptorSize: TUINTN;
										DescriptorVersion: UInt32;
										VirtualMap: PEFIMemoryDescriptor):
										TEFIStatus; cdecl;

	TEFIConvertPointer = function(DebugDesposition: TUINTN; Address: PPointer):
								  TEFIStatus; cdecl;

	TEFIGetVariable = function(VariableName: PChar16; VendorGuid: PEFIGuid;
							   Attributes: PUInt32; DataSize: PUINTN;
							   Data: Pointer): TEFIStatus; cdecl;

	TEFIGetNextVariableName = function(VariableNameSize: PUINTN;
									   VariableName: PChar16;
									   VendorGuid: PEFIGuid): TEFIStatus; cdecl;

	TEFISetVariable = function(VariableName: PChar16; VendorGuid: PEFIGuid;
							   Attributes: UInt32; DataSize: TUINTN;
							   Data: Pointer): TEFIStatus; cdecl;

	TEFIGetNextHighMonoCount = function(HighCount: PUInt32): TEFIStatus; cdecl;

	TEFIResetSystem = function(ResetType: TEFIResetType;
							   ResetStatus: TEFIStatus; DataSize: TUINTN;
							   ResetData: PChar16): TEFIStatus; cdecl;

	TEFIUpdateCapsule = function(CapsuleHeaderArray: PPEFICapsuleHeader;
								 CapsuleCount: TUINTN;
								 ScatterGatherList: TEFIPhysicalAddress):
								 TEFIStatus; cdecl;

	TEFIQueryCapsuleCapabilities = function(
									 CapsuleHeaderArray: PPEFICapsuleHeader;
									 CapsuleCount: TUINTN;
									 MaximumCapsuleSize: PUInt64;
									 ResetType: PEFIResetType
								   ): TEFIStatus; cdecl;

	TEFIQueryVariableInfo = function(Attributes: UInt32;
									 MaximumVariableStorageSize: PUInt64;
									 RemainingVariableStorageSize: PUInt64;
									 MaximumVariableSize: PUInt64): TEFIStatus;
									 cdecl;

	TEFITableHeader = packed record
		Signature	: UInt64;
		Revision	: UInt32;
		HeaderSize	: UInt32;
		CRC32		: UInt32;
		Reserved	: UInt32;
	end;

	TEFICapsuleHeader = packed record
		CapsuleGuid		 : TEFIGuid;
		HeaderSize		 : UInt32;
		Flags			 : UInt32;
		CapsuleImageSize : UInt32;
	end;

	TEFIConfigurationTable = packed record
		VendorGuid	: TEFIGuid;
		VendorTable	: Pointer;
	end;

	TEFIMemoryDescriptor = packed record
		_Type			: UInt32;
		PhysicalStart	: TEFIPhysicalAddress;
		VirtualStart	: TEFIVirtualAddress;
		NumberOfPages	: UInt64;
		Attribute		: UInt64;
	end;

	TEFITime = packed record
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

	TEFITimeCapabilities = packed record
		Resolution	: UInt32;
		Accuracy	: UInt32;
		SetsToZero	: TBoolean;
	end;

	TEFISimpleTextInputProtocol = packed record
		Reset			: TEFIInputReset;
		ReadKeyStroke	: TEFIInputReadKey;
		WaitForKey		: TEFIEvent;
	end;

	TEFIInputKey = packed record
		ScanCode	: UInt16;
		UnicodeChar	: Char16;
	end;

	TSimpleTextOutputMode = packed record
		MaxMode			: Int32;
		{ current settings }
		Mode			: Int32;
		Attribute		: Int32;
		CursorColumn	: Int32;
	CursorRow		: Int32;
		CursorVisible	: TBoolean;
	end;

	PSimpleTextOutputMode = ^TSimpleTextOutputMode;

	TEFISimpleTextOutputProtocol = packed record
		Reset				: TEFITextReset;
		OutputString		: TEFITextString;
		TestString			: TEFITextTestString;
		QueryMode			: TEFITextQueryMode;
		SetMode				: TEFITextSetMode;
		SetAttribute		: TEFITextSetAttribute;
		ClearScreen			: TEFITextClearScreen;
		SetCursorPosition	: TEFITextSetCursorPosition;
		EnableCursor		: TEFITextEnableCursor;
		Mode				: PSimpleTextOutputMode;
	end;

	TEFIRuntimeServices = packed record
		Hdr							: TEFITableHeader;
		{ Time Services }
		GetTime						: TEFIGetTime;
		SetTime						: TEFISetTime;
		GetWakeupTime				: TEFIGetWakeupTime;
		SetWakeupTime				: TEFISetWakeupTime;
		{ Virtual Memory Services }
		SetVirtualAddressMap		: TEFISetVirtualAddressMap;
		ConvertPointer				: TEFIConvertPointer;
		{ Variable Services }
		GetVariable					: TEFIGetVariable;
		GetNextVariableName			: TEFIGetNextVariableName;
		SetVariable					: TEFISetVariable;
		{ Miscellaneous Services }
		GetNextHighMonotonicCount	: TEFIGetNextHighMonoCount;
		ResetSystem					: TEFIResetSystem;
		{ UEFI 2.0 Capsule Services }
		UpdateCapsule				: TEFIUpdateCapsule;
		QueryCapsuleCapabilities	: TEFIQueryCapsuleCapabilities;
		{ Miscellaneous UEFI 2.0 Service }
		QueryVariableInfo			: TEFIQueryVariableInfo;
	end;

	TEFISystemTable = packed record
		Hdr					 : TEFITableHeader;
		FirmwareVendor		 : PChar16;
		FirmwareRevision	 : UInt32;
		ConsoleInHandle		 : TEFIHandle;
		ConIn				 : PEFISimpleTextInputProtocol;
		ConsoleOutHandle	 : TEFIHandle;
		ConOut				 : PEFISimpleTextOutputProtocol;
		StandardErrorHandle	 : TEFIHandle;
		StdErr				 : PEFISimpleTextOutputProtocol;
		RuntimeServices		 : PEFIRuntimeServices;
		BootServices		 : Pointer; // TODO: EFI_BOOT_SERVICES;
		NumberOfTableEntries : TUINTN;
		ConfigurationTable	 : PEFIConfigurationTable;
	end;

	{$packrecords default}
