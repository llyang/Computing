#include "GUI.h"
#include "Point.h"
#include "Window.h"

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

class Simple_window : public Graph_lib::Window {

public:
  Simple_window(Graph_lib::Point xy, int w, int h, const std::string &title)
      : Graph_lib::Window{xy, w, h, title},
        quit_button{Graph_lib::Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit},
        next_button{Graph_lib::Point{x_max() - 70, 20}, 70, 20, "Next",
                    cb_next},
        next_pushed{false} {
    attach(quit_button);
    attach(next_button);
  }

  void wait_for_next() {
    while (!next_pushed && Fl::wait())
      ;
    next_pushed = false;
    Fl::redraw();
  }

private:
  Graph_lib::Button quit_button;
  Graph_lib::Button next_button;

  bool next_pushed;

  // callback for quit_button
  static void cb_quit(void *, void *pw) {
    static_cast<Simple_window *>(pw)->quit();
  }

  void quit() { hide(); }

  // callback for next_button
  static void cb_next(void *, void *pw) {
    static_cast<Simple_window *>(pw)->next();
  }

  void next() { next_pushed = true; }
};

