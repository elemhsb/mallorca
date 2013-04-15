#!/bin/sh
#
# $Id:$ olri
#
[ $# = 1 ] || { echo "Usage: $0 <pattern>"; exit 5; }
find . -type f -print0 | xargs -0 egrep "$@"
