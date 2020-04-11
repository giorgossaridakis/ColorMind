// colormind library

// show help
void showhelp()
{
  int i;
   clear();
   changecolor(58);
   gotoxy(1,1);
   printw("               ColorMind %.1f - a MasterMind curses clone.\n\nYou,the codebreaker try to guess a color pattern, in both order and color, within ten turns.Each guess is made by placing a row of colored pegs on the bottom of the screen.Once placed, the codemaker (the computer) places your choice on the appropriate turn row and provides feedback by placing from zero to four letters in the same row.A <b>lack peg is placed for each code peg from the guess which is correct in both color and position.A <w>hite peg indicates the existence of a correct color code peg placed in the wrong position. If there are duplicate colours in the guess, they cannot all be awarded a key peg unless they correspond to the same number of duplicate colours in the hidden code. For example, if the hidden code is white-white-black-black and the player guesses white-white-white-black, the codemaker will award two colored key pegs for the two correct whites, nothing for the third white as there is not a third white in the code, and a colored key peg for the black. No indication is given of the fact that the code also includes a second black.\n\n\n\n\n\n\n\nhit key..", VERSION);
   refresh();
   getchar();
   redrawscreen();
}

// show a message
int showmessage(int x_pos, int y_pos, const char *message, int keyflag, int color)
{
  int i, n=0;
  
  changecolor(color);
  for (i=x_pos;i<x_pos+strlen(message);i++) {
   gotoxy(i, y_pos);
  addch(message[n++]); }
  refresh();
  if (keyflag)
   return (getchar());
  
 return 0;
}


// draw screen
void drawscreen()
{
  int i;
  clear();
  
  gotoxy(nocolors*2, 1);
  changecolor(11);
  printw("ColorMind %.1f", VERSION);
  changecolor(58);
  gotoxy(1,2);
  for (i=0;i<10+nocolors;i++)
   printw("/\\");
  drawbox(1, (nocolors*2), 3, (MAXTRIES*2)); // MAXTRIES is 10 anyway
  for (i=0;i<MAXTRIES-1;i++)
   drawhorizontalline(2, 5+(i*2), (nocolors*2));
  for (i=0;i<nocolors;i++)
   drawverticalline(3+(i*2), 4, (MAXTRIES*2)-1);
  showmessage((nocolors*2)+10, 3, "colors", 0, 58);
  for (i=0;i<nocolors;i++) {
   changecolor(i+1);
   gotoxy((nocolors*2)+10+(i*2), 4);
  addch('x'); }
  showmessage((nocolors*2)+10, (MAXTRIES*2)-3, "<arrow keys>", 0, 58);
  showmessage((nocolors*2)+10, (MAXTRIES*2)-2, "<enter>", 0, 58);
  showmessage((nocolors*2)+10, (MAXTRIES*2)-1, "<o>ptions", 0, 58);
  showmessage((nocolors*2)+10, (MAXTRIES*2), "<h>elp", 0, 58);
  if (reveal)
   showmessage((nocolors*2)+10, (MAXTRIES*2)+1, "<r>eveal", 0, 58);
  showmessage((nocolors*2)+10, (MAXTRIES*2)+2,"ESC or <q>uit", 0, 58);
  refresh();
}

// show colors in table and pegs
void showcolorsandpegs(int pegsnumber, int trynumber)
{
  int i;
  
  // colors
  for (i=0;i<nocolors;i++) {
   changecolor(guessedcolors[trynumber][i]+1);
   gotoxy((i*2)+2, (MAXTRIES*2)+2-(trynumber*2));
  addch('x'); }
  changecolor(58);
  gotoxy((nocolors*2)+2, (MAXTRIES*2)+2-(trynumber*2));
  // pegs
  for (i=0;i<pegshistory[trynumber][CWHITE];i++)
   addch('w');
  for (i=0;i<pegshistory[trynumber][CBLACK];i++)
   addch('b');
  if (!pegsnumber)
   printw("zero");
  refresh();
}

