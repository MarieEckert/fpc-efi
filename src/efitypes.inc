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
	TEFIPhysicalAddress	= UInt64;
	TEFIVirtualAddress	= UInt64;
	PEFIHandle			= ^TEFIHandle;
	PEFIGuid			= ^TEFIGuid;
	PEFIEvent			= ^TEFIEvent;
	PBoolean			= ^TBoolean;
	PChar8				= PChar;
	PChar16				= PWideChar;
	PINTN				= ^TINTN;
	PUINTN				= ^TUINTN;
	PPointer			= ^Pointer;
	PPChar8				= ^PChar8;
	PPChar16			= ^PChar16;
	PPEFIHandle			= ^PEFIHandle;
	PPEFIGuid			= ^PEFIGuid;
	PPPEFIGuid			= ^PPEFIGuid;

	{ Enumations }
	TEFIResetType		= (EfiResetCold,
						   EfiResetWarm,
						   EfiResetShutdown);
	TEFIAllocateType	= (AllocateAnyPages,
						   AllocateMaxAddress,
						   AllocateAddress,
						   MaxAllocateType);
	TEFIMemoryType		= (EfiReservedMemoryType,
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
	TEFIInterfaceType	= (EfiNativeInterface);
	TEFILocateSearchType= (AllHandles,
						   ByRegisterNotify,
						   ByProtocol);
	TEFITimerDelay		= (TimerCancel,
						   TimerPeriodic,
						   TiemrRelative);

	{$packrecords c}

	PEFISimpleTextInputProtocol			= ^TEFISimpleTextInputProtocol;
	PEFIInputKey						= ^TEFIInputKey;
	PEFISimpleTextOutputProtocol		= ^TEFISimpleTextOutputProtocol;
	PEFITime							= ^TEFITime;
	PEFITimeCapabilities				= ^TEFITimeCapabilities;
	PEFIMemoryDescriptor				= ^TEFIMemoryDescriptor;
	PEFICapsuleHeader					= ^TEFICapsuleHeader;
	PPEFICapsuleHeader					= ^PEFICapsuleHeader;
	PEFIPhysicalAddress					= ^TEFIPhysicalAddress;
	PEFIDevicePathProtocol				= ^TEFIDevicePathProtocol;
	PPEFIDevicePathProtocol				= ^PEFIDevicePathProtocol;
	PEFIOpenProtocolInformationEntry	= ^TEFIOpenProtocolInformationEntry;
	PPEFIOpenProtocolInformationEntry	= ^PEFIOpenProtocolInformationEntry;
	PEFIResetType						= ^TEFIResetType;
	PEFIRuntimeServices					= ^TEFIRuntimeServices;
	PEFIConfigurationTable				= ^TEFIConfigurationTable;
	PEFIBootServices					= ^TEFIBootServices;
	PEFISystemTable						= ^TEFISystemTable;

	{ procedural types }

	TEFIInputReset = function(
						 This: PEFISimpleTextInputProtocol;
						 ExtendedVerification: TBoolean
					 ): TEFIStatus; cdecl;

	TEFIInputReadKey = function(
						   This: PEFISimpleTextInputProtocol;
						   Key: PEFIInputKey
					   ): TEFIStatus; cdecl;

	TEFITextReset = TEFIInputReset;

	TEFITextString = function(
						 This: PEFISimpleTextOutputProtocol;
						 _String: PChar16
					 ): TEFIStatus; cdecl;

	TEFITextTestString = TEFITextString;

	TEFITextQueryMode = function(
							This: PEFISimpleTextOutputProtocol;
							ModeNumber: TUINTN;
							Columns: PUINTN;
							Rows: PUINTN):
						TEFIStatus; cdecl;

	TEFITextSetMode = function(
						  This: PEFISimpleTextOutputProtocol;
						  ModeNumber: TUINTN
					  ): TEFIStatus; cdecl;

	TEFITextSetAttribute = function(
							   This: PEFISimpleTextOutputProtocol;
							   Attribute: TUINTN):
						   TEFIStatus; cdecl;

	TEFITextClearScreen = function(
							  This: PEFISimpleTextOutputProtocol
						  ): TEFIStatus; cdecl;

	TEFITextSetCursorPosition = function(
									This: PEFISimpleTextOutputProtocol;
									Column: TUINTN;
									Row: TUINTN
								): TEFIStatus; cdecl;

	TEFITextEnableCursor = function(
							   This: PEFISimpleTextOutputProtocol;
							   Visible: Boolean
						   ): TEFIStatus; cdecl;

	TEFIGetTime = function(
					  Time: PEFITime;
					  Capabilities: PEFITimeCapabilities
				  ): TEFIStatus; cdecl;

	TEFISetTime = function(Time: PEFITime): TEFIStatus; cdecl;

	TEFIGetWakeupTime = function(
							Enabled: PBoolean;
							Pending: PBoolean;
							Time: PEFITime
						): TEFIStatus; cdecl;

	TEFISetWakeupTime = function(
							Enable: TBoolean;
							Time: PEFITime
						): TEFIStatus; cdecl;

	TEFISetVirtualAddressMap = function(
								   MemoryMapSize: TUINTN;
								   DescriptorSize: TUINTN;
								   DescriptorVersion: UInt32;
								   VirtualMap: PEFIMemoryDescriptor
							   ): TEFIStatus; cdecl;

	TEFIConvertPointer = function(
							 DebugDesposition: TUINTN;
							 Address: PPointer
						 ): TEFIStatus; cdecl;

	TEFIGetVariable = function(
						  VariableName: PChar16;
						  VendorGuid: PEFIGuid;
						  Attributes: PUInt32;
						  DataSize: PUINTN;
						  Data: Pointer
					  ): TEFIStatus; cdecl;

	TEFIGetNextVariableName = function(
								  VariableNameSize: PUINTN;
								  VariableName: PChar16;
								  VendorGuid: PEFIGuid
							  ): TEFIStatus; cdecl;

	TEFISetVariable = function(
						  VariableName: PChar16;
						  VendorGuid: PEFIGuid;
						  Attributes: UInt32;
						  DataSize: TUINTN;
						  Data: Pointer
					  ): TEFIStatus; cdecl;

	TEFIGetNextHighMonoCount = function(HighCount: PUInt32): TEFIStatus; cdecl;

	TEFIResetSystem = function(
						 ResetType: TEFIResetType;
						 ResetStatus: TEFIStatus; DataSize: TUINTN;
						 ResetData: PChar16
					  ): TEFIStatus; cdecl;

	TEFIUpdateCapsule = function(
							CapsuleHeaderArray: PPEFICapsuleHeader;
							CapsuleCount: TUINTN;
							ScatterGatherList: TEFIPhysicalAddress
						): TEFIStatus; cdecl;

	TEFIQueryCapsuleCapabilities = function(
									   CapsuleHeaderArray: PPEFICapsuleHeader;
									   CapsuleCount: TUINTN;
									   MaximumCapsuleSize: PUInt64;
									   ResetType: PEFIResetType
								   ): TEFIStatus; cdecl;

	TEFIQueryVariableInfo = function(
								Attributes: UInt32;
								MaximumVariableStorageSize: PUInt64;
								RemainingVariableStorageSize: PUInt64;
								MaximumVariableSize: PUInt64
							): TEFIStatus; cdecl;

	TEFIRaiseTPL = function(NewTpl: TEFITPL): TEFITPL; cdecl;

	TEFIRestoreTPL = procedure(OldTpl: TEFITPL); cdecl;

	TEFIAllocatePages = function(
							_Type: TEFIAllocateType;
							MemoryType: TEFIMemoryType;
							Pages: TUINTN;
							Memory: PEFIPhysicalAddress
						): TEFIStatus; cdecl;

	TEFIFreePages = function(
						Memory: PEFIPhysicalAddress;
						Pages: TUINTN
					): TEFIStatus; cdecl;

	TEFIGetMemoryMap = function(
						   MemoryMapSize: PUINTN;
						   MemoryMap: PEFIMemoryDescriptor;
						   MapKey: PUINTN;
						   DescriptorSize: PUINTN;
						   DescriptorVersion: PUInt32
					   ): TEFIStatus; cdecl;

	TEFIAllocatePool = function(
						   PoolType: TEFIMemoryType;
						   Size: TUINTN;
						   Buffer: PPointer
					   ): TEFIStatus; cdecl;

	TEFIFreePool = function(Buffer: Pointer): TEFIStatus; cdecl;

	TEFIEventNotify = procedure(
						  Event: TEFIEvent;
						  Context: Pointer
					  ); cdecl;

	TEFICreateEvent = function(
						  _Type: UInt32;
						  NotifyTpl: TEFITPL;
						  NotifyFunction: TEFIEventNotify;
						  Event: PEFIEvent
					  ): TEFIStatus; cdecl;

	TEFISetTimer = function(
					   Event: TEFIEvent;
					   _Type: TEFITimerDelay;
					   TriggerTime: UInt64
				   ): TEFIStatus; cdecl;

	TEFIWaitForEvent = function(
						   NumberOfEvents: TUINTN;
						   Event: PEFIEvent;
						   Index: PUINTN
					   ): TEFIStatus; cdecl;

	TEFISignalEvent = function(Event: TEFIEvent): TEFIStatus; cdecl;

	TEFICloseEvent = function(Event: TEFIEvent): TEFIStatus; cdecl;

	TEFICheckEvent = function(Event: TEFIEvent): TEFIStatus; cdecl;

	TEFIInstallProtocolInterface = function(
									   Handle: TEFIHandle;
									   Protocol: PEFIGuid;
									   InterfaceType: TEFIInterfaceType;
									   _Interface: Pointer
								   ): TEFIStatus; cdecl;

	TEFIReinstallProtocolInterface = function(
										 Handle: TEFIHandle;
										 Protocol: PEFIGuid;
										 OldInterface: Pointer;
										 NewInterface: Pointer
									 ): TEFIStatus; cdecl;

	TEFIUninstallProtocolInterface = function(
										 Handle: TEFIHandle;
										 Protocol: PEFIGuid;
										 _Interface: Pointer
									 ): TEFIStatus; cdecl;

	TEFIHandleProtocol = function(
							 Handle: TEFIHandle;
							 Protocol: PEFIGuid;
							 _Interface: PPointer
						 ): TEFIStatus; cdecl;

	TEFIRegisterProtocolNotify = function(
									 Protocol: PEFIGuid;
									 Event: TEFIEvent;
									 Registration: PPointer
						 ): TEFIStatus; cdecl;

	TEFILocateHandle = function(
						   SearchType: TEFILocateSearchType;
						   Protocol: PEFIGuid;
						   SearchKey: Pointer;
						   BufferSize: PUINTN;
						   Buffer: PEFIHandle
					   ): TEFIStatus; cdecl;

	TEFILocateDevicePath = function(
							   Protocol: PEFIGuid;
							   DevicePath: PPEFIDevicePathProtocol;
							   Device: PEFIHandle
						   ): TEFIStatus; cdecl;

	TEFIInstallConfigurationTable = function(
										Guid: PEFIGuid;
										Table: Pointer
									): TEFIstatus; cdecl;

	TEFIImageLoad = function(
						BootPolicy: TBoolean;
						ParentImageHandle: TEFIHandle;
						DevicePath: PEFIDevicePathProtocol;
						SourceBuffer: Pointer;
						SourceSize: TUINTN;
						ImageHandle: PEFIHandle
					): TEFIStatus; cdecl;

	TEFIImageStart = function(
						 ImageHandle: TEFIHandle;
						 ExitDataSize: PUINTN;
						 ExitData: PPChar16
					 ): TEFIStatus; cdecl;

	TEFIExit = function(
				   ImageHandle: TEFIHandle;
				   ExitStatus: TEFIStatus;
				   ExitDataSize: TUINTN;
				   ExitData: PChar16
			   ): TEFIStatus; cdecl;

	TEFIImageUnload = function(ImageHandle: TEFIHandle): TEFIStatus; cdecl;

	TEFIExitBootServices = function(
							   ImageHandle: TEFIHandle;
							   MapKey: TUINTN
						   ): TEFIStatus; cdecl;

	TEFIGetNextMonotonicCount = function(Count: PUInt64): TEFIStatus; cdecl;

	TEFIStall = function(Microseconds: TUINTN): TEFIStatus; cdecl;

	TEFISetWatchdogTimer = function(
							   Timeout: TUINTN;
							   WatchdogCode: UInt64;
							   DataSize: TUINTN;
							   WatchdogData: PChar16
						   ): TEFIStatus; cdecl;

	TEFIConnectController = function(
								ControllerHandle: TEFIHandle;
								DriverImageHandle: PEFIHandle;
								RemainingDevicePath: PEFIDevicePathProtocol;
								Recursive: TBoolean
							): TEFIStatus; cdecl;

	TEFIDisconnectController = function(
								   ControllerHandle:  TEFIHandle;
								   DriverImageHandle: TEFIHandle;
								   ChildHandle: TEFIHandle
							   ): TEFIStatus; cdecl;

	TEFIOpenProtocol = function(
						   Handle: TEFIHandle;
						   Protocol: PEFIGuid;
						   _Interface: PPointer;
						   AgentHandle: TEFIHandle;
						   ControllerHandle: TEFIHandle;
						   Attributes: UInt32
					   ): TEFIStatus; cdecl;

	TEFICloseProtocol = function(
						   Handle: TEFIHandle;
						   Protocol: PEFIGuid;
						   AgentHandle: TEFIHandle;
						   ControllerHandle: TEFIHandle
					   ): TEFIStatus; cdecl;

	TEFIOpenProtocolInformation = function(
									  Handle: TEFIHandle;
									  Protocol: PEFIGuid;
									  EntryBuffer:
										PPEFIOpenProtocolInformationEntry;
									  EntryCount: PUINTN
								  ): TEFIStatus; cdecl;

	TEFIProtocolsPerHandle = function(
								 Handle: TEFIHandle;
								 ProtocolBuffer: PPPEFIGuid;
								 ProtocolBufferCount: PUINTN
							 ): TEFIStatus; cdecl;

	TEFILocateHandleBuffer = function(
								 SearchType: TEFILocateSearchType;
								 Protocol: PEFIGuid;
								 SearchKey: Pointer;
								 NoHandles: PUINTN;
								 Buffer: PPEFIHandle
							 ): TEFIStatus; cdecl;

	TEFILocateProtocol = function(
							 Protocol: PEFIGuid;
							 Registration: Pointer;
							 _Interface: PPointer
						 ): TEFIStatus; cdecl;

	TEFIInstallMultipleProtocolInterfaces = function(
												Handle: PEFIHandle
											): TEFIStatus; cdecl; varargs;

	TEFIUninstallMultipleProtocolInterfaces = function(
												  Handle: TEFIHandle
											  ): TEFIStatus; cdecl; varargs;

	TEFICalculateCrc32 = function(
							 Data: Pointer;
							 DataSize: PUINTN;
							 Crc32: PUInt32
						 ): TEFIStatus; cdecl;

	TEFICopyMem = procedure(
					  Destination: Pointer;
					  Source: Pointer;
					  Length: TUINTN
				  ); cdecl;

	TEFISetMem = procedure(
					 Buffer: Pointer;
					 Size: TUINTN;
					 Value: UInt8
				  ); cdecl;

	TEFICreateEventEx = function(
							_Type: UInt32;
							NotifyTpl: TEFITPL;
							NotifyFunction: TEFIEventNotify;
							NotifyContext: Pointer;
							EventGroup: PEFIGuid;
							Event: PEFIEvent
					  ): TEFIStatus; cdecl;

	{ records }

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

	TEFIOpenProtocolInformationEntry = packed record
		AgentHandle		 : TEFIHandle;
		ControllerHandle : TEFIHandle;
		Attributes		 : UInt32;
		OpenCount		 : UInt32;
	end;

	TEFIDevicePathProtocol = packed record
		_Type	: UInt8;
		SubType	: UInt8;
		Length	: array [0..1] of UInt8;
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

	TEFIBootServices = packed record
		Hdr									: TEFITableHeader;
		{ Task Priority Services }
		RaiseTPL							: TEFIRaiseTpl;
		RestoreTPL							: TEFIRestoreTpl;
		{ Memory Services }
		AllocatePages						: TEFIAllocatePages;
		FreePages							: TEFIFreePages;
		GetMemoryMap						: TEFIGetMemoryMap;
		AllocatePool						: TEFIAllocatePool;
		FreePool							: TEFIFreePool;
		{ Event & Timer Services }
		CreateEvent							: TEFICreateEvent;
		SetTimer							: TEFISetTimer;
		WaitForEvent						: TEFIWaitForEvent;
		SignalEvent							: TEFISignalEvent;
		CloseEvent							: TEFICloseEvent;
		CheckEvent							: TEFICheckEvent;
		{ Protocol Handler Services }
		InstallProtocolInterface			: TEFIInstallProtocolInterface;
		ReinstallProtocolInterface			: TEFIReinstallProtocolInterface;
		UninstallProtocolInterface			: TEFIUninstallProtocolInterface;
		HandleProtocol						: TEFIHandleProtocol;
		Reserved							: Pointer;
		RegisterProtocolNotify				: TEFIRegisterProtocolNotify;
		LocateHandle						: TEFILocateHandle;
		LocateDevicePath					: TEFILocateDevicePath;
		InstallConfigurationTable			: TEFIInstallConfigurationTable;
		{ Image Services }
		LoadImage							: TEFIImageLoad;
		StartImage							: TEFIImageStart;
		Exit								: TEFIExit;
		UnloadImage							: TEFIImageUnload;
		ExitBootServices					: TEFIExitBootServices;
		{ Miscellaneous Services }
		GetNextMonotonicCount				: TEFIGetNextMonotonicCount;
		Stall								: TEFIStall;
		SetWatchdogTimer					: TEFISetWatchdogTimer;
		{ DriverSupport Services }
		ConnectController					: TEFIConnectController;
		DisconnectController				: TEFIDisconnectController;
		{ Open and Close Protocol Services }
		OpenProtocol						: TEFIOpenProtocol;
		CloseProtocol						: TEFICloseProtocol;
		OpenProtocolInformation				: TEFIOpenProtocolInformation;
		{ Library Services }
		ProtocolsPerHandle					: TEFIProtocolsPerHandle;
		LocateHandleBuffer					: TEFILocateHandleBuffer;
		LocateProtocol						: TEFILocateProtocol;
		InstallMultipleProtocolInterfaces	:
									TEFIInstallMultipleProtocolInterfaces;
		UninstallMultipleProtocolInterfaces	:
									TEFIUninstallMultipleProtocolInterfaces;
		{ 32-bit CRC Services }
		CalculateCrc32						: TEFICalculateCrc32;
		{ Miscellaneous Services }
		CopyMem								: TEFICopyMem;
		SetMem								: TEFISetMem;
		CreateEventEx						: TEFICreateEventEx;
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
		BootServices		 : PEFIBootServices;
		NumberOfTableEntries : TUINTN;
		ConfigurationTable	 : PEFIConfigurationTable;
	end;

	{$packrecords default}
