#include "bot.h"
#include <math.h>


Bot::Bot(int x, int y) {
    this->x = x;
    this->y = y;
    this->brain = new Brain();
    this->brain->Clear();
}

void Bot::Update(time_t tick) {
    //Update brain every second.
    if (difftime(tick, this->myTick) > 0 ) {
        this->brain->Update();
    }
    
    //Engage the brain's outputs
    if (this->brain->Motor1) {
        LeftMotor();
    }

    if (this->brain->Motor2) {
        RightMotor();
    }

    //Wrap direction
    if (this->direction > 360) {
        this->direction -= 360;
    } else if (this->direction < 0) {
        this->direction += 360;
    }

    //Cap velocity
    if (this->velocity > 2) {
        this->velocity = 2;
    } else if (this->velocity < -2) {
        this->velocity = -2;
    }
    
    //Apply forces
    this->x += cos(RADIANS(this->direction)) * (this->velocity * 1.0);
    this->y += sin(RADIANS(this->direction)) * (this->velocity * 1.0);

    //Don't exceed arena
    if (this->x < 0) {
        this->x = 0;
    } else if (this->x > WORLD_WIDTH) {
        this->x = WORLD_WIDTH;
    }

    if (this->y < 0) {
        this->y = 0;
    } else if (this->y > WORLD_HEIGHT) {
        this->y = WORLD_HEIGHT;
    }

    //Apply friction
    if (this->velocity > 0) {
        this->velocity -= 0.5;
    } else if (this->velocity < 0) {
        this->velocity += 0.5;
    }

    //Update tick
    this->myTick = tick;
}

void Bot::LeftMotor() {
    this->direction += 1;

    this->velocity += 0.5f;
}

void Bot::RightMotor() {
    this->direction -= 1;

    this->velocity += 0.5f;
}