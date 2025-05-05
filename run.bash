#!/bin/bash

set -e

make

uefi-run -b /usr/share/edk2/x64/OVMF.4m.fd -q $(which qemu-system-x86_64) main.efi