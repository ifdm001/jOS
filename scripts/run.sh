#!/bin/sh

BASE="/home/jose/wip/jOS"

sudo su -c "mount -o loop,offset=1048576 ${BASE}/referencia.img /mnt/tmp/"
sudo su -c "cp ${BASE}/jOS/jOS /mnt/tmp/"
sudo su -c "umount /mnt/tmp"


if [ "$1" = "bochs" ]; then
	# Use this to compile bochs:
	# ./configure --enable-x86-64 --enable-smp --enable-long-phy-address --enable-pci --enable-configurable-msrs --enable-fast-function-calls --enable-show-ips --enable-debugger --enable-x86-debugger --enable-iodebug --enable-debugger-gui --enable-all-optimizations --enable-vmx --enable-logging --enable-readline --enable-disasm --prefix=/opt/bochs-2012/ 

	# bochs still needs the floppy:
	sudo su -c "mount ${BASE}/root.img /mnt/tmp/ -o loop"
	sudo su -c "cp ${BASE}/jOS/jOS /mnt/tmp/"
	sudo su -c "umount /mnt/tmp"

	/opt/bochs/bin/bochs -qf $BASE/jOS/scripts/jOSbochsrc


else # default to qemu:

	# control+alt+2 enters monitor mode
	#EXTRA="-S" # wait for gdb
	# to get 1gb page tables: -cpu kvm64,+pdpe1gb ,
	# it seems unimplemented, see: target-i386/cpuid.c on qemu source :(
	qemu-system-x86_64 -name jOS -s $EXTRA -machine pc-1.3,kernel_irqchip=off \
		-drive if=ide,index=0,media=disk,file=${BASE}/referencia.img \
		-enable-kvm \
		-no-reboot -m 1024 $*
fi



