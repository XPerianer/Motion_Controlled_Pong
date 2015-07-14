#include "game.h"

Ball::Ball(int display_width,int display_height) : color(0,0,255){ //initalise
  reset(display_width,display_height);
}

void Ball::reset(int display_width, int display_height){
  x = display_width/2;
  y = display_height/2;
  old_x = display_width/2;
  old_y = display_height/2;
  vx = 5; // in px per second
  vy = 0; //in px per second
  bounces = 0;
}

void Ball::draw(Canvas *canvas){
  DrawCircle(canvas,x,y,0,color);
}

void Ball::move(std::chrono::duration<double> duration){
  old_x = x;
  old_y = y;
  x += vx * duration.count();
  y += vy * duration.count();
}

Paddle::Paddle(int px, int py) : color(0,255,0){

  width = 1;
  height = 10;
  x = px;
  y = py;
  position = 500;
}

void Paddle::draw(Canvas *canvas){
  y = ((double)31/1000*position) - ((double)height /1000*position);
  DrawLine(canvas, x,y,x,y+height,color);
  canvas->SetPixel(x,y,200,0,0);
  canvas->SetPixel(x,y+height,200,0,0);
}

Game::Game(): leftPaddle(1,0), rightPaddle(30,0),ball(32,32), background_color(0,0,0), foreground_color(200,0,0){
   if(!font.LoadFont("../matrix/fonts/4x6.bdf")){
     std::cout << "Error at loading Font File" << std::endl;
   }
    /*
     * Set up GPIO pins. This fails when not running as root.
     */
    std::cout << "Initalisation begins" << std::endl;
    if (!io.Init()){
      std::cout << "Initalisieren fehlgeschlagen" << std::endl;
      }
    /*
     * Set up the RGBMatrix. It implements a 'Canvas' interface.
     */
  int rows = 32;    // A 32x32 display. Use 16 when this is a 16x32 display.
  int chain = 1;    // Number of boards chained together.
  int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
  canvas = new RGBMatrix(&io, rows, chain, parallel);
  width = 32;
  height = 32;
 std::cout << "Initalisation finished" << std::endl;
}

void Game::reset(){
  animationStatus = 0;
  leftPoints = 0;
  rightPoints = 0;
  ball.reset(width,height);
}

void Game::draw(){
  canvas->Fill(background_color.r,background_color.g,background_color.b);
  //Do Score-Display:

  DrawText(canvas,font,6,8,foreground_color,std::to_string(leftPoints).c_str());
  DrawText(canvas,font,23,8,foreground_color,std::to_string(rightPoints).c_str());
  rightPaddle.draw(canvas);
  leftPaddle.draw(canvas);
  ball.draw(canvas);
}

void Game::destroy(){
  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;
}

void Game::update(){
  animateColors();
  if(ball.bounces > 3){
    ball.vx *= 1.2;
    ball.bounces = 0;
  }
  ball.move(duration);
  ballCollision();
  //Check for Points on each side made
  if(ball.x < 0 - abs(ball.vx)){ //Because vx is negative abs() needed here because if the Ball turns it would be a point for the enemy
    rightPoints++;
    ball.x = width /2;
    ball.y = height/2;
    ball.old_x = width/2;
    ball.old_y = height/2;
    ball.vx = -5;
    ball.vy = 0;
  }
  else if(ball.x > 31 + abs(ball.vx)){
    leftPoints++;
    ball.x = width /2;
    ball.y = height/2;
    ball.old_x = width/2;
    ball.old_y = height/2;
    ball.vx = 5;
    ball.vy = 0;
  }
}

void Game::ballCollision(){
  if(ball.y < 0){ //Collision with top and bottom
    ball.old_y = ball.y;
    ball.y = 0;
    ball.vy = -ball.vy;
  }
  else if(ball.y > 31){
    ball.old_y = ball.y;
    ball.y = 31;
    ball.vy = -ball.vy;
  }
  //Collision with Paddles
  if(ball.x < leftPaddle.x + 1 && ball.old_x >= leftPaddle.x + 1) //+1 for the "radius" of the Ball
  {//Ball moved over the Line where it could bounce the Paddle
    double ratio = fabs((ball.old_x -(leftPaddle.x +1))/(ball.x - ball.old_x));//ratio at how near the ball was to the bouncing line
    int ball_bouncing_y = ball.old_y + ratio * ball.vy + 0.5;
    if(ball_bouncing_y >= leftPaddle.y && ball_bouncing_y <= leftPaddle.y + leftPaddle.height){
      ball.x = leftPaddle.x + 1;
      ball.vx = -ball.vx;
      ball.bounces++;
      ball.vy = (rand()%5-2.5); //Random number between -2.5 and 2.5
    }
  } else if (ball.x > rightPaddle.x-1 && ball.old_x <= rightPaddle.x -1){
    double ratio = fabs((ball.old_x -(rightPaddle.x - 1))/(ball.x - ball.old_x));//ratio at how near the ball was to the bouncing line
    int ball_bouncing_y = ball.old_y + ratio * ball.vy + 0.5;
    //For Debug:
    //std::cout << ball_bouncing_y << " " << rightPaddle.y << std::endl;
    if(ball_bouncing_y >= rightPaddle.y && ball_bouncing_y <= rightPaddle.y + rightPaddle.height){
      ball.x = rightPaddle.x - 1;
      ball.vx = -ball.vx;
      ball.bounces++;
      ball.vy = (rand()%5-2.5); //Random number between -2.5 and 2.5
    }
  }
}

void Game::animateColors(){ //Get nice Rainbow Colors
  switch(animationStatus){

    case 0:
      foreground_color.b++;
      if(foreground_color.b >= 255){
        animationStatus++;
      }
      break;
    case 1:
      foreground_color.r--;
      if(foreground_color.r <= 0){
        animationStatus++;
      }
      break;
    case 2:
      foreground_color.g++;
      if(foreground_color.g >= 255){
        animationStatus++;
      }
      break;
    case 3:
        foreground_color.b--;
        if(foreground_color.b <= 0){
          animationStatus=0;
        }
        break;
    case 4:
        foreground_color.r++;
        if(foreground_color.r >= 255){
            animationStatus++;
        }
        break;
    case 5:
        foreground_color.g--;
        if(foreground_color.g <= 0){
          animationStatus = 0;
        }
  }
}
