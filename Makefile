###########################################
# Makefile for msi-steelseries-led
#
# Eduardo Diez Viñuela
# 2016-03-30
###########################################

CC=gcc
LIBS=-lhidapi-libusb

.PHONY: all clean install uninstall

all: msi-steelseries-led

msi-steelseries-led:
	$(CC) -Wall -s -O2 msi-steelseries-led.c $(LIBS) -o msi-steelseries-led

msi-steelseries-led-E2:
	$(CC) -DE2 -Wall -s -O2 msi-steelseries-led.c $(LIBS) -o msi-steelseries-led

clean:
	rm -f msi-steelseries-led

install:
	cp udev-rules /etc/udev/rules.d/99-steelseries-gt72.rules
	cp msi-steelseries-led /usr/bin
	cp msi-steelseries-led.sh /etc/profile.d/
	cp msi-steelseries-led.service /lib/systemd/system/
	chmod 755 /usr/bin/msi-steelseries-led
	chmod 755 /etc/profile.d/msi-steelseries-led.sh
	systemctl enable msi-steelseries-led.service

uninstall:
	systemctl disable msi-steelseries-led.service
	rm -f /lib/systemd/system/msi-steelseries-led.service
	rm -f /etc/profile.d/msi-steelseries-led.sh
	rm -f /usr/bin/msi-steelseries-led
	rm -f /etc/udev/rules.d/99-steelseries-gt72.rules
	rm -f /home/*/.msi-steelseries-led.conf.bin
