// cursescreen.cc
WINDOW *win1;

// Initialize screen
int initscreen()
{
  win1=initscr();
  if (has_colors() == FALSE) {
   endwin();
   printf("Your terminal does not support color\n");
  raise(2); }
  cbreak();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
//   curs_set(0);
  start_color();
  
  /* colors  
        COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7 
    
    attributes
    A_NORMAL        Normal display (no highlight)
    A_STANDOUT      Best highlighting mode of the terminal.
    A_UNDERLINE     Underlining
    A_REVERSE       Reverse video
    A_BLINK         Blinking
    A_DIM           Half bright
    A_BOLD          Extra bright or bold
    A_PROTECT       Protected mode
    A_INVIS         Invisible or blank mode
    A_ALTCHARSET    Alternate character set
    A_CHARTEXT      Bit-mask to extract a character
    COLOR_PAIR(n)   Color-pair number n */
 
  // basic pairs
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  // mixed colors 
  init_pair(7, COLOR_RED, COLOR_GREEN);
  init_pair(8, COLOR_RED, COLOR_YELLOW);
  init_pair(9, COLOR_RED, COLOR_BLUE);
  init_pair(10, COLOR_RED, COLOR_MAGENTA);
  init_pair(11, COLOR_RED, COLOR_CYAN);
  init_pair(12, COLOR_RED, COLOR_WHITE);
  init_pair(13, COLOR_GREEN, COLOR_RED);  
  init_pair(14, COLOR_GREEN, COLOR_YELLOW);  
  init_pair(15, COLOR_GREEN, COLOR_BLUE);
  init_pair(16, COLOR_GREEN, COLOR_MAGENTA);
  init_pair(17, COLOR_GREEN, COLOR_CYAN);
  init_pair(18, COLOR_GREEN, COLOR_WHITE);
  init_pair(19, COLOR_RED, COLOR_GREEN); // twice declared :)
  init_pair(20, COLOR_YELLOW, COLOR_RED);  
  init_pair(21, COLOR_YELLOW, COLOR_GREEN);   
  init_pair(22, COLOR_YELLOW, COLOR_BLUE); 
  init_pair(23, COLOR_YELLOW, COLOR_MAGENTA); 
  init_pair(24, COLOR_YELLOW, COLOR_CYAN);  
  init_pair(25, COLOR_YELLOW, COLOR_WHITE); 
  init_pair(26, COLOR_BLUE, COLOR_RED); 
  init_pair(27, COLOR_BLUE, COLOR_GREEN); 
  init_pair(28, COLOR_BLUE, COLOR_YELLOW); 
  init_pair(29, COLOR_BLUE, COLOR_MAGENTA); 
  init_pair(30, COLOR_BLUE, COLOR_CYAN);
  init_pair(31, COLOR_BLUE, COLOR_WHITE); 
  init_pair(32, COLOR_MAGENTA, COLOR_RED); 
  init_pair(33, COLOR_MAGENTA, COLOR_GREEN); 
  init_pair(34, COLOR_MAGENTA, COLOR_YELLOW); 
  init_pair(35, COLOR_MAGENTA, COLOR_BLUE); 
  init_pair(36, COLOR_MAGENTA, COLOR_CYAN); 
  init_pair(37, COLOR_MAGENTA, COLOR_WHITE); 
  init_pair(38, COLOR_CYAN, COLOR_RED);   
  init_pair(39, COLOR_CYAN, COLOR_GREEN); 
  init_pair(40, COLOR_CYAN, COLOR_YELLOW); 
  init_pair(41, COLOR_CYAN, COLOR_BLUE); 
  init_pair(42, COLOR_CYAN, COLOR_MAGENTA); 
  init_pair(43, COLOR_CYAN, COLOR_WHITE); 
  init_pair(44, COLOR_WHITE, COLOR_RED);
  init_pair(45, COLOR_WHITE, COLOR_GREEN);
  init_pair(46, COLOR_WHITE, COLOR_YELLOW);  
  init_pair(47, COLOR_WHITE, COLOR_BLUE);
  init_pair(48, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(49, COLOR_WHITE, COLOR_CYAN);
  // same colors background and foreground
  init_pair(50, COLOR_BLACK, COLOR_BLACK);
  init_pair(51, COLOR_RED, COLOR_RED);
  init_pair(52, COLOR_GREEN, COLOR_GREEN);  
  init_pair(53, COLOR_YELLOW, COLOR_YELLOW);  
  init_pair(54, COLOR_BLUE, COLOR_BLUE);
  init_pair(55, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(56, COLOR_CYAN, COLOR_CYAN);
  init_pair(57, COLOR_WHITE, COLOR_WHITE);
  // white on COLOR_BLACK  
  init_pair(58, COLOR_WHITE, COLOR_BLACK);
  
  attron(COLOR_PAIR(58));  
 return 0;
}

// close screen
void endscreen()
{
  delwin(win1);
  endwin();
  curs_set(1);
  refresh();
}

// change color
void changecolor(int choice)
{
  int color;  
  
  if (!choice)
   scanf("%d", &color);
  else
   color=choice;
   attron(COLOR_PAIR(color));
}

// draw a usual box
void drawbox(int x_pos, int x_size, int y_pos, int y_size)
{
  int i;
  attron(A_ALTCHARSET);
  changecolor(58);
  
  gotoxy(x_pos, y_pos);
  addch(108);
  gotoxy(x_pos+x_size, y_pos);
  addch(107);
  gotoxy(x_pos, y_pos+y_size);
  addch(109);
  gotoxy(x_pos+x_size, y_pos+y_size);
  addch(106);
  for (i=x_pos+1;i<x_pos+x_size;i++) {
   gotoxy(i, y_pos);
   addch(113);
   gotoxy(i, y_pos+y_size);
  addch(113); }
  for (i=y_pos+1;i<y_pos+y_size;i++) {
   gotoxy(x_pos, i);
   addch(120);
   gotoxy(x_pos+x_size, i);
  addch(120); }
  attroff(A_ALTCHARSET);
 refresh();
}

// draw vertical line
void drawverticalline(int x_pos, int y_pos, int y_size)
{
  int i;
  attron(A_ALTCHARSET);
  changecolor(58);
    
  for (i=0;i<y_size;i++) {
   gotoxy(x_pos, y_pos+i);
  addch(120); }
  changecolor(58);
  attroff(A_ALTCHARSET);
  refresh();
}

// draw horizontal line
void drawhorizontalline(int x_pos, int y_pos, int x_size)
{
  int i;
  attron(A_ALTCHARSET);
  changecolor(58);
    
  for (i=0;i<x_size;i++) {
   gotoxy(x_pos+i, y_pos);
  addch(113); }
  changecolor(58);
  attroff(A_ALTCHARSET);
  refresh();
}
