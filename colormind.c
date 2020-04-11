// colormind - mastermind clone
#include "cmind.h"

int main()
{
  int i, quitflag, victory=0;
    
   // initialization
   srand(time(NULL));
   initscreen();
   generatecolorcode();
  
    drawscreen();
    // loop
    while (tries<MAXTRIES) {
     if ((quitflag=readnextcolorline()))
      break;
     // parse line
     for (i=0;i<nocolors;i++)
      ++guessedsumcolors[1][guessedcolors[tries][i]];
     i=cmindengine();
     showcolorsandpegs(i, tries); 
     if ((victory=estimatevictory()))
      break;
    ++tries; }
   
    // result
    if (quitflag)
     return -1;
     attron(A_BLINK);
     switch (victory) {
      case 0:
       showmessage((nocolors*2)+10, 5, "Loss!", 0, 7);
       attroff(A_BLINK);
       revealcode();
      break;
      case 1:
       showmessage((nocolors*2)+10, 5, "Victory!", 0, 8);
       attroff(A_BLINK);
   break; }
   
  showmessage(1, 24, "key to exit", 1, 58);
  endscreen();
 return 0;
}
