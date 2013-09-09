#!/bin/sh

PATH=/opt/local/bin:$PATH:.

$(dirname $0)/openocd.sh

exec eclipse -nosplash -data ../workspace-elemhsb-paparazzi-mallorca "$@" &
