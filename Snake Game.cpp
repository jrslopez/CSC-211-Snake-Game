#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
void Difficulty();
void Setup();
void Draw();
void Input();
void Logic();
void Restart();

bool gameOver, endGame;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, random30fruitX, random30fruitY, random5fruitX, random5fruitY, score;
int tailX[100], tailY[100];
int nTail;
char head, tail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
enum eDifficulty { EASY, MEDIUM, HARD };
eDifficulty mode;
float speed;

int main()
{
	system("Color F0");
	Difficulty();
	Setup();
	while (!endGame)
	{
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
			Sleep(speed);
		}
		Restart();
	}
	return 0;
}

void Difficulty()
{
	int gamemode;
	cout << "Welcome to our Snake Game!" << endl;
	cout << "by James Lopez, Fabio Pecora, Karen Koag, and Megan Kwan" << endl;
	cout << endl;
	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
	cout << endl;
	cout << "Choose a game mode: " << endl;
	cin >> gamemode;
	switch (gamemode)
	{
	case 1:
		mode = EASY;
		speed = 10;
		break;
	case 2:
		mode = MEDIUM;
		speed = 0.1;
		break;
	case 3:
		mode = HARD;
		speed = 0.001;
		break;
	}
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2; //snake starts in middle
	y = height / 2;
	head = '^';
	tail = 's';
	fruitX = rand() % width;
	fruitY = rand() % height;
	if (mode != EASY)
	{
		random30fruitX = rand() % width;
		random30fruitY = rand() % height;
		random5fruitX = rand() % width;
		random5fruitY = rand() % height;
	}
	score = 0;
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++)
		cout << "_"; //top border
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "|"; //left border
			if (i == y && j == x)
				cout << head; //snake head
			else if (i == fruitY && j == fruitX)
				cout << "@"; //regular fruit
			else if (i == random30fruitY && j == random30fruitX)
			{
				if (score % 45 == 0 && score != 0)
					cout << "o"; //random fruit
				else cout << " ";
			}
			else if (i == random5fruitY && j == random5fruitX)
			{
				if (score % 20 == 0 && score != 0)
					cout << "."; //random fruit
				else cout << " ";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << tail; //tail
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "|"; //right border
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "_"; //bottom border
	cout << endl;
	cout << "Score:" << score << endl;
}


void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}


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
		head = '<';
		tail = '~';
		x--;
		break;
	case RIGHT:
		head = '>';
		tail = '~';
		x++;
		break;
	case UP:
		head = '^';
		tail = 's';
		y--;
		break;
	case DOWN:
		head = 'v';
		tail = 's';
		y++;
		break;
	default:
		break;
	}
	if (mode == HARD)
	{
		if (x >= width || x < 0 || y >= height || y < 0) //for bordered game
			gameOver = true;
	}
	if (x >= width) 
		x = 0; 
	else if (x < 0) 
		x = width - 1;
	if (y >= height) 
		y = 0; 
	else if (y < 0) 
		y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

	if (x == random30fruitX && y == random30fruitY) //randomfruit for 30 points
	{
		score += 30;
		random30fruitX = rand() % width;
		random30fruitY = rand() % height;
		nTail++;
	}

	if (x == random5fruitX && y == random5fruitY) //randomfruit for 5 points
	{
		score += 5;
		random5fruitX = rand() % width;
		random5fruitY = rand() % height;
		nTail++;
	}
}
void Restart()
{
	char choice;
	cout << "That was a great run! Do you want to play again (Y/N)? ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		endGame = false;
		gameOver = false;
	}
	else
	{
		cout << endl;
		cout << "Your final score is: " << score << endl;
		cout << endl;
		cout << "Sad to see you go :( Thank you for playing our game! :)" << endl;
		cout << endl;
		endGame = true;
	}
}
