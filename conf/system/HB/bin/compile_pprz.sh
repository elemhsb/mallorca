#!/bin/sh

for i in BOOZ2 Quad_NavGo Hexa_LisaL Quad_LisaM_2 Bixler MentorEnergy Microjet Twog_IMU Umarim_Lite Twinjet EasyStar_ETS setup_lisam2 Twinstar_energyadaptive
do
	AIRCRAFT=$i
	bin/compile.sh
	echo "------------------------------------------------------"
	read a
done
