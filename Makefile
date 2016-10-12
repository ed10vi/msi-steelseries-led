###########################################
# Makefile for msi-steelseries-led
#
# Eduardo Diez Viñuela
# 2016-03-30
###########################################

all: msi-steelseries-led

CC=gcc
LIBS=-lhidapi-libusb

msi-steelseries-led:
	$(CC) -Wall -g msi-steelseries-led.c $(LIBS) -o msi-steelseries-led

clean:
	rm -f msi-steelseries-led

install:
	cp udev-rules /etc/udev/rules.d/99-steelseries-gt72.rules
	cp msi-steelseries-led /usr/bin
	cp profile /etc/profile.d/msi-steelseries-led.sh
	cp msi-steelseries-led.sh /etc/init.d/msi-steelseries-led.sh
	chmod 755 /etc/init.d/msi-steelseries-led.sh
	update-rc.d msi-steelseries-led.sh defaults

uninstall:
	update-rc.d -f msi-steelseries-led.sh remove
	rm -f /etc/init.d/msi-steelseries-led.sh
	rm -f /etc/profile.d/msi-steelseries-led.sh
	rm -f /usr/bin/msi-steelseries-led
	rm -f /etc/udev/rules.d/99-steelseries-gt72.rules
	rm -f /home/*/.msi-steelseries-led.conf.bin
	
.PHONY: clean