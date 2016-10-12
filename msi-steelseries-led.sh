#!/bin/bash
### BEGIN INIT INFO
# Provides:		msi-steelseries-led.sh
# Required-Start:
# Required-Stop:
# Default-Start:	2 3 4 5
# Default-Stop:
# Short-Description:	msi-steelseries-led.sh
# Description:		Turn on Steelseries MSI Keyboard leds
### END INIT INFO

case "$1" in
	start)
		echo -n "Starting MSI SteelSeries Led:"
		/usr/bin/msi-steelseries-led -n -p work
		exit $?
		;;
	restart|reload|force-reload|condrestart)
		echo -n "Restarting MSI SteelSeries Led:"
		/usr/bin/msi-steelseries-led -n -p work
		exit $?
		;;
	*)
		echo "Usage: $0 {start|restart|reload|force-reload|condrestart}"
		exit 1
		;;
esac
