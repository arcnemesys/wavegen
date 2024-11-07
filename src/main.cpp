#pragma once 
#include <wx/wx.h>
#include <cmath>
#include <vector>
enum {
  ID_Hello = 1
};

class WaveformGenerator {
  public:
    enum WaveType {
      SINE,
      SQUARE,
      SAW
    };

// Generates a vector of samples that comprise the waveform.
// frequency: pitch in Hz (cycles per second)
// amplitude: volume/loudness (0.0 to 1.0)
static std::vector<float> generateWaveForm(
    WaveformGenerator::WaveType type, 
    float frequency,
    float amplitude,
    float duration,
    float sampleRate = 44100) 
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
      case SINE:
        sample = amplitude * std::sin(phase);
        break;
      case SQUARE:
        sample = amplitude * (std::sin(phase) > 0 ? 1.0f : -1.0f);
        break;
      case SAW:
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
};

class MyFrame : public wxFrame {
  public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "My First wxWidgets App") {
      wxButton *button = new wxButton(this, wxID_ANY, "Click Me", wxPoint(20, 20));
      wxMenu *menuFile = new wxMenu;
      menuFile->Append(ID_Hello, "&Hello...\tCtrl-J", "Help string shown in status bar.");
      menuFile->AppendSeparator();
      menuFile->Append(wxID_EXIT);
      wxMenu *menuHelp = new wxMenu;
      menuHelp->Append(wxID_ABOUT);

      wxMenuBar *menuBar = new wxMenuBar;
    }
};

class MyApp : public wxApp {
  public:
    bool OnInit() {
      MyFrame *frame = new MyFrame();
      frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
