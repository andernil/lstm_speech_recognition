#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/anders/master/HLS/solution1/.autopilot/db/a.g.bc ${1+"$@"}
