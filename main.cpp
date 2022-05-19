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
bool waveCleared = false;

Player player(0, 0, 0, 0, 0);

vector<Enemy> enemies;
vector<Laser> firedLaser;

float frameIndex = 1;
float levelEnemies = 20;
float levelLasers = 20;
float level = 1;
float levelUp = 0;

void setup()
{
    for (int i = 0; i <= levelEnemies; i++)
    {
        enemies.push_back(Enemy(rand() % 800, rand() % 50, rand() % 100, 32, 32, 0));
    }

    for (int i = 0; i <= levelLasers; i++)
    {
        firedLaser.push_back(Laser(0, 0, 0, 0));
    }
}

/*void eraseLaser(int point)
{
    firedLaser.erase(firedLaser.begin() + point);
    eraseLaser(point);
}*/

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
        if (waveCleared == true)
        {
            level++;
            if (level >= 4)
            {
                gameOver = true;
            }
            
            else if (level < 4)
            {
                levelEnemies = level * 10 * 2;
                levelLasers = level * 10 * 2;
                levelUp = 1;
            }
        }

        frameIndex++;
        waveCleared = true;

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
                if (enemies[i].y > 0 && enemies[i].hit == 0)
                {
                    enemies[i].y += enemies[i].speed * GetFrameTime();
                }
                
                if (enemies[i].y > 600)
                {
                    enemies[i].y = 10;               
                }

                if (levelUp == 1)
                {
                    enemies[i].hit = 0;
                    enemies[i].y = 10;
                    enemies[i].x = rand() % 800;
                    enemies[i].speed = rand() % 100;
                }
                
                if (enemies[i].y > 0 && enemies[i].hit == 0)
                {
                    enemies[i].draw();
                    waveCleared = false;
                }
                //cout << enemies[i].hit;
            }

            for (unsigned long long int x=0; x < levelLasers; x++)
            {
                for (unsigned long long int y=0; y < levelLasers; y++)
                {
                    if (CheckCollisionCircleRec(firedLaser[y].center, firedLaser[y].radius, enemies[x].getRect()))
                    {
                        enemies[x].hit = 1;
                        //cout << "ouch for enemy number " << x << "\n";
                    }

                    if (CheckCollisionRecs(player.getRect(), enemies[x].getRect()))
                    {
                        gameOver = true;
                    }
                    //cout << "Collision detected for " << x << " comparing to " << y << "\n";
                }
            }
            cout << waveCleared << "\n";
            levelUp = 0;
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
