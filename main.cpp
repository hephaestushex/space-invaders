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

Player player(0, 0, 0, 0, 0);
vector<Enemy> enemies;
vector<Laser> firedLaser;
float frameIndex = 1;
float levelEnemies = 30;


void setup()
{
    player = Player(GetScreenWidth() / 2, GetScreenHeight() - GetScreenHeight() / 4, 200, 32, 32);
    for(float i = 0; i <= levelEnemies; i++)
    {
        enemies.push_back(Enemy(rand() % 800, rand() % 200, 300, 32, 32));
    }
}

void checkToEraseLaser(int point)
{
    if (firedLaser[point].y <= 0 )
    {
        firedLaser.erase(firedLaser.begin() + point);
        checkToEraseLaser(point);
    } 
}

void checkToEraseEnemy(int point)
{
    if (enemies[point].y >= 450)
    {
        enemies.erase(enemies.begin() + point);
        checkToEraseEnemy(point);
    } 
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

    // Main game loop
    while (!WindowShouldClose)    // Detect window close button or ESC key
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

        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        {
            firedLaser.push_back(Laser(player.x, player.y - 32, 300, 8));
        }
        
        //Logic

        for(unsigned long long int i=0; i < firedLaser.size(); i++)
        {
            if (firedLaser[i].y > 0 )
            {
                firedLaser[i].y -= firedLaser[i].speed * GetFrameTime();
            }
            else if (firedLaser[i].y <= 0)
            {
                checkToEraseLaser(i);                
            }
        }

        frameIndex += 1;
        //cout << frameIndex << endl;
        //cout << enemies.size() << endl;

        for(unsigned long long int i=0; i < enemies.size(); i++)
        {
            if (enemies[i].y > 0 )
            {
                enemies[i].y += enemies[i].speed * GetFrameTime();
            }
            else if (enemies[i].y >= 450)
            {
                checkToEraseEnemy(i);
                //cout << "delete\n";               
            }
            cout << enemies[i].y << endl;

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
                if (firedLaser[i].y > 0)
                {
                    firedLaser[i].draw();
                }
            }

            for(unsigned long long int i=0; i < enemies.size(); i++)
            {
                if (enemies[i].y > 10)
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
