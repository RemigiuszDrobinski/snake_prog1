#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>
#include "Header.h"
#include "Header1.h"

using namespace std;

void option();
void draw_menu();

void start()                                        //Funkcja, która
{
	draw_menu();
	system("cls");
	while (!gameOver) {
		drawingMap();
		Input();
		Logic();
		Sleep(time_snake);
	}
}

void clearScreen() {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0,0 };
	SetConsoleCursorPosition(output, pos);
}

void emptyline() {
	cout << "#                                   #" << endl;
}

void option() {
	system("cls");
	for (int i = 0; i < 37; i++)
		cout << "#";
	cout << endl;
	emptyline();
	cout << "#         1.WYMIARY MAPY            #" << endl;
	cout << "#         2.PREDKOSC WEZA           #" << endl;
	cout << "#         3.PRZENIKANIE SCIAN       #" << endl;
	cout << "#         4.MENU                    #" << endl;
	emptyline();
	for (int i = 0; i < 37; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cin >> option_menu;
	switch (option_menu) {
	case 1:
		cout << "Podaj wysokosc mapy: ";
		cin >> h;
		cout << "Podaj szerokosc mapy: ";
		cin >> w;
		option();
		break;
	case 2:
		cout << "Podaj opoznienie weza: ";
		cin >> time_snake;
		option();
		break;
	case 3:
		cout << "Czy waz moze przenikac przez sciany: " << endl;
		cout << "(Wpisz 1 jesli tak, 0 jesli nie)" << endl;
		cin >> przenikanie;
		option();
		break;
	case 4:
		draw_menu();
	}
}

void draw_menu() {
	system("cls");
	for (int i = 0; i < 37; i++)
		cout << "#";
	cout << endl;
	emptyline();
	cout << "#            WITAJ GRACZU           #" << endl;
	cout << "#    ABY ROZOCZAC SWOJA PRZYGODE    #" << endl;
	cout << "#   WPISZ INTERESUJACA CIE LICZBE   #" << endl;
	emptyline();
	emptyline();
	cout << "#             1.START               #" << endl;
	cout << "#             2.OPCJE               #" << endl;
	cout << "#             3.WYJDZ               #" << endl;
	emptyline();
	cout << "#          Remigiusz Drobinski 2019 #" << endl;
	for (int i = 0; i < 37; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cin >> option_menu;
	switch (option_menu) {
	case 1:

		break;
	case 2:
		option();
		break;
	case 3:
        exit(0);
		break;
	}
}



void score_add() {
	if (h*w < 150) a = 2;
	else a = 1;
	if (time_snake < 40) b = 2;
	else b = 1;
	if (przenikanie == 0) c = 3;
	else c = 1;
	score = score + 10 * a * b * c;
}

void save_score() {
	cout << endl;
	cout << "Czy chcesz zapisac swoj wynik? (tak/nie)";
	cin >> save;
	if (save == "tak") {
		cout << "Podaj swoj nick: "; cin >> nick;
		plik.open("wyniki.txt", ios::out | ios::app);
		time_t czas;
		struct tm * ptr;
		time(&czas);
		ptr = localtime(&czas);
		char * data = asctime(ptr);
		plik << "Nick: " << nick << endl;
		plik << "Score: " << score << endl;
		plik << "Data: " << data << endl;
		plik.close();
	}
}


void drawingMap() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	clearScreen();
	for (int i = 0; i < w + 2; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x) {
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
				cout << "O";
				SetConsoleTextAttribute(hOut, FOREGROUND_RED);

			}
			else if (i == fruitY && j == fruitX)
				cout << "*";

			else {

				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
						cout << "o";
						SetConsoleTextAttribute(hOut, FOREGROUND_RED);
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == w - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < w + 2; i++) {
		cout << "#";
	}
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	cout << endl << "Score: " << score;
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);
}

void Setup() {
	gameOver = false;
	movement = STOP;
	x = w / 2;
	y = h / 2;
	fruitX = rand() % w;
	fruitY = rand() % h;
}
void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			movement = l;
			break;
		case 'd':
			movement = p;
			break;
		case 'w':
			movement = g;
			break;
		case 's':
			movement = d;
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
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (movement) {
	case l:
		x--;
		break;
	case p:
		x++;
		break;
	case g:
		y--;
		break;
	case d:
		y++;
		break;
	default:
		break;
	}
	if (przenikanie == 0) {
		if (x > w || x < 0 || y > h || y < 0)
			gameOver = true;
	}
	else {
		if (x >= w) {
			x = 0;
		}
		else if (x < 0)
			x = w - 1;
		if (y >= h)
			y = 0;
		else if (y < 0)
			y = h - 1;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		score_add();
		fruitX = rand() % w;
		fruitY = rand() % h;
		nTail++;
	}
}
