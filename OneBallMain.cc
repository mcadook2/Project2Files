#include<iostream>
#include<Board.h>
#include<stdio.h>
#include<stdlib.h>


using namespace std;

// Windows violates the ANSI standard with some standard functions,
// like sleep().  So we have to use a different header if we are
// running windows to use that function.  Everyone else uses unistd.h.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


void StepBall(double &ballX, double &ballY, double &ballDX, double &ballDY, 
              int ballColor, int width, int height) {
    double newX = ballX + ballDX;  // Move forward/backward by dX
    double newY = ballY + ballDY;  // Move up/down by dY

    // Bounce off the X walls
    if (newX < 1) {
        newX = 1;       // Put it at the wall
        ballDX *= -1.0;   // Flip the velocity (bounce)
    }

    if (newX > width) {
        newX = width;   // Put it at the wall
        ballDX *= -1.0;   // Flip the velocity (bounce)
    }

    // Bounce off the Y walls
    if (newY < 1) {
        newY = 1;       // Put it at the wall
        ballDY *= -1.0;   // Flip the velocity (bounce)
    }

    if (newY > height) {
        newY = height;   // Put it at the wall
        ballDY *= -1.0;   // Flip the velocity (bounce)
    }

    // Commit to the new position:
    ballX = newX;
    ballY = newY;
}


void MillisecondsDelay(int msec) {
#ifdef _WIN32
  Sleep(msec);  // Takes milliseconds
#else
  usleep(msec*1000);  // Takes nanoseconds
#endif
}

int main() {
    double ballX = 10;
    double ballY = 10;
    double ballDX = 1;
    double ballDY = 1;
    int ballColor = 2;

    int width;
    int height;
    int maxSteps = 500;

    cout << "Give the X and Y position of the ball: ";
    cin >> ballX >> ballY;
    cout << "Give the dX and dY velocity of the ball: ";
    cin >> ballDX >> ballDY;

    cout << "Initializing the display ..." << endl;

    // Clear the display for drawing ASCII art
    SetupCursesDisplay(width, height);
    //width = 20;
    //height = 20;

    // Draw our ball!
    DrawBall(-1, -1, ballX, ballY, ballColor);
    getchar();

    // Loop for maxSteps, moving the ball each time step
    for (int step=0; step<maxSteps; step++) {
      // Slow the sim down so we can actually see it (pause for 1/20 sec)
      MillisecondsDelay(50);

      // Remember where the ball used to be, so we can erase it
      double oldX = ballX;  
      double oldY = ballY;

      // Move the ball one time step
      StepBall(ballX, ballY, ballDX, ballDY, ballColor, width, height);
      //cout << "Ball[" << step << "]:  " << ballX << ", " << ballY 
      //     << ", " << ballDX << ", " << ballDY << endl;

      // Draw the new position of the ball, erase the old.
      DrawBall(oldX, oldY, ballX, ballY, ballColor);
    }

    //ShutdownCursesDisplay();
    cout << "... Display is closed." << endl;
    cout << "Display Dim:  " << width << "  " << height << endl;

    return 0;
}
