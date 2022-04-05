#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
 
// Driver program
int main(void)
{
    // This program will create different sequence of
    // random numbers on every program run
 
    // Use current time as seed for random generator
    srand(time(0));
    int randomNumber;
 	cout << "Start\n";
    for(int i = 0; i<5; i++)
    {
        randomNumber = rand()%800;
        if(randomNumber > 800)
        {
        	cout << "A number greater than 800\n";
        }
        else if(randomNumber == 800)
        {
        	cout << "Success\n";
        }
        cout << randomNumber << "\n";
    }
 	cout << "End";
    return 0;
}