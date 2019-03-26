#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/anders/master/Vivado_HLS/fft_single/proj/solution1/.autopilot/db/a.g.bc ${1+"$@"}
