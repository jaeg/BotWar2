#include "brain.h"

void Brain::Update()
{
    this->Motor1 = false;
    this->Motor2 = false;
    int newGrid[BRAIN_SIZE][BRAIN_SIZE];
    //Blank out new grid... gotta be a better way.
    for (int x = 0; x < BRAIN_SIZE; x++)
    {
        for (int y = 0; y < BRAIN_SIZE; y++)
        {
            newGrid[x][y] = -1;
        }
    }

    //Process the simulation rules
    for (int x = 0; x < BRAIN_SIZE; x++)
    {
        for (int y = 0; y < BRAIN_SIZE; y++)
        {
            if (newGrid[x][y] == -1) {
                newGrid[x][y] = this->grid[x][y];
            }
            switch (this->grid[x][y])
            {
            case CELL_DEAD:
                break;
            case CELL_HEAD:
                for (int sx = x-1; sx < x+2; sx++)
                {
                    for (int sy = y -1; sy < y + 2; sy++)
                    {
                        if (sx >= 0 && sx < BRAIN_SIZE && sy >= 0 && sy < BRAIN_SIZE) {
                            if (this->grid[sx][sy] == CELL_TRACK) {
                                newGrid[sx][sy] = CELL_HEAD;
                            }    

                            if (this->grid[sx][sy] == CELL_MOTOR1) {
                                printf("Motor 1 activated\n");
                                this->Motor1 = true;
                            }   

                            if (this->grid[sx][sy] == CELL_MOTOR2) {
                                printf("Motor 2 activated\n");
                                this->Motor2 = true;
                            }                            
                        }
                    }
                }
                newGrid[x][y] = CELL_TAIL;
                break;
            case CELL_TAIL:
                newGrid[x][y] = CELL_TRACK;
                break;
            case CELL_TRACK:
                break;
            }
        }
    }

    //Copy grid.
    for (int x = 0; x < BRAIN_SIZE; x++)
    {
        for (int y = 0; y < BRAIN_SIZE; y++)
        {
            this->grid[x][y] = newGrid[x][y];
        }
    }
}

void Brain::Clear()
{
    for (int i = 0; i < BRAIN_SIZE; i++)
    {
        for (int j = 0; j < BRAIN_SIZE; j++)
        {
            this->grid[i][j] = CELL_DEAD;
        }
    }
}

void Brain::ChangeBrainCell(int x, int y, int value)
{
    if (x >= BRAIN_SIZE || y >= BRAIN_SIZE)
    {
        printf("Invalid brain cell location\n");
    }
    this->grid[x][y] = value;
}

int Brain::GetBrainCell(int x, int y)
{
    if (x >= BRAIN_SIZE || y >= BRAIN_SIZE)
    {
        printf("Invalid brain cell location\n");
        return -1;
    }
    return this->grid[x][y];
}