#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "Graph_lib/Graph.h"

constexpr int window_width { 800 };
constexpr int window_height { 600 };
constexpr int blocks_per_row { 10 };
constexpr int block_width { window_width / blocks_per_row };
constexpr int block_height { 20 };

constexpr int fps { 60 };

constexpr Graph_lib::Color background { Graph_lib::Color::white };

#endif
