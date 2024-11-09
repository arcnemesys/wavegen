#define _USE_MATH_DEFINES
#include <cmath>
#include "waveform.h"
// Generates a vector of samples that comprise the waveform.
// frequency: pitch in Hz (cycles per second)
// amplitude: volume/loudness (0.0 to 1.0)
std::vector<float> WaveformGenerator::generateWaveform(
    WaveformGenerator::WaveType type, 
    float frequency,
    float amplitude,
    float duration,
    float sampleRate) 
{
  std::vector<float> samples;
  // Calculate number of samples needed
  int numSamples = static_cast<int>(duration * sampleRate);
  
  // Track the current angle in the waveform cycle.
  float phase = 0.0f;
  // Amount to advance phase each sample 
  // 2(PI) * frequency gives us the number of full cycles per second.
    // We divide this by sample rate to get movement per sample.
  float phaseIncrement = 2.0f * M_PI * frequency / sampleRate;
  
  // Generate each sample 
  for (int i = 0; i < numSamples; i++) {
    float sample = 0.0f;
    switch (type) {
		case WaveformGenerator::SINE:
			sample = amplitude * std::sin(phase);
			break;
		case WaveformGenerator::SQUARE:
			sample = amplitude * (std::sin(phase) > 0 ? 1.0f : -1.0f);
			break;
		case WaveformGenerator::SAW:
			sample = amplitude * (2.0f * (phase / (2.0f * M_PI)) - 1.0f);
			break;
    }

    samples.push_back(sample);
    
    // Move phase forward and wrap around at 2Pi
    phase += phaseIncrement;
    if (phase >= 2.0f * M_PI) {
      phase -= 2.0f * M_PI;
    }
  }

  return samples;
}
