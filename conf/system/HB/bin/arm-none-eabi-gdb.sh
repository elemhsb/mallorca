#!/bin/sh

# Called from commandline
arm-none-eabi-gdb --command=conf/system/HB/gdbinit.gdb "$@"
