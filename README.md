# fpc-efi

UEFI bindings for freepascal and a very simple application.

**This is currently more of a testing ground and not particularly cleaned up to
be usable as a library**

## File Overview

* `src/efilib.pas` - The main unit which contains/includes all the bindings
* `src/eficonstants.inc` – Required by the efilib unit, contains EFI constants
* `src/efitypes.inc` - Also required by the efilib unit, contains EFI types
* `src/elf.pas` – Datatypes and constants for working with ELF binaries
* `src/entry.asm` – Main entry point for the example program
* `src/kernel_main.pas` – Actual pascal code for the example program
* `src/system.pas` – Basic fpc system unit

## Building and running the example
### Requirements

* nasm
* fpc 3.2.2
* GNU development tools
* qemu
* OVMF

### Building

```bash
git submodule update --init \
make
```

*the example currently still relies on the linker script from gnuefi*

### Running

```bash
uefi-run -b <path to your OVMF.fd> -q $(which qemu-system-x86_64) main.efi
```

**OR** build and run in one command

```
./run.bash
```

(although that might need some adjustments depending on your system)

## Acknowledgements

The gnuefi project was and still is a very good resource for getting a more
practical sense of what has to be done. It was also the original source for the
code in `src/entry.asm`, although I translated it to NASM and made some further
modifications. The current relocation logic which is being used also comes from
gnuefi (although it was also ported by me, to freepascal in this case).
