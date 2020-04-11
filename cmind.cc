// colormind - mastermind clone
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>

#define MAXCOLORS 8
#define MINCOLORS 2
#define STANDARDCOLORSNO 4
#define MAXTRIES 16
#define MINTRIES 2
#define STANDARDTRIESNO 8
#define MAXLINE 80
#define VERSION 1.0
#define WHITE 0
#define BLACK 1

using namespace std;

// variables, classes
class PEGS {
 public:
  int white;
  int black;
  PEGS(int i1, int i2) { white=i1; black=i2; };
  PEGS() { };
~PEGS() { }; };
vector<PEGS> pegshistory;
struct Word { char formulaWord[MAXLINE]; };
vector<Word> words;
const char *COLORNAMES[]={ "red", "green", "blue", "black", "cyan", "magenta", "brown", "white" }, *PEGNAMES[]={ "white", "black" }, *PASSWORD="reveal";
char *myname;
bool reveal=false;
int colorcode[2][MAXCOLORS], guessedcolors[MAXTRIES][MAXCOLORS], guessedsumcolors[2][MAXCOLORS], whitepegs, blackpegs, tries=0, maxtries=STANDARDTRIESNO, nocolors=STANDARDCOLORSNO;

// functions declaration
void separatewords(char formula[]);
int readline(char line[]);
void showpegshistory();
void revealcolorcode();
void showusage();

int main(int argc, char *argv[])
{
  int i, i1, c, correctline, victory=0;
  char guessline[MAXLINE];
  myname=argv[0];
  // randomize
  srand(time(NULL));

  // parse command line options
  while ((c = getopt(argc, argv, ":c:t:r")) != -1)
   switch (c) {
	case 'c':
     if ((i=atoi(optarg))<=MAXCOLORS && i>=MINCOLORS)
      nocolors=atoi(optarg);
     else
      showusage();
    break;
    case 't':
     if ((i=atoi(optarg))<=MAXTRIES && i>=MINTRIES)
      maxtries=atoi(optarg);
     else
      showusage();
    break;
    case 'r':
     reveal=true;
    break;
    case '?':
     showusage();
    break;
    default:
     abort();
  break; }
  
  // show information
  cout << "ColorMind version " << VERSION << endl << "colors: <";
  for (i=0;i<nocolors;i++)
   cout << COLORNAMES[i] << " ";
  cout << "\b> extra: <history>";
  if (reveal)
   cout << " <reveal>";
  cout << endl;
  // generate color code
  for (i=0;i<nocolors;i++) // colorcode[2] contains generated code and sum of colors
   colorcode[1][i]=0;
  for (i=0;i<nocolors;i++) {
   colorcode[0][i]=rand() % nocolors;
  ++colorcode[1][colorcode[0][i]]; }
   // loop
   while (tries<maxtries) {
    for (i=0;i<nocolors;i++) { // guessedcolors contains currently given code
     guessedcolors[tries][i]=-1;
     guessedsumcolors[0][i]=0; // guessedsumcolors[2] contains given pegs from guessed colors and sum of given guessed colors
    guessedsumcolors[1][i]=0; }
    correctline=0;
    while (!correctline) {
     correctline=1;
     cout << "try number: " << tries+1 << endl;
     while (!(i=readline(guessline)));
     separatewords(guessline);
     if (words.size()!=nocolors)
      correctline=0;
     // extra commands
     if (!strcmp(guessline, "history"))
      showpegshistory();
     if (!strcmp(guessline, PASSWORD) && reveal)
      revealcolorcode();
     // parse words vector
     for (i=0;i<nocolors;i++)
      for (i1=0;i1<nocolors;i1++)
       if (!strcmp(words[i].formulaWord, COLORNAMES[i1]))
        guessedcolors[tries][i]=i1;
     for (i=0;i<nocolors;i++)
      ++guessedsumcolors[1][guessedcolors[tries][i]];
     for (i=0;i<nocolors;i++)
      if (guessedcolors[tries][i]==-1)
    correctline=0; }
    // award pegs
    whitepegs=0; blackpegs=0;
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
    for (i=0;i<whitepegs;i++)
     cout << PEGNAMES[WHITE] << " ";
    for (i=0;i<blackpegs;i++)
     cout << PEGNAMES[BLACK] << " ";
    if (!whitepegs && !blackpegs)
     cout << "zero pegs";
    cout << endl;
    // record peg history
    PEGS tpegs(whitepegs, blackpegs);
    pegshistory.push_back(tpegs);
    ++tries;
    if (blackpegs==nocolors) {
     victory=1;
   break; } }
   // result
   switch (victory) {
    case 0:
     cout << "color code: ";
     for (i=0;i<nocolors;i++)
      cout << COLORNAMES[colorcode[0][i]] << " ";
     cout << endl;
    break;
    case 1:
     cout << "Victory!" << endl;
   break; }

 return 0;
}

// separate words in string and store in vector inside structure
void separatewords(char formula[])
{
  int i, n;
  char tformula[MAXLINE];
  Word tword;
  vector<Word>::iterator p=words.begin();
  while (p<words.end()) // because words.clear() only moves pointer, words are kept
   words.erase(p++);
  words.clear();
    
   for (i=0;i<strlen(formula);i++) {
    n=0;
    while (isspace(formula[i]))
     ++i;
    while (!isspace(formula[i]) && i<strlen(formula))
     tformula[n++]=tolower(formula[i++]);
    tformula[n]='\0';
    strcpy(tword.formulaWord, tformula);
   words.push_back(tword); }
}

// read line
int readline(char line[])
{
  int i=0;
  char c;
  
   while ((c=getchar())!='\n')
    line[i++]=c;
   line[i]='\0'; 
    
 return strlen(line);
}

// show pegs history
void showpegshistory()
{
  int i, i1, i2;
  
   for (i=0;i<tries;i++) {
    cout << i+1 << ":";
    for (i1=0;i1<nocolors;i1++)
     cout << COLORNAMES[guessedcolors[i][i1]] << " ";
    cout << "-> ";
    for (i1=0;i1<pegshistory[i].white;i1++)
     cout << PEGNAMES[WHITE][0] << " ";
    for (i2=0;i2<pegshistory[i].black;i2++)
     cout << PEGNAMES[BLACK][0] << " ";
    if (!i1 && !i2)
     cout << "zero";
   cout << endl; }
}
        
// reveal code
void revealcolorcode()
{
  int i;
  
  cout << "color code: ";
  for (i=0;i<nocolors;i++)
   cout << COLORNAMES[colorcode[0][i]] << " ";
  cout << endl;
} 

// show usage
void showusage()
{
  cout << myname << " [-c <colors&rows, 2..8>] [-t <tries 2..16>] [-r <reveal code>]" << endl;
    
 exit(EXIT_FAILURE);   
}
