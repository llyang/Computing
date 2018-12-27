#ifndef _MY_WINDOW_H
#define _MY_WINDOW_H

#include <functional>
#include <map>
#include <string>

#include "Graph_lib/Window.h"

#include "Scene.h"

class My_window : public Graph_lib::Window {

public:
  My_window();

  ~My_window() override = default;

  void switch_to(Scene* s);

  void start();

  void title();

  void loop();

  static void cb_timeout(void* pw) { static_cast<My_window*>(pw)->loop(); }

  int handle(int event) override;

  bool handle_keydown(const std::string& key);

private:
  Scene_title scene_title;
  Scene_play scene_play;
  Scene* current_scene;
  std::map<std::string, std::function<void()>> keydown_handlers;
};

#endif
