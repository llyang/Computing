#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <string>

using namespace std;

struct myWindow : Fl_Window
{
  myWindow(int w, int h, const string& title)
      : Fl_Window(w, h, title.c_str())
  {
    color(FL_WHITE);
    resizable(this);
    show();
  }

  void draw() override {
    Fl_Window::draw();

    fl_color(FL_BLUE);

    fl_line_style(FL_SOLID, 5);
    fl_line(100, 100, 200, 200);
    fl_rectf(100, 300, 100, 100);

    fl_font(FL_HELVETICA, 24);
    fl_draw("I don't know what to say", 300, 500);
  }

};

int main (int argc, char** argv)
{
  myWindow win {800, 600, "What?"};
  return Fl::run();
}
