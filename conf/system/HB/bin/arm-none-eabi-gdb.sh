#!/bin/sh

arm-none-eabi-gdb --command=conf/system/HB/gdbinit.gdb "$@"
