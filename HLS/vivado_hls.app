<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="com.autoesl.autopilot.project" name="MFCC" top="window_FFT">
  <files>
    <file name="HLS/FFT_top.cpp" sc="0" tb="false" cflags=""/>
    <file name="HLS/FFT_top.h" sc="0" tb="false" cflags=""/>
    <file name="HLS/hamming_original.cpp" sc="0" tb="false" cflags=""/>
    <file name="HLS/hamming_original.h" sc="0" tb="false" cflags=""/>
    <file name="../solution1/fft_tb.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
    <file name="../../../speech_commands_v0.01/golden_mel.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
    <file name="../wav_data.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas"/>
  </files>
  <solutions>
    <solution name="solution1" status="active"/>
    <solution name="solution2" status="inactive"/>
  </solutions>
  <includePaths/>
  <libraryPaths/>
  <Simulation>
    <SimFlow name="csim" clean="true" csimMode="0" lastCsimMode="0"/>
  </Simulation>
</project>
