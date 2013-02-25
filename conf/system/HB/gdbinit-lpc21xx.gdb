# set debug remote 1

target remote 	localhost:3333

monitor arm7_9 	dcc_downloads 		enable
monitor arm7_9	fast_memory_access	enable
monitor reset 	halt

# set debug remote 0

symbol-file	var/HBMINI_V2/ap/ap.elf
tbreak		main
load 		var/HBMINI_V2/ap/ap.elf

cont
