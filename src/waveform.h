#pragma once

#include <vector>

class WaveformGenerator {
public:
    enum WaveType {
        SINE,
        SQUARE,
        SAW
    };

    static std::vector<float> generateWaveform(
        WaveType type, 
        float frequency, 
        float amplitude, 
        float duration, 
        float sampleRate = 44100
    );
};

