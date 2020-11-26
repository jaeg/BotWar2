//Using SDL and standard IO
#include "bot.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool paused = true;

int main( int argc, char* args[] )
{
    printf( "Start!\n" );
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    SDL_Renderer* renderer = NULL;

    Bot *bot = new Bot(WORLD_WIDTH/2,WORLD_HEIGHT/2);

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
           else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            SDL_Event e;
            bool quit = false;
            time_t tick;
            time(&tick);
            while (!quit){
                while (SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit = true;
                    }
                    if (e.type == SDL_KEYDOWN){
                        const Uint8 *state = SDL_GetKeyboardState(NULL); 
                        if ( state[SDL_SCANCODE_SPACE] ) { 
                            paused = !paused;
                            printf("Paused %i\n", paused);
                        }
                        if ( state[SDL_SCANCODE_ESCAPE] ) {
                            quit = true;
                        }
                        
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN){
                        int mX = 0;
                        int mY = 0;
                        if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                            printf("Clicked\n");
                            int cellX = mX/32;
                            int cellY = mY/32;

                            int cell = bot->brain->GetBrainCell(cellX,cellY);
                            if (cell == CELL_DEAD) {
                                bot->brain->ChangeBrainCell(cellX,cellY,CELL_TRACK);
                            }

                            if (cell == CELL_TRACK) {
                                bot->brain->ChangeBrainCell(cellX,cellY,CELL_HEAD);
                            }

                            if (cell == CELL_HEAD) {
                                bot->brain->ChangeBrainCell(cellX,cellY,CELL_TAIL);
                            }

                            if (cell == CELL_TAIL) {
                                bot->brain->ChangeBrainCell(cellX,cellY,CELL_MOTOR1);
                            }

                            if (cell == CELL_MOTOR1) {
                                bot->brain->ChangeBrainCell(cellX,cellY,CELL_MOTOR2);
                            }

                            if (cell == CELL_MOTOR2) {
                                bot->brain->ChangeBrainCell(cellX,cellY,CELL_DEAD);
                            }

                            printf("%i,%i\n",cellX,cellY);
                        }
                    }
                }

                // clear the screen
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                time(&tick);
                if (!paused) {
                    bot->Update(tick);
                }
                
                //Draw brain grid
                for (int x = 0; x < BRAIN_SIZE; x++){
                    for (int y = 0; y < BRAIN_SIZE; y++) {
                        int cell = bot->brain->GetBrainCell(x,y);
                        switch (cell) {
                            case CELL_DEAD:
                                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (solid black)
                                break;
                            case CELL_HEAD:
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // the rect color (solid red)
                                break;
                            case CELL_TAIL:
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // the rect color (solid blue)
                                break;
                            case CELL_TRACK:
                                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // the rect color (solid green)
                                break;
                            case CELL_MOTOR1:
                                SDL_SetRenderDrawColor(renderer, 125, 125, 0, 255); // the rect color (solid green)
                                break;
                            case CELL_MOTOR2:
                                SDL_SetRenderDrawColor(renderer, 125, 0, 125, 255); // the rect color (solid green)
                                break;
                        }
                        SDL_Rect rect = SDL_Rect(); // the rectangle
                        rect.x = x * 32;
                        rect.y = y * 32;
                        rect.h = 31;
                        rect.w = 31;
                        SDL_RenderFillRect(renderer, &rect);
                    }
                }

                //Draw arena
                SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
                SDL_Rect rect = SDL_Rect(); // the rectangle
                rect.x = BRAIN_SIZE * 32 + 32;
                rect.y = 0;
                rect.h = WORLD_HEIGHT;
                rect.w = WORLD_WIDTH;
                SDL_RenderFillRect(renderer, &rect);

                //Draw robot
                SDL_SetRenderDrawColor(renderer, 255, 9, 9, 255);
                rect = SDL_Rect(); // the rectangle
                rect.x = BRAIN_SIZE * 32 + 32 + bot->x-8;
                rect.y = bot->y-8;
                rect.h = 16;
                rect.w = 16;
                SDL_RenderFillRect(renderer, &rect);

                //Draw direction pointer of robot
                int eyeX = bot->x + cos(RADIANS(bot->direction)) * 3.0f;
                int eyeY = bot->y + sin(RADIANS(bot->direction)) * 3.0f;
                SDL_SetRenderDrawColor(renderer, 0, 255, 9, 255);
                rect = SDL_Rect(); // the rectangle
                rect.x = BRAIN_SIZE * 32 + 32 + eyeX-4;
                rect.y = eyeY-4;
                rect.h = 8;
                rect.w = 8;
                SDL_RenderFillRect(renderer, &rect);
                

                // flip the backbuffer
                // this means that everything that we prepared behind the screens is actually shown
                SDL_RenderPresent(renderer);
                SDL_Delay(100);
            }
        }
    }
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    printf( "End\n" );
    return 0;
}