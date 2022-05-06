#include "Engine.h"
#include <stdlib.h>
#include <memory.h>

#include "wall.h"
#include "platform.h"
#include "color.h"
#include "ball.h"

//static std::unique_ptr<Wall> leftUWall; // what?
static Wall* leftWall;
static Wall* rightWall;
static Wall* topWall;
static Platform* platform;
static Ball* ball;

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()



// initialize game data in this function
void initialize()
{
    const int wallThickness = 15;
    leftWall = new Wall(0, wallThickness, true);
    rightWall = new Wall(SCREEN_WIDTH - wallThickness, wallThickness, true);
    topWall = new Wall(0, wallThickness, false);

    platform = new Platform(60, 20);
    ball = new Ball(10);
    platform->attachBall(ball);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    if (is_mouse_button_pressed(0)) {
        platform->detachBall();
    }
    platform->update(leftWall->b.p1.x, rightWall->b.p0.x, get_cursor_x());
    ball->collide(topWall->b, false, false);
    ball->collide(leftWall->b, false, false);
    ball->collide(rightWall->b, false, false);
    ball->collide(platform->b, true, true);
    bool outOfBounds = ball->update(dt);

    if (outOfBounds) {
        platform->attachBall(ball);
    }

    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    leftWall->draw();
    rightWall->draw();
    topWall->draw();
    platform->draw();
    ball->draw();
    
}

// free game data in this function
void finalize()
{
    delete leftWall;
    delete rightWall;
    delete topWall;
    delete platform;
    delete ball;
}
