#ifndef _SCENE_H
#define _SCENE_H

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"

#include "Ball.h"
#include "Block.h"
#include "Paddle.h"

class Scene {
public:
  Scene();

  virtual void reset() {}

  virtual void update() {}

  virtual ~Scene();

  virtual void attach_to_window(Graph_lib::Window& w);
  virtual void detach_from_window();

  virtual bool handle_keydown(const std::string& key) { return false; }
  virtual bool handle_keyup(const std::string& key) { return false; }

protected:
  Graph_lib::Window* win;
  std::vector<const Graph_lib::Shape*> shapes;
  std::vector<Graph_lib::Widget*> widgets;
};

class Scene_title : public Scene {
public:
  Scene_title();

private:
  Graph_lib::Image image;
};

class Scene_play : public Scene {
public:
  Scene_play();
  ~Scene_play() override;

  void reset() override;
  void update() override;

  bool handle_keydown(const std::string& key) override;
  bool handle_keyup(const std::string& key) override;

private:
  Ball ball;
  Paddle paddle;
  std::vector<Block*> blocks;
  std::map<std::string, std::function<void()>> keydown_handlers;
  std::map<std::string, std::function<void()>> keyup_handlers;
};

#endif
