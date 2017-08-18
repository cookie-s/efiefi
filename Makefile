CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -mno-red-zone -fno-stack-protector -Wall \
		 -e EfiMain

define GDISK_COMMANDS
n


+100M
ef00
w
y
endef
export GDISK_COMMANDS

.PHONY: all image

all: main.efi image/EFI/BOOT/BOOTX64.EFI

%.efi: %.dll
	objcopy --target=efi-app-x86_64 $< $@

%.dll: %.c
	$(CC) $(CFLAGS) $< -o $@

image: image/EFI/BOOT/BOOTX64.EFI
	rm -f image.img
	mkdir -p mount
	dd if=/dev/zero of=image.img bs=1M count=200
	echo "$$GDISK_COMMANDS" | gdisk image.img
	sudo losetup loop62 image.img
	sudo kpartx -av /dev/loop62
	sudo mkfs.vfat -F32 /dev/mapper/loop62p1
	sudo mount /dev/mapper/loop62p1 mount
	sudo cp -r image/* mount
	sudo umount /dev/mapper/loop62p1
	sudo kpartx -dv /dev/loop62
	sudo losetup -d /dev/loop62
	qemu-img convert image.img -O vmdk image.vmdk
	cp -f image.vmdk /archshare

qemu: main.efi OVMF.fd image/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -nographic -bios OVMF.fd -hda fat:image

mount/EFI/BOOT/BOOTX64.EFI: main.efi
	mkdir -p image/EFI/BOOT
	cp main.efi image/EFI/BOOT/BOOTX64.EFI

OVMF.fd:
	wget http://downloads.sourceforge.net/project/edk2/OVMF/OVMF-X64-r15214.zip
	unzip OVMF-X64-r15214.zip OVMF.fd

clean:
	rm -f main.efi
