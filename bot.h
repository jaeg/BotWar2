#ifndef BOT_H
#define BOT_H

#include "brain.h"
#include <time.h>

#define RADIANS(a) (a * 3.14f / 180.0f)
const int WORLD_WIDTH = 200;
const int WORLD_HEIGHT = 200;

class Bot {
    public:
    float x;
    float y;
    int direction;
    double velocity;
    time_t myTick;
    Brain *brain;
    Bot(int x, int y);
    void LeftMotor();
    void RightMotor();
    void Update(time_t);
};

#endif