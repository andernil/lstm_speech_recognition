<project xmlns="com.autoesl.autopilot.project" name="MFCC" top="MFCC_main">
    <files>
        <file name="MFCC/hamming_original.cpp" sc="0" tb="false" cflags=""/>
        <file name="MFCC/hamming_original.h" sc="0" tb="false" cflags=""/>
        <file name="../solution1/fft_tb.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
        <file name="../solution1/csim/build/goldenMFCC_yes.dat" sc="0" tb="1" cflags=""/>
        <file name="../solution1/csim/build/wavData_yes.dat" sc="0" tb="1" cflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

