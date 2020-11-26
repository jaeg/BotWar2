#ifndef BRAIN_H
#define BRAIN_H

#include <stdio.h>

const int BRAIN_SIZE = 10;

const int CELL_DEAD = 0;
const int CELL_HEAD = 1;
const int CELL_TAIL = 2;
const int CELL_TRACK = 3;
const int CELL_MOTOR1 = 4;
const int CELL_MOTOR2 = 5;

class Brain {
    public:
        void Clear();
        void ChangeBrainCell(int x, int y, int value);
        int GetBrainCell(int x, int y);
        void Update();
        Brain() {
            for (int i = 0; i < BRAIN_SIZE; i++){
                for (int j = 0; j < BRAIN_SIZE; j++) {
                    printf( "%i", this->grid[i][j] );
                }
                printf( "\n" );
            }
        };
        bool Motor1;
        bool Motor2;
    private:
        int grid[BRAIN_SIZE][BRAIN_SIZE];
};
#endif