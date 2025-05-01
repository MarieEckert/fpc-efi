CC = gcc
CFLAGS = -Ignu-efi/inc -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args

LD = ld
LDFLAGS = -shared -Bsymbolic -Lgnu-efi/x86_64/lib -Lgnu-efi/x86_64/gnuefi -Tgnu-efi/gnuefi/elf_x86_64_efi.lds gnu-efi/x86_64/gnuefi/crt0-efi-x86_64.o

PC = fpc
PFLAGS = -Aelf -n -O3 -Op3 -Si -Sc -Sg -Xd -CX -XXs -Px86_64 -Rintel -Tlinux

main.efi: main.so
	objcopy -j .text -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10 main.so main.efi

main.so: kernel_main.o
	$(LD) $(LDFLAGS) kernel_main.o system.o -o main.so -lgnuefi -lefi

.PHONY: kernel_main.o
kernel_main.o: kernel_main.pas
	$(PC) kernel_main.pas $(PFLAGS)