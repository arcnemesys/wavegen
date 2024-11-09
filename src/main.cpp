#pragma once 
#include <wx/wx.h>
#include "waveform.h"
enum {
  ID_Hello = 1
};
class WaveformPanel : public wxPanel {
private:
	// Storing calculated waveform data points
	std::vector<float> samples;

public:
	// Constructor takes a parent window pointer 
	// wxID_ANY lets wx auto-assign an unique identifier::
	WaveformPanel(wxFrame* parent): wxPanel(parent, wxID_ANY) {
		SetBackgroundColour(*wxBLACK);
		// Connects paint event to handler, called whenever the panel is redrawn
		Bind(wxEVT_PAINT, &WaveformPanel::OnPaint, this);

		// Generate initial waveform data 
		samples = WaveformGenerator::generateWaveform(
			WaveformGenerator::SINE,
			440.0f, // A4 note 
			0.5f,   // Half amplitude 
			0.02f   // 20 milliseconds of data
		);
	}

	// Paint event handler called when window needs to be redrawn
	void OnPaint(wxPaintEvent& evt) {
		wxPaintDC dc(this);
		// Current panel dimensions
		int width, height;
		GetSize(&width, &height);

		// Draw axis 
		dc.SetPen(*wxGREEN_PEN);
		dc.DrawLine(0, height / 2, width, height / 2);
		
		// Draw waveform 
		dc.SetPen(*wxYELLOW_PEN);
		float xScale = (float)width / samples.size();
		for (size_t i = 1; i < samples.size(); i++) {
			dc.DrawLine(
				(i-1) * xScale,
				height / 2 - (samples[i-1] * height / 2),
				i * xScale,
				height / 2 - (samples[i] * height / 2)
			);
		}
	}
};
class MyFrame : public wxFrame {
  public:
    MyFrame() : wxFrame(
		nullptr, 
		wxID_ANY, 
		"Waveform Generator", 
		wxDefaultPosition,
		wxSize(800, 400)) 
	{
		auto panel = new WaveformPanel(this);
		Show(true);
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
