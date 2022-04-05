#include <iostream>
#include "raylib.h"

class Laser
{
    public:
        float x, y, speed, radius;
        bool e, isFired;

        

	    Laser(float pX, float pY, float pSpeed, float pRadius)
	    {
		    x = pX;
		    y = pY;
		    speed = pSpeed;
            radius = pRadius;
            e = false;
            isFired = false;
	    }

        
        void draw()
        {
            if (e)
            {
                radius+=0.1;
            }
            
            DrawCircle(x, y, radius, RED);
        }

};