// colormind headers

// included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>

// constant definitions
#define UP 259
#define LEFT 260
#define RIGHT 261
#define DOWN 258
#define ESC 27
#define SPACE 32
#define MAXCOLORS 6
#define MINCOLORS 2
#define STANDARDCOLORSNO 4
#define MAXTRIES 10
#define CWHITE 0
#define CBLACK 1
#define VERSION 1.0

// variables, classes, structures
bool reveal=false;
int colorcode[2][MAXCOLORS], guessedcolors[MAXTRIES][MAXCOLORS]={ 0 }, guessedsumcolors[2][MAXCOLORS]={ 0 }, pegshistory[MAXTRIES][2]={ 0 }, tries=0, nocolors=STANDARDCOLORSNO;

// function definitions
// cursescreen
int initscreen();
void endscreen();
void changecolor(int choice);
void drawbox(int x_pos, int x_size, int y_pos, int y_size);
void drawverticalline(int x_pos, int y_pos, int y_size);
void drawhorizontalline(int x_pos, int y_pos, int x_size);
// cmindengine
int cmindengine();
void generatecolorcode();
// cmindlibrary
void showhelp();
int showmessage(int x_pos, int y_pos, const char *message, int keyflag, int color);
void drawscreen();
void showcolorsandpegs(int pegsnumber, int trynumber);
int readnextcolorline();
void showcurrentcolorline(int trynunber);
void redrawscreen();
void revealcode();
int estimatevictory();
void gotoxy(int x, int y);

// locally included files
#include "cursesscreen.c"
#include "cmindengine.c"
#include "cmindlibrary.c"