// read next color line
int readnextcolorline()
{
  int i, i1, colorpos=0, c;
  if (tries)
   for (i=0;i<nocolors;i++)
    guessedcolors[tries][i]=guessedcolors[tries-1][i];
  showcurrentcolorline(tries);
  gotoxy(2+(colorpos*2), 24);
  refresh();
  
  while (c!=ESC && c!='q' && c!='\n') {
   c=tolower(getch());
   if (c!=ERR) {
    switch (c) {
     case RIGHT:
      if (colorpos<nocolors-1)
       ++colorpos;
     break;
     case LEFT:
      if (colorpos>0)
       --colorpos;
     break;
     case UP:
      if (guessedcolors[tries][colorpos]<nocolors-1)
       ++guessedcolors[tries][colorpos];
     break;
     case DOWN:
      if (guessedcolors[tries][colorpos]>0)
       --guessedcolors[tries][colorpos];
     break;
     case 'h':
      showhelp();
     break;
     case 'o':
      while ((tolower(i=showmessage(1, 24, "reveal code (y/n):", 1, 58)))!=ESC && i!='y' && i!='n');
      addch(i);
      refresh();
      if (i==ESC) {
       clearline(24);
       showcurrentcolorline(tries);
      break; }
      if (i=='y')
       reveal=1;
      while ((tolower(i=showmessage(1, 24, "colors/rows number 2..6:", 1, 58)))!=ESC && !isdigit(i));
      i-='0';
      if (i<MINCOLORS || i>MAXCOLORS) {
       clearline(24);
       showcurrentcolorline(tries);
      break; }
      printw("%d", i);
      refresh();
      if (nocolors!=i) {
       nocolors=i;
       tries=0;
      generatecolorcode(); }
      redrawscreen();
     break;
     case 'r':
      if (reveal)
       revealcode();
    break; }
    changecolor(guessedcolors[tries][colorpos]+1);
    gotoxy(2+(colorpos*2), 24);
    printw("x");
    gotoxy(2+(colorpos*2), 24);
  refresh(); } }
  // reset guessedsumcolors array
  for (i1=0;i1<2;i1++)
   for (i=0;i<nocolors;i++) // guessedcolors contains currently given code
    guessedsumcolors[i1][i]=0; // guessedsumcolors[2] contains given pegs from guessed colors and sum of given guessed colors
  for (i=0;i<nocolors;i++)
   ++guessedsumcolors[1][guessedcolors[tries][i]];
    
 // return values: 0 next try, 1 exit
 return (c=='\n') ? 0 : 1;
}

// redraw screen
void redrawscreen()
{
  int i;
  
   clear();
   drawscreen();
   for (i=0;i<tries;i++) 
    showcolorsandpegs(pegshistory[i][CWHITE]+pegshistory[i][CBLACK], i);
   showcurrentcolorline(tries);
}

// clear line
void clearline(int line)
{
  int i=1;
  
   changecolor(58);
   gotoxy(i, line);
   for (;i<80;i++)
    addch(SPACE);
  refresh();
}

// show current read line
void showcurrentcolorline(int trynunber)
{
  int i;   

   for (i=0;i<nocolors;i++) {
    changecolor(guessedcolors[trynunber][i]+1);
    gotoxy(2+(i*2), 24);
   printw("x"); }
   refresh();
}

// reveal code
void revealcode()
{
  int i;
  
   showmessage((nocolors*2)+10, 6, "color code", 0, 58);
   for (i=0;i<nocolors;i++) {
    changecolor(colorcode[0][i]+1);
    gotoxy((nocolors*2)+10+(i*2), 7);   
   addch('x'); }
}

// estimate victory
int estimatevictory()
{
  return (pegshistory[tries][CBLACK]==nocolors) ? 1 : 0;
}

// gotoxy
void gotoxy(int x, int y)
{
  move(y-1,x);
}
