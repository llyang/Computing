#include <iostream>
#include <stdexcept>

#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"

#include "My_window.h"
#include "Scene.h"

using Graph_lib::Button;
using Graph_lib::Point;

Scene::Scene()
    : win { nullptr }
{
}

Scene::~Scene()
{
  for (auto p : widgets)
    delete p;
}

void Scene::attach_to_window(Graph_lib::Window& w)
{
  if (win && win != &w) {
    throw std::runtime_error { "cannot attach to a different window" };
  }
  win = &w;
  for (auto p : shapes)
    win->attach(*p);
  for (auto p : widgets)
    win->attach(*p);
}

void Scene::detach_from_window()
{
  win->detach_all_shapes();
  for (auto p : widgets)
    win->detach(*p);
}

Scene_title::Scene_title()
    : Scene {}
    , image { Point { (window_width - 360) / 2, (window_height - 480) / 2 - 50 }, "blue.jpg" }
{
  widgets.push_back(new Button { Point { 350, 530 }, 100, 40, "start",
      [](void*, void* pw) { static_cast<My_window*>(pw)->start(); }, 20 });
  shapes.push_back(&image);
}

Scene_play::Scene_play()
    : Scene {}
    , keydown_handlers {
      { "a", [this]() { paddle.set_speed(-1); } },
      { "d", [this]() { paddle.set_speed(1); } }
    }
    , keyup_handlers { { "a", [this]() { paddle.set_speed(0); } }, { "d", [this]() { paddle.set_speed(0); } } }
{
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < blocks_per_row; ++col) {
      blocks.push_back(new Block { col * block_width, row * block_height });
      shapes.push_back(blocks[blocks.size() - 1]->get_shape());
    }
  }
  shapes.push_back(paddle.get_shape());
  shapes.push_back(ball.get_shape());
}

Scene_play::~Scene_play()
{
  for (auto p : blocks)
    delete p;
}

void Scene_play::reset()
{
  paddle.reset();
  ball.reset();
  for(auto p : blocks)
    p->reset();
  // resetting objects may invalidate the pointers to shapes
  // if so, we need to setup the vector again
  // shapes.clear();
  // shapes.push_back(...);
}

void Scene_play::update()
{
  ball.move();
  paddle.move();
  ball.collide(paddle);
  for (auto b : blocks) {
    if (b->is_alive())
      ball.collide(*b);
  }
}

bool Scene_play::handle_keydown(const std::string& key)
{
  auto it = keydown_handlers.find(key);
  if (it != keydown_handlers.end()) {
    (it->second)();
    return true;
  } else {
    return false;
  }
}

bool Scene_play::handle_keyup(const std::string& key)
{
  auto it = keyup_handlers.find(key);
  if (it != keyup_handlers.end()) {
    (it->second)();
    return true;
  } else {
    return false;
  }
}