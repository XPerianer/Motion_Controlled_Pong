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
