#ifndef BOARD_H_
#define BOARD_H_

void SetupCursesDisplay(int &width, int &height);
void ClearCursesDisplay();
void ShutdownCursesDisplay();
void DrawBall(double oldX, double oldY, double newX, double newY, int ballColorLevel);

#endif
