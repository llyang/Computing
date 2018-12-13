#include <chrono>
#include <future>
#include <random>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

#include "GUI.h"
#include "Graph.h"
#include "Window.h"

using std::string;

using Graph_lib::Color;
using Graph_lib::Point;

class My_window : public Graph_lib::Window {

public:
  My_window(Point xy, int w, int h, const string& title);

private:
  Graph_lib::Button quit_button;

  Graph_lib::Button joke_button;
  Graph_lib::Text joke_text;
  std::future<string> output_joke;

  Graph_lib::Button quiz_button;
  Graph_lib::Text quiz_text;
  std::future<string> output_quiz;

  // callback for quit_button
  static void cb_quit(void*, void* pw)
  {
    static_cast<My_window*>(pw)->quit();
  }

  void quit() { hide(); }

  // callback for joke_button
  static void cb_joke(void*, void* pw)
  {
    auto p = static_cast<My_window*>(pw);
    p->output_joke = std::async(std::launch::async, &My_window::get_joke, p);
  }

  static void cb_joke_begin(void* pw)
  {
    auto p = static_cast<My_window*>(pw);
    p->joke_button.deactivate();
    p->joke_text.set_label("Working...");
    Fl::redraw();
  }

  static void cb_joke_end(void* pw)
  {
    auto p = static_cast<My_window*>(pw);
    p->joke_text.set_label(p->output_joke.get());
    p->joke_button.activate();
    Fl::redraw();
  }

  // callback for quiz_button
  static void cb_quiz(void*, void* pw)
  {
    auto p = static_cast<My_window*>(pw);
    p->output_quiz = std::async(std::launch::async, &My_window::get_quiz, p);
  }

  static void cb_quiz_begin(void* pw)
  {
    auto p = static_cast<My_window*>(pw);
    p->quiz_button.deactivate();
    p->quiz_text.set_label("Working...");
    Fl::redraw();
  }

  static void cb_quiz_end(void* pw)
  {
    auto p = static_cast<My_window*>(pw);
    p->quiz_text.set_label(p->output_quiz.get());
    p->quiz_button.activate();
    Fl::redraw();
  }

  string get_joke();

  string get_quiz();
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Graph_lib::Window { xy, w, h, title }
    , quit_button { Point { x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
    , joke_button { Point { 50, 50 }, 80, 20, "Joke", cb_joke }
    , joke_text { Point { 50, 100 }, "" }
    , quiz_button { Point { 50, 150 }, 80, 20, "Quiz", cb_quiz }
    , quiz_text { Point { 50, 200 }, "" }
{
  attach(quit_button);
  attach(joke_button);
  joke_text.set_font(Graph_lib::Font::times_bold);
  joke_text.set_font_size(20);
  joke_text.set_color(Color::dark_red);
  attach(joke_text);
  attach(quiz_button);
  quiz_text.set_font(Graph_lib::Font::times_bold);
  quiz_text.set_font_size(20);
  quiz_text.set_color(Color::dark_red);
  attach(quiz_text);
}

string My_window::get_joke()
{
  static const std::vector<string> jokes {
    "Newton's first law: bodies in motion remain in motion, and bodies at rest stay in bed unless their mothors call them to get up",
    "There are only 10 kinds of people in this world: those who know binary and those who don’t"
  };
  Fl::awake(cb_joke_begin, this);
  std::this_thread::sleep_for(std::chrono::seconds { 10 });
  Fl::awake(cb_joke_end, this);
  static std::random_device rd;
  static std::default_random_engine ran(rd());
  static std::uniform_int_distribution<int> ui(0, jokes.size() - 1);
  return jokes[ui(ran)];
}

string My_window::get_quiz()
{
  static const std::vector<string> quizzes {
    "How many steps does it take to put an elephant into a refrigerator?",
    "You wrote so many lines of code. Do you have a girlfriend?",
    "Can you solve the Riemann hypothesis?"
  };
  Fl::awake(cb_quiz_begin, this);
  std::this_thread::sleep_for(std::chrono::seconds { 10 });
  Fl::awake(cb_quiz_end, this);
  static std::random_device rd;
  static std::default_random_engine ran(rd());
  static std::uniform_int_distribution<int> ui(0, quizzes.size() - 1);
  return quizzes[ui(ran)];
}

int main()
{
  My_window win { Point { 100, 100 }, 1200, 400, "Silly" };

  Fl::lock();

  return Graph_lib::gui_main();
}

