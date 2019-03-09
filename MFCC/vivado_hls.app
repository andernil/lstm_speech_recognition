<project xmlns="com.autoesl.autopilot.project" name="MFCC" top="FFT">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <files xmlns="">
        <file name="../wavData_yes.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../goldenMFCC_yes.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../solution1/fft_tb.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="MFCC/hamming_original.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="MFCC/hamming_original.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="MFCC/FFT_top.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="MFCC/FFT_top.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

