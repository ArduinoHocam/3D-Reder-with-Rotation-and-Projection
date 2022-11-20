#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <Eigen/Dense>

#define SCR_WDT 640
#define SCR_HGT 480

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;


constexpr float degreeToRadians(int degree){
    return static_cast<float>(degree*M_PI/180.0);
}


Eigen::MatrixXd getRotX(int theta){
    Eigen::MatrixXd RotX(3,3);
    RotX <<
            1.0, 0.0, 0.0,
            0.0, cos(degreeToRadians(theta)), -sin(degreeToRadians(theta)),
            0.0, sin(degreeToRadians(theta)), cos(degreeToRadians(theta));
    return RotX;
}
Eigen::MatrixXd getRotY(int theta){
Eigen::MatrixXd RotY(3,3);
RotY <<
        cos(degreeToRadians(theta)), 0.0, sin(degreeToRadians(theta)), 
        0.0, 1.0, 0.0,
        -sin(degreeToRadians(theta)), cos(degreeToRadians(theta)), 0.0;
    return RotY;
}
Eigen::MatrixXd getRotZ(int theta){
Eigen::MatrixXd RotZ(3,3);
RotZ <<
        cos(degreeToRadians(theta)), -sin(degreeToRadians(theta)), 0.0,
        sin(degreeToRadians(theta)), cos(degreeToRadians(theta)), 0.0,
        0.0, 0.0, 0.0;
    return RotZ;
}

int center_x = SCR_CEN_X;
int center_y = SCR_CEN_Y;
int theta = 15;
int radius = 60;
int end_x = center_x;
int end_y = center_y;

int finalpoints2D [8][2] = {0};


int SCALE  = 32;
int increment_amount = 1;
int main(int argc, char *argv[])
{
Eigen::MatrixXd points3D(8,3);
points3D <<
        -1, -1, 1,
        1, -1, 1,
        1, 1, 1,
        -1, 1, 1,

        -1, -1, -1,
        1, -1, -1,
        1, 1, -1,
        -1, 1, -1;

Eigen::MatrixXd projectionM(3,3);
projectionM <<
        1, 0, 0,
        0, 1, 0,
        0, 0, 0;
    if (SDL_Init(SDL_INIT_VIDEO) == 0){
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        if (SDL_CreateWindowAndRenderer(SCR_WDT, SCR_HGT, 0, &window, &renderer) == 0){
            SDL_bool done = SDL_FALSE;
            while (!done){
                SDL_Event event;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                for(int i=0; i<8;i++){
                    Eigen::Vector3d pointsVec(points3D.coeff(i, 0), points3D.coeff(i, 1), points3D.coeff(i, 2));

                    // 3D -  rotation
                    Eigen::Vector3d rotated = getRotX(theta)*pointsVec;
                    rotated = getRotY(theta)*rotated;
                    
                    //project
                    auto projected2d  = projectionM * rotated;
                    finalpoints2D[i][0] = projected2d[0]*SCALE+SCR_CEN_X;
                    finalpoints2D[i][1] = projected2d[1]*SCALE+SCR_CEN_Y;
                
                    SDL_RenderDrawPoint(renderer, projected2d[0]*SCALE+SCR_CEN_X, projected2d[1]*SCALE+SCR_CEN_Y);
                    
                }                
                SDL_RenderDrawLine(renderer, finalpoints2D[0][0], finalpoints2D[0][1], finalpoints2D[1][0], finalpoints2D[1][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[1][0], finalpoints2D[1][1], finalpoints2D[2][0], finalpoints2D[2][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[2][0], finalpoints2D[2][1], finalpoints2D[3][0], finalpoints2D[3][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[3][0], finalpoints2D[3][1], finalpoints2D[0][0], finalpoints2D[0][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[4][0], finalpoints2D[4][1], finalpoints2D[5][0], finalpoints2D[5][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[5][0], finalpoints2D[5][1], finalpoints2D[6][0], finalpoints2D[6][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[6][0], finalpoints2D[6][1], finalpoints2D[7][0], finalpoints2D[7][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[7][0], finalpoints2D[7][1], finalpoints2D[4][0], finalpoints2D[4][1]);

                SDL_RenderDrawLine(renderer, finalpoints2D[0][0], finalpoints2D[0][1], finalpoints2D[4][0], finalpoints2D[4][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[1][0], finalpoints2D[1][1], finalpoints2D[5][0], finalpoints2D[5][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[3][0], finalpoints2D[3][1], finalpoints2D[7][0], finalpoints2D[7][1]);
                SDL_RenderDrawLine(renderer, finalpoints2D[2][0], finalpoints2D[2][1], finalpoints2D[6][0], finalpoints2D[6][1]);

                
                SDL_RenderPresent(renderer);

                theta++;
                SDL_Delay(10);
                while (SDL_PollEvent(&event)){
                    if (event.type == SDL_QUIT){
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer){
            SDL_DestroyRenderer(renderer);
        }
        if (window){
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}
