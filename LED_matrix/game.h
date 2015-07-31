//Motion_Controlled_Pong to play Pong with your Smartphone and a Raspberry Pi.
//Copyright (C) 2015  Dominik Meier (XPerianer) <hiscore.pressthebutton@hotmail.de>

//This program is free software: you can redistribute it and/or modify
//the Free Software Foundation, either version 3 of the License, or
//it under the terms of the GNU General Public License as published by
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "led-matrix.h"
#include "graphics.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

using namespace rgb_matrix;

class Ball{
  public:
  double x,y;
  double old_x,old_y;
  double vx, vy;
  int bounces;
  Color color;
public:
  void draw(Canvas *canvas);
  void move(std::chrono::duration<double> duration);
  void reset(int display_width, int display_height);
  Ball(int display_width, int display_height);
};

class Paddle{

public:
  int position;
  int width,height;
  int x,y;
private:
  Color color;

public:
   void draw(Canvas *canvas);
   Paddle(int px, int py);
};

class Game{

private:
  int width,height;
  Color background_color;
  Color foreground_color;
  Ball ball;
  int leftPoints,rightPoints;
  int animationStatus;
  //Needed for RGB_Panel
  Canvas *canvas;
  GPIO io;
  Font font;
public:
  Paddle rightPaddle;
  Paddle leftPaddle;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> duration;
  void reset();
  void draw();
  void update();
  void ballCollision();
  void animateColors();
  void destroy();
  Game();

};
