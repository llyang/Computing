#include <wx/sizer.h>
#include <wx/wx.h>

class BasicDrawPane : public wxPanel {
public:
  BasicDrawPane(wxFrame* parent);

  void paintEvent(wxPaintEvent& evt);

  DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp {
private:
  bool OnInit();

  wxFrame* frame;
  BasicDrawPane* drawPane;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxBoxSizer* sizer { new wxBoxSizer { wxHORIZONTAL } };
  frame = new wxFrame { nullptr, -1, wxT("我是谁？我从哪里来？我要去哪里？"),
    wxPoint { 400, 300 }, wxSize { 800, 600 } };

  drawPane = new BasicDrawPane { frame };
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();
  return true;
}

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxFrame* parent)
    : wxPanel { parent }
{
}

void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
  wxPaintDC dc { this };

  // draw some text
  wxFont font;
  font.SetNativeFontInfoUserDesc("Sans 14");
  dc.SetFont(font);
  dc.DrawText(wxT("红圆圈，蓝方块，黑线条"), 100, 400);

  // draw a circle
  dc.SetBrush(*wxRED_BRUSH); // green filling
  dc.SetPen(wxPen { wxColor { 255, 0, 0 }, 1 }); // 5-pixels-thick red outline
  dc.DrawCircle(wxPoint { 200, 100 }, 50 /* radius */);

  // draw a rectangle
  dc.SetBrush(*wxBLUE_BRUSH); // blue filling
  dc.SetPen(wxPen { wxColor { 0, 0, 255 }, 1 }); // 10-pixels-thick pink outline
  dc.DrawRectangle(300, 100, 200, 200);

  // draw a line
  dc.SetPen(wxPen { wxColor { 0, 0, 0 }, 3 }); // black line, 3 pixels thick
  dc.DrawLine(500, 500, 700, 300); // draw line across the rectangle
}

