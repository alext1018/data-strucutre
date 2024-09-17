#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>

using namespace std;
using namespace chrono;

// define some constants
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool gameOver;

// set up the game
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// draw the grid and snake on the console
void Draw()
{
    system("clear"); // clear the console
    cout << "Score: " << score << endl;
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool printed = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        printed = true;
                    }
                }
                if (!printed)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
}

// take input from the user
void Input()
{
    static bool initialized = false;
    static termios oldt, newt;

    if (!initialized) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        setbuf(stdin, NULL);
        initialized = true;
    }

    auto startTime = steady_clock::now();

    while (true) {
        if (kbhit()) {
            switch (getchar()) {
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'q':
                gameOver = true;
                break;
            default:
                break;
            }
            break;
        }

        auto elapsedTime = duration_cast<milliseconds>(steady_clock::now() - startTime).count();
        if (elapsedTime >= 50) {
            break;
        }
    }
}

// update the game state

// update the game state
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
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
        default:
            break;
    }

    // check if the snake goes out of bounds or collides with its own tail
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // check if the snake eats the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
