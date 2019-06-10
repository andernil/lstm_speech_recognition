<project xmlns="com.autoesl.autopilot.project" name="HLS_FFT_16" top="hls_xfft2real">
    <files>
        <file name="HLS_FFT_16/hls_realfft.h" sc="0" tb="false" cflags=""/>
        <file name="HLS_FFT_16/real2xfft.cpp" sc="0" tb="false" cflags=""/>
        <file name="HLS_FFT_16/sliding_win.h" sc="0" tb="false" cflags=""/>
        <file name="HLS_FFT_16/window_fn.h" sc="0" tb="false" cflags=""/>
        <file name="HLS_FFT_16/xfft2real.cpp" sc="0" tb="false" cflags=""/>
        <file name="HLS_FFT_16/xfft2real.h" sc="0" tb="false" cflags=""/>
        <file name="../hls_realfft_test.cpp" sc="0" tb="1" cflags=""/>
        <file name="../reference_fft.h" sc="0" tb="1" cflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" clean="true" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
        <solution name="solution2" status="inactive"/>
    </solutions>
</project>

