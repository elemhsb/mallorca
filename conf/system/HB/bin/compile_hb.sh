#!/bin/sh

cd $PAPARAZZI_HOME
. ./ENV

#   BOOZ2 \
#   EasyStar_ETS \
#   HBMINI_V1 \
#   HBMINI_V2 \
#   HBMINI_V2_FUNJET \
#   HBMINI_V3 \
#   HB_f \
#   Hexa_LisaL \
#   LisaLv11_Aspirinv15_FW \
#   LisaLv11_Aspirinv15_RC \
#   LisaLv11_Booz2v12_FW \
#   LisaLv11_Booz2v12_RC \
#   Microjet \
#   Quad_LisaM_2 \
#   Twinjet \
#   Twog_IMU \
#   Umarim_Lite \
#   Umarim_Lite_HB \

#   HBMINI_V1 \
#   HBMINI_V2_FUNJET \
#   HB_f \
#   HBMINI_V3 \

for AIRCRAFT in \
   HBMINI_V2 \
   HBMINI_V2_Q_MPU6000 \
   Twinjet \
   Twog_IMU \
   Umarim_Lite \
   Umarim_Lite_HB
do
	echo $AIRCRAFT
	make AIRCRAFT=$AIRCRAFT clean_ac ap 2>&1 | egrep -i 'ap.elf  :|error|warning|\*'
	echo "--------------------------------------------------------------------------"; echo
done
