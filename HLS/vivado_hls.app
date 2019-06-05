<project xmlns="com.autoesl.autopilot.project" name="HLS" top="window_FFT">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" clean="true" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <files xmlns="">
        <file name="../wav_data.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../../../speech_commands_v0.01/golden_mel.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="../fft_tb.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="HLS/hamming_original.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="HLS/hamming_original.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="HLS/FFT_top.h" sc="0" tb="false" cflags="" blackbox="false"/>
        <file name="HLS/FFT_top.cpp" sc="0" tb="false" cflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

