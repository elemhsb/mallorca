#!/bin/sh

#PATH=/opt/local/bin:$PATH:.
PATH=/usr/bin:/bin

cd $PAPARAZZI_HOME

OCDCONFDIR=conf/system/HB

inline_edit()
{
    # remove Warning about 12Mhz, we have 12Mhz.
    sed -i 's/	echo/	# &/' "$1"
}

CONFIG=$OCDCONFDIR/openocd-arm-usb-ocd.cfg
if [ ! -s $CONFIG ] ;  then
	cat \
	/opt/local/share/openocd/scripts/interface/olimex-arm-usb-ocd.cfg \
	/opt/local/share/openocd/scripts/target/lpc2148.cfg > $CONFIG
	inline_edit $CONFIG
fi

CONFIG_H=$OCDCONFDIR/openocd-arm-usb-ocd-h.cfg
if [ ! -s $CONFIG_H ] ;  then
	cat \
	/opt/local/share/openocd/scripts/interface/olimex-arm-usb-ocd-h.cfg \
	/opt/local/share/openocd/scripts/target/lpc2148.cfg > $CONFIG_H
	inline_edit $CONFIG_H
fi

OPENOCD_CFG=$PAPARAZZI_HOME/openocd.cfg
if [ ! -h $OPENOCD_CFG ] ; then
	printf "Which version ARM-USB-OCD or ARM-USB-OCD-H as default ?\n"
	printf "<return> | [hH]"
	read a
	if [ "$a" = "h" ] || [ "$a" = "H" ] ; then
		ln -s $CONFIG_H $OPENOCD_CFG
	else
		ln -s $CONFIG $OPENOCD_CFG
	fi
fi

killall openocd >/dev/null 2>&1 
sleep 0.5

exec openocd "$@" > openocd.log 2>&1 &
sleep 0.5
