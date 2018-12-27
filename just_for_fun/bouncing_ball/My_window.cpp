#include <stdexcept>
#include <string>

#include "My_window.h"
#include "constants.h"

using Graph_lib::Color;
using Graph_lib::Point;

My_window::My_window()
    : Graph_lib::Window { window_width, window_height, "ball", false }
    , scene_title {}
    , scene_play {}
    , current_scene { &scene_title }
{
  set_background_color(background);
  current_scene->attach_to_window(*this);
  Fl::add_timeout(1. / fps, cb_timeout, this);
}

void My_window::switch_to(Scene* s)
{
  current_scene->detach_from_window();
  s->reset();
  s->attach_to_window(*this);
  current_scene = s;
}

void My_window::start()
{
  switch_to(&scene_play);
  keydown_handlers.clear();
  keydown_handlers["r"] = [this]() { title(); };
}

void My_window::title()
{
  switch_to(&scene_title);
  keydown_handlers.clear();
}

void My_window::loop()
{
  current_scene->update();
  redraw();
  Fl::repeat_timeout(1. / fps, cb_timeout, this);
}

int My_window::handle(int event)
{
  int ret { Fl_Window::handle(event) };
  if (ret == 1)
    return ret;
  switch (event) {
  case FL_FOCUS:
  case FL_UNFOCUS:
    ret = 1;
    break;
  // TODO: need to deal with cases where two keys are pressed at the same time
  case FL_KEYDOWN: {
    std::string key = Fl::event_text();
    if (handle_keydown(key))
      ret = 1;
    else if (current_scene->handle_keydown(key))
      ret = 1;
    break;
  }
  case FL_KEYUP: {
    std::string key = Fl::event_text();
    if (current_scene->handle_keyup(key))
      ret = 1;
    break;
  }
  default:
    break;
  }
  return ret;
}

bool My_window::handle_keydown(const std::string& key)
{
  try {
    keydown_handlers.at(key)();
    return true;
  } catch (std::out_of_range&) {
    return false;
  }
}