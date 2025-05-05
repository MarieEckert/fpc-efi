// vim: set filetype=pascal :

{ constant definitions for interfacing with EFI.
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

{$ifndef EFILIB_EFICONSTANTS_INC}
{$define EFILIB_EFICONSTANTS_INC}

{$include efitypes.inc}

const
	{ EFI_STATUS Codes }
	{ EFI_STATUS Success Codes (High Bit Clear) [Table 235] }
	EFI_SUCCESS					: TEfiStatus = 0;

	{ EFI_STATUS Error Codes (High Bit Set) [Table 236] }
	EFI_LOAD_ERROR				: TEfiStatus = (1 shl 63) or 1;
	EFI_INVALID_PARAMETER		: TEfiStatus = (1 shl 63) or 2;
	EFI_UNSUPPORTED				: TEfiStatus = (1 shl 63) or 3;
	EFI_BAD_BUFFER_SIZE			: TEfiStatus = (1 shl 63) or 4;
	EFI_BUFFER_TOO_SMALL		: TEfiStatus = (1 shl 63) or 5;
	EFI_NOT_READY				: TEfiStatus = (1 shl 63) or 6;
	EFI_DEVICE_ERROR			: TEfiStatus = (1 shl 63) or 7;
	EFI_WRITE_PROTECTED			: TEfiStatus = (1 shl 63) or 8;
	EFI_OUT_OF_RESOURCES		: TEfiStatus = (1 shl 63) or 9;
	EFI_VOLUME_CORRUPTED		: TEfiStatus = (1 shl 63) or 10;
	EFI_VOLUME_FULL				: TEfiStatus = (1 shl 63) or 11;
	EFI_NO_MEDIA				: TEfiStatus = (1 shl 63) or 12;
	EFI_MEDIA_CHANGED			: TEfiStatus = (1 shl 63) or 13;
	EFI_NOT_FOUND				: TEfiStatus = (1 shl 63) or 14;
	EFI_ACCESS_DENIED			: TEfiStatus = (1 shl 63) or 15;
	EFI_NO_RESPONSE				: TEfiStatus = (1 shl 63) or 16;
	EFI_NO_MAPPING				: TEfiStatus = (1 shl 63) or 17;
	EFI_TIMEOUT					: TEfiStatus = (1 shl 63) or 18;
	EFI_NOT_STARTED				: TEfiStatus = (1 shl 63) or 19;
	EFI_ALREADY_STARTED			: TEfiStatus = (1 shl 63) or 20;
	EFI_ABORTED					: TEfiStatus = (1 shl 63) or 21;
	EFI_ICMP_ERROR				: TEfiStatus = (1 shl 63) or 22;
	EFI_TFTP_ERROR				: TEfiStatus = (1 shl 63) or 23;
	EFI_PROTOCOL_ERROR			: TEfiStatus = (1 shl 63) or 24;
	EFI_INCOMPATIBLE_VERSION	: TEfiStatus = (1 shl 63) or 25;
	EFI_SECURITY_VIOLATION		: TEfiStatus = (1 shl 63) or 26;
	EFI_CRC_ERROR				: TEfiStatus = (1 shl 63) or 27;
	EFI_END_OF_MEDIA			: TEfiStatus = (1 shl 63) or 28;
	EFI_END_OF_FILE				: TEfiStatus = (1 shl 63) or 31;
	EFI_INVALID_LANGUAGE		: TEfiStatus = (1 shl 63) or 32;
	EFI_COMPROMISED_DATA		: TEfiStatus = (1 shl 63) or 33;
	EFI_IP_ADDRESS_CONFLICT		: TEfiStatus = (1 shl 63) or 34;
	EFI_HTTP_ERROR				: TEfiStatus = (1 shl 63) or 35;

	{ EFI_STATUS Warning Codes (High Bit Clear) [Table 237] }
	EFI_WARN_UNKNOWN_GLYPH		: TEfiStatus = 1;
	EFI_WARN_DELETE_FAILURE		: TEfiStatus = 2;
	EFI_WARN_WRITE_FAILURE		: TEfiStatus = 3;
	EFI_WARN_BUFFER_TOO_SMALL	: TEfiStatus = 4;
	EFI_WARN_STALE_DATA			: TEfiStatus = 5;
	EFI_WARN_FILE_SYSTEM		: TEfiStatus = 6;

{$endif}
