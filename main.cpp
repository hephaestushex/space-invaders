#include <iostream>
#include <vector>
#include <time.h>
#include "raylib.h"
#include "Player.hpp"
#include "Laser.hpp"
#include "Enemy.hpp"

using namespace std;

bool gameOver = false;
bool waveCleared = false;

Player player(0, 0, 0, 0, 0);
Laser laser(0, 0, 0, 0);

vector<Enemy> enemies;

float levelEnemies = 20;
float level = 1;

void setup()
{
    for (int i = 0; i <= levelEnemies; i++)
    {
        enemies.push_back(Enemy(rand() % 800, rand() % 50, rand() % 100, 32, 32, 0));
    }
}

void clearEnemies()
{
    
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(800, 600, "Space Invaders");

    SetTargetFPS(60); // Set our game to run at 50 frames-per-second

    srand(time(0)); // Seeds the pseudorandom number generator

    //--------------------------------------------------------------------------------------

    setup(); // Setup game variables
    player = Player(GetScreenWidth() / 2, GetScreenHeight() - GetScreenHeight() / 4, 200, 32, 32);
    laser = Laser(player.x, player.y, 300, 8);
    cout << levelEnemies << "\n";

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Controls
        
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            player.x -= player.speed * GetFrameTime();
        }
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            player.x += player.speed * GetFrameTime();
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            laser.x = player.x;
            laser.y = player.y;
            laser.isFired = true;
        }

        // Logic
        if (waveCleared == true)
        {
            level++;
            if (level >= 4)
            {
                gameOver = true;
            }

            else if (level < 4)
            {
                levelEnemies = level * 2 * 10;
                waveCleared = true;
                cout << levelEnemies << "\n";
            }
        }

        waveCleared = true;
        
        for (unsigned long long int i=0; i < enemies.size(); i++)
        {
            if (CheckCollisionCircleRec(Vector2{laser.x, laser.y}, laser.radius, enemies[i].getRect()))
            {
                enemies[i].hit = 1;

                //cout << "ouch for enemy number " << i << "\n";
            }
        }
        //cout << laser.x << " "<< laser.y << "\n";

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawFPS(10, 10);

        if (IsKeyPressed(KEY_E))
        {
            player.e = !player.e;
            laser.e = !laser.e;
        }

        player.draw();

        if (laser.y > 0 && laser.isFired == true)
        {
            laser.y -= laser.speed * GetFrameTime();
        }

        else if (laser.y > 0) 
        {
            laser.x = player.x;
            laser.y = player.y;
        }
        
        else if (laser.y < 0)
        {
            laser.y = player.y;
            laser.x = player.x;
            laser.isFired = false;
        }

        /*if (laser.y > 0)
        {
            laser.draw();
        }*/

        laser.draw();
        
        for (unsigned long long int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].y > 0 && enemies[i].hit == 0)
            {
                enemies[i].y += enemies[i].speed * GetFrameTime();
            }

            if (enemies[i].y > 600)
            {
                enemies[i].y = 10;
            }

            if (CheckCollisionRecs(player.getRect(), enemies[i].getRect()))
            {
                gameOver = true;
                //cout << "gameOver\n";
            }

            if (enemies[i].hit == 0)
            {
                waveCleared = true;
            }

            if (waveCleared == true)
            {
                enemies[i].hit = 0;
                enemies[i].y = 10;
                enemies[i].x = rand() % 800;
                enemies[i].speed = rand() % 100;
            }

            if (enemies[i].y > 0 && enemies[i].hit != 1)
            {
                enemies[i].draw();
            }
            // cout << enemies[i].hit;
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    return 0;
    //--------------------------------------------------------------------------------------
}
