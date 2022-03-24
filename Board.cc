#include<Board.h>
#include<curses.h>

// Create some constants that we will use for drawing
#define MAXCHARS 10
#define BALL_CHARACTER 'O'

// The "COLOR_{etc}" constants are predefined in the ncurses header
const int  COLOR_LEVELS[MAXCHARS] = {COLOR_WHITE, COLOR_WHITE, COLOR_YELLOW,
                                     COLOR_GREEN, COLOR_GREEN, COLOR_CYAN,
                                     COLOR_BLUE, COLOR_BLUE, COLOR_MAGENTA,
                                     COLOR_RED};

/**
 * Use the ncurses library to setup the display for drawing.  The screen
 * is drawn all in black
 **/
void SetupCursesDisplay(int &width, int &height) {
    initscr();  // ncurses: Determine terminal type, setup ncurses
    cbreak();   // ncurses: Disable line buffering
    noecho();   // ncurses: Don't echo input back to the screen

    // Set the width and height of the field
    height = LINES-1;  // LINES is defined in ncurses
    width  = COLS-1;  // COLS is defined in ncurses

    // Clear the display
    clear();  // ncurses:  Clear the display

    // Setup the colors available to us (foregrand and backgound)
    start_color();
    for (int idx=0; idx<MAXCHARS; idx++)
      init_pair(idx+1, COLOR_LEVELS[idx], COLOR_BLACK);

  refresh();  // ncurses: refresh the screen
}


/**
 * This function provides the ability to clear the display 
 * so the screen will be blank.
 **/
void ClearCursesDisplay() {
    clear();  // ncurses: Clear the display
}


/**
 * Use the ncurses library to put the display back the TwoDCharArray
 * it is supposed to be.
 **/
void ShutdownCursesDisplay() {
  endwin();  // ncurses: Return the terminal to normal control
}


void DrawBall(double oldX, double oldY, double newX, double newY, int ballColorLevel) {
  // If the old ball position is positive, erase it
  if ( (oldX > 0) && (oldY > 0) ) {
    //attron(COLOR_PAIR(0));  // Set color to Black
    //mvaddch((int)oldY, (int)oldX, ' ');  // ncurses:  draw a blank space
    attron(COLOR_PAIR(MAXCHARS-1));      // Set color to Red
    mvaddch((int)oldY, (int)oldX, '.');  // ncurses:  draw a tracer as a '.'
  }

  // If the new ball position is positive, draw it
  if ( (newX > 0) && (newY > 0) ) {
    attron(COLOR_PAIR(ballColorLevel));  // Set color to whatever we're given
    mvaddch((int)newY, (int)newX, BALL_CHARACTER);  // ncurses:  draw character
  }

  refresh();  // ncurses: refresh the screen
}
