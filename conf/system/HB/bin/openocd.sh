#!/bin/sh

[ "$PAPARAZZI_HOME" = "" ] && printf "$0: failed!   PAPARAZZI_HOME not set\n\n" && exit 1

PATH=/usr/bin:/bin

cd $PAPARAZZI_HOME

# Configuration sources
OCDSCRIPTS=/usr/share/openocd/scripts

# Configuration destination relativ to PAPARAZZI_HOME
OCDCONFDIR=var

# functions
inline_edit()
{
    # remove Warning about 12Mhz, we have 12Mhz.
    sed -i 's/	echo/	# &/' "$1"
}


# Olimex ARM-USB-OCD config
CONFIG=$OCDCONFDIR/openocd-arm-usb-ocd.cfg
if [ ! -s $CONFIG ] ;  then
	mkdir -p $OCDCONFDIR
	cat \
	    $OCDSCRIPTS/interface/olimex-arm-usb-ocd.cfg \
	    $OCDSCRIPTS/target/lpc2148.cfg > $CONFIG
	inline_edit $CONFIG
fi

# Olimex ARM-USB-OCD-H config
CONFIG_H=$OCDCONFDIR/openocd-arm-usb-ocd-h.cfg
if [ ! -s $CONFIG_H ] ;  then
	mkdir -p $OCDCONFDIR
	cat \
	    $OCDSCRIPTS/interface/olimex-arm-usb-ocd-h.cfg \
	    $OCDSCRIPTS/target/lpc2148.cfg > $CONFIG_H
	inline_edit $CONFIG_H
fi

# Symlink to User defined configuration
OPENOCD_CFG=$OCDCONFDIR/openocd.cfg
if [ ! -h $OPENOCD_CFG ] ; then
	printf "Which version ARM-USB-OCD or ARM-USB-OCD-H as default ?\n"
	printf "<return> | [hH]"
	read a
	if [ "$a" = "h" ] || [ "$a" = "H" ] ; then
		ln -s $( basename $CONFIG_H ) $OPENOCD_CFG
	else
		ln -s $( basename $CONFIG ) $OPENOCD_CFG
	fi
fi

# Stop all running openocd
killall openocd >/dev/null 2>&1 
sleep 0.5

# Start new OPENOCD
exec openocd -f $OPENOCD_CFG "$@" > openocd.log 2>&1 &
