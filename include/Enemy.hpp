#include <iostream>
#include "raylib.h"

class Enemy
{
    public:
        float x, y, speed, hits, width, height;

        Enemy(float pX, float pY, float pSpeed, float pWidth, float pHeight)
        {
            x = pX;
            y = pY;
            speed = pSpeed;
            width = pWidth;
            height = pHeight;
        }

        Rectangle getRect()
        {
            // Rectangle me = {x - width / 2, y - height / 2, width, height};
            // return me;
            return Rectangle{x - width / 2, y - height / 2, width, height};
        }

        void draw()
        { 
            //cout << x << endl; //Uncomment this to debug x
            //cout << y << endl; //Uncomment this to debug y
            
            
            DrawRectangleRec(getRect(), BLUE);
        }
};