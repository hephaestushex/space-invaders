#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "Player.hpp"
#include "Laser.hpp"
#include "Enemy.hpp"

using namespace std;

bool gameOver = false;
bool enemyKilled = false;

Player player(0, 0, 0, 0, 0);

vector<Enemy> enemies;
vector<Laser> firedLaser;

float frameIndex = 1;
float levelEnemies = 10;
float levelLasers = 20;

unsigned long long int aliasI = 0;

int i = 0;

void setup()
{
    for (i = 0; i <= levelEnemies; i++)
    {
        enemies.push_back(Enemy(rand() % 800, rand() % 50, rand() % 100, 32, 32, 0));
    }

    for (i = 0; i <= levelLasers; i++)
    {
        firedLaser.push_back(Laser(0, 0, 0, 0));
    }
}

void eraseLaser(int point)
{
    firedLaser.erase(firedLaser.begin() + point);
    eraseLaser(point);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(800, 600, "Space Invaders");

    SetTargetFPS(60);               // Set our game to run at 50 frames-per-second

    srand(time(0));                 // Seeds the pseudorandom number generator

    //--------------------------------------------------------------------------------------

    setup();                        // Setup game variables
    player = Player(GetScreenWidth() / 2, GetScreenHeight() - GetScreenHeight() / 4, 200, 32, 32);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Controls
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            player.x -= player.speed * GetFrameTime();
        }
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            player.x += player.speed * GetFrameTime();
        }

        
        
        //Logic

        frameIndex++;

        for(unsigned long long int i=0; i < firedLaser.size(); i++)
        {
            aliasI = i;
            
            
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawFPS(10, 10);

            if (IsKeyPressed(KEY_E))
            {
                player.e = !player.e;
            }

            player.draw();

            for(unsigned long long int i=0; i < firedLaser.size(); i++)
            {
                if (firedLaser[i].y > 0 )
                {
                    firedLaser[i].y -= firedLaser[i].speed * GetFrameTime();
                }
                else if (firedLaser[i].y < 0)
                {
                    firedLaser[i].y = player.y;
                    firedLaser[i].x = player.x;
                }

                if (frameIndex == 10 && firedLaser[i].speed == 0)
                {
                    firedLaser[i] = Laser(player.x, player.y - 16, 300, 8);
                    frameIndex = 0;
                }
                
                if (firedLaser[i].y > 0)
                {
                    firedLaser[i].draw();
                }
            }

            for(unsigned long long int i=0; i < enemies.size(); i++)
            {
                if (enemies[i].y > 0 )
                {
                    enemies[i].y += enemies[i].speed * GetFrameTime();
                }
                
                if (enemies[i].y >= 600)
                {
                    enemies[i].y = 0;               
                }
                
                if (enemies[i].y > 0 && enemies[i].hit == 0)
                {
                    enemies[i].draw();
                }
            }  
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
