// cmindengine.cc
int cmindengine()
{
  int i, i1, whitepegs=0, blackpegs=0;
  
    // award pegs
    // black pegs
    for (i=0;i<nocolors;i++) {
     if (guessedcolors[tries][i]==colorcode[0][i]) {
      ++guessedsumcolors[0][guessedcolors[tries][i]];
     ++blackpegs; } }
     // white pegs
     for (i=0;i<nocolors;i++) {
      for (i1=0;i1<nocolors;i1++) {
        if (guessedcolors[tries][i]==colorcode[0][i1] && guessedcolors[tries][i]!=colorcode[0][i] && guessedsumcolors[0][guessedcolors[tries][i]]<colorcode[1][guessedcolors[tries][i]] && guessedsumcolors[0][guessedcolors[tries][i]]<guessedsumcolors[1][guessedcolors[tries][i]]) {
        ++guessedsumcolors[0][guessedcolors[tries][i]];
    ++whitepegs; } } }
    // record peg history
    pegshistory[tries][CWHITE]=whitepegs;
    pegshistory[tries][CBLACK]=blackpegs;    

 return whitepegs+blackpegs;
}

// generate color code
void generatecolorcode()
{
 int i;
 
  for (i=0;i<nocolors;i++) // colorcode[2] contains generated code and sum of colors
   colorcode[1][i]=0;
  for (i=0;i<nocolors;i++) {
   colorcode[0][i]=rand() % nocolors;
  ++colorcode[1][colorcode[0][i]]; }
}

