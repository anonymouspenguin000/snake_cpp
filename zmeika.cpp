#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fx, fy, score;
int tailX[100], tailY[100], nTail = 0;
enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;

void regenFood() {
    while (true) {
        fx = rand() % width;
        fy = rand() % height;
        if (fx < width - 1 && fy < height - 1 && fx > 0 && fy > 0) break;
    }
}
void Setup() {
    srand(time(NULL));
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    regenFood();
    score = 0;
}
void Draw() {
    system("cls");
    cout << "Control snake: W, A, S, D. Press X to close.\nYou need to turn on english keyboard layout" << endl << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) cout << '#';
            else if (i == fy && j == fx) cout << '*';
            else if (i == y && j == x) cout << '@';
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << '&';
                        print = true;
                    }
                }
                if (!print) cout << ' ';
            } 

            if (j == width - 1) cout << endl;
        }
    }
    cout << endl << "Score: " << score;
}
void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
           y--;
            break;
        case DOWN:
            y++;
            break;
    }

    if (x == width - 1 || x == 0 || y == height - 1 || y == 0) gameOver = true;
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }
    if (x == fx && y == fy) {
        score += 5;
        nTail++;
        regenFood();
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(120);
    }
    return 0;
}

