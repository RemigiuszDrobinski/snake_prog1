#pragma once
#include <fstream>
#include <string>
using namespace std;

enum eDirection { STOP = 0, l, p, g, d };
eDirection movement;
int w = 15, h = 20, nTail, option_menu, przenikanie = 0, time_snake = 45;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
string nick, save;
fstream plik;
int a, b, c;
bool gameOver;
