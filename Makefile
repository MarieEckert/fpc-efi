OFILES = src/entry.o

###################
# { Tool Config } #
###################

AS = nasm
ASFLAGS = -f elf64

OBJCOPY = objcopy
OBJCOPYFLAGS = -j .text -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym \
			   -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc \
			   --target efi-app-x86_64 --subsystem=10

LD = ld
LDFLAGS = -shared -Bsymbolic -Lgnu-efi/x86_64/lib -Lgnu-efi/x86_64/gnuefi \
		  -Tgnu-efi/gnuefi/elf_x86_64_efi.lds

PPC = fpc
PFLAGS = -Aelf -n -O3 -Op3 -Si -Sc -Sg -Xd -CX -XXs -Px86_64 -Rintel -Tlinux -Cg

#############
# { Rules } #
#############

main.efi: main.so
	objcopy $(OBJCOPYFLAGS) main.so main.efi

main.so: $(OFILES) src/kernel_main.o
	$(LD) $(LDFLAGS) src/*.o -o main.so

src/%.o: src/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# freepascal builds incrementally by itself
.PHONY: src/kernel_main.o
src/kernel_main.o:
	$(PPC) src/kernel_main.pas $(PFLAGS)
