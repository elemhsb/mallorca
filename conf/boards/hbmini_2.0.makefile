#
# hbmini_2.0.makefile
#
# http://paparazzi.enac.fr/wiki/HB/mini
#
ARCH=lpc21
BOARD=hbmini
BOARD_VERSION=2.0
BOARD_CFG=\"boards/$(BOARD)_$(BOARD_VERSION).h\"

ifndef FLASH_MODE
FLASH_MODE = IAP
endif

#
#
# some default values shared between different firmwares
#
#

#
# default LED configuration
#
ifndef RADIO_CONTROL_LED
RADIO_CONTROL_LED  = none
endif

ifndef BARO_LED
BARO_LED = none
endif

ifndef AHRS_ALIGNER_LED
AHRS_ALIGNER_LED = none
endif

ifndef GPS_LED
GPS_LED = none
endif

ifndef SYS_TIME_LED
SYS_TIME_LED = none
endif

#RADIO_CONTROL_LINK = UART0


ifndef MODEM_PORT
MODEM_PORT = UART0
endif
ifndef MODEM_BAUD
MODEM_BAUD = B57600
endif

ifndef GPS_PORT
GPS_PORT=UART1
endif
ifndef GPS_BAUD
GPS_BAUD=B38400
endif
#
# you can use different actuators by adding a configure option to your firmware section
# e.g. <configure name="ACTUATORS" value="actuators_ppm/>
#
ifndef ACTUATORS
ACTUATORS = actuators_4017
endif


# All targets on the TINY board run on the same processor achitecture
$(TARGET).ARCHDIR = $(ARCH)

