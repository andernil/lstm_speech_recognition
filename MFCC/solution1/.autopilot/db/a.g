#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/anders/master/MFCC/solution1/.autopilot/db/a.g.bc ${1+"$@"}
