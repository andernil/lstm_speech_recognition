<project xmlns="com.autoesl.autopilot.project" name="MFCC" top="window_FFT">
    <files>
        <file name="../../../speech_commands_v0.01/wav_data.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
        <file name="../../../speech_commands_v0.01/golden_mel.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
        <file name="../solution1/fft_tb.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
        <file name="MFCC/hamming_original.h" sc="0" tb="false" cflags=""/>
        <file name="MFCC/hamming_original.cpp" sc="0" tb="false" cflags=""/>
        <file name="MFCC/FFT_top.h" sc="0" tb="false" cflags=""/>
        <file name="MFCC/FFT_top.cpp" sc="0" tb="false" cflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" clean="true" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

