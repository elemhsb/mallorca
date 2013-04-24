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

#   HB_f \

for AIRCRAFT in \
   HBMINI_V1 \
   HBMINI_V2 \
   HBMINI_V2_FUNJET \
   HBMINI_V3 \
   HBMINI_V2_Q_MPU6000 \
   Twinjet \
   Twog_IMU \
   Umarim_Lite \
   Umarim_Lite_HB
do
	bin/compile.sh 2>&1 | egrep -i 'ap.elf  :|error|warning|\*' | uniq | grep -v waypoint
done
