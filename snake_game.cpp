#include <iostream> // input-output stream
#include <cstdlib> // C standard library
#include <conio.h> // console input-output
#include <windows.h> // for implementing 'Sleep' function

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20; // size of the window
int x, y, coinX, coinY, score; // x,y - coordinates of the snake's head		coinX, coinY - coordinates of the coin
int tailX[100], tailY[100];
int tailLength;
enum Direction {STOP = 0, UP, LEFT, DOWN, RIGHT};
Direction d;

void Setup();
void Draw();
void Input();
void Logic();

int main()
{
	Setup();
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(200);
	}
	return 0;
}

void Setup()
{
	gameOver = false;
	d = STOP;
	x = (width / 2);
	y = (height / 2);
	coinX = 2 * (rand() % (width / 2));
	coinY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	
	cout << "SNAKE GAME v. 1.0" << endl;
	cout << "by Jakub Sadecki" << endl << endl;
	cout << "CONTROL:" << endl;
	cout << "       up 'W'       " << endl;
	cout << "left 'A'   right 'D'" << endl;
	cout << "      down 'S'      " << endl << endl;
	
	for (int i = 0; i < (width + 2); i++)
		cout << ",";	
	cout << endl;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << ",";
				
			if (i == y && j == x)
				cout << "O";
			else if (i == coinY && j == coinX)
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < tailLength; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}	
			if (j == (width - 1))
				cout << ",";
		}
		cout << endl;
	}
	
	for (int i = 0; i < (width + 2); i++)
		cout << ",";
	cout << endl << endl;
	cout << "SCORE: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'w':
				d = UP;
				break;
			case 'a':
				d = LEFT;
				break;
			case 's':
				d = DOWN;
				break;
			case 'd':
				d = RIGHT;
				break;
			case 27: // 27 is ASCII Code for 'ESC' button
				gameOver = true;
				break;
		}
	}
}

void Logic()
{
	int pastX = tailX[0];
	int pastY = tailY[0];
	int pastX2, pastY2;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++)
	{
		pastX2 = tailX[i];
		pastY2 = tailY[i];
		tailX[i] = pastX;
		tailY[i] = pastY;
		pastX = pastX2;
		pastY = pastY2;
	}
	switch (d)
	{
		case UP:
			y--;
			break;
		case LEFT:
			x = (x - 2);
			break;
		case DOWN:
			y++;
			break;
		case RIGHT:
			x = (x + 2);
			break;
		default:
			break;
	}
	if (x >= width || x < 0 || y >= height || y < 0)
		gameOver = true;
	
	for (int i = 0; i < tailLength; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	
	if (x == coinX && y == coinY)
	{
		score = score + 10;
		coinX = 2 * (rand() % (width / 2));
		coinY = rand() % height;
		tailLength++;
	}
}


