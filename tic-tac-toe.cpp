/***********************************************************************
* Program:
*    Lesson 08, Tic-Tac-Toe
* Summary: 
*    This program reads, displays, and writes a Tic-Tac-Toe board
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#define size 3
#define player1 'X'
#define player2 'O'
#define blank '.'

bool read(         char board[][size], const char* fileName);
bool write(     const char board[][size], const char* fileName);
void display(   const char board[][size]);
bool didWin(    const char board[][size], char turn);
bool diagonal(  const char board[][size], char turn);
bool straightMatch(const char board[][size], char turn);



/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
   char board[size][size];

   // read the board
   char fileName[256];
   cout << "Enter source filename: ";
   cin  >> fileName;
   if (!read(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   // display the board
   display(board);

   // write the board to a file
   //cout << "Enter destination filename: ";
   //cin  >> fileName;
   //if (!write(board, fileName))
   //{
   //   cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
   //   return 1;
  // }

   return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][size], const char* fileName)
{
   assert(*fileName);

   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return false;

   // read 9 symbols, hopefully they are . X O
   for (int r = 0; r < size; r++)
      for (int c = 0; c < size; c++)
      {
         fin >> board[r][c];
         assert(!fin.fail());
         assert(board[r][c] == player1 ||
                board[r][c] == player2 ||
                board[r][c] == blank);
      }

   // close the file
   fin.close();
   return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][size], const char* fileName)
{
   assert(fileName[0] != '\0');

   // open the file
   ofstream fout(fileName);
   if (fout.fail())
      return false;

   // write my 9 symbols
   for (int r = 0; r < size; r++)
      for (int c = 0; c < size; c++)
         fout << board[r][c] << (c == size - 1 ? '\n' : ' ');

   // close it!
   fout.close();
   cout << "File written\n";
   return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][size])
{

   //determine line spaceing
   string line;
   for (int i = 0; i < size - 1; i++)
   {
      line += "---+";
   }

   line += "---\n";

   // loop through each row
   for (int r = 0; r < size; r++)
   {
      // only the first row is not preceeded with the --+-- magic
      if (r != 0)
         cout << line;

      // now, on each row, do the column stuff
      for (int c = 0; c < size; c++)
      {
         // display a space for the dot
         if (board[r][c] == blank)
            cout << "   ";
         else
            cout << " " << board[r][c] << " ";

         // end with a | or a newline
         cout << (c == size - 1? '\n' : '|');
      }
   }

   // display who won
   if (didWin(board, player1))
      cout << player1 << " won!\n";
   if (didWin(board, player2))
      cout << player2 << " won!\n";
   
   return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][size], char turn)
{
   return diagonal(board, turn) || straightMatch(board, turn); //|| horizontal(board, turn) || vertical(board, turn);
   //return diagonal(board, turn) || horizontal(board, turn) || vertical(board, turn);
}

/*
 *
 *
 * */
bool diagonal(const char board[][size], char turn)
{

   bool didWin = true;
   
   // check all corners and move in until we are all done
   for (int i = 0, j = size - 1; i < size - 1; i++, j--)
   {

      //check if it's the middle and it's odd, there will only be one space in the middle
      //it must be equal, or we will return false
      if (i == (size + 1) / 2 - 1 && size % 2 != 0)
         return board[i][i] == turn;


      if (!(board[i][i] == turn && board[j][j] == turn) && !(board[j][i] == turn && board[i][j] == turn))
         return false;
      
      /*///////////////
       * how i derived my logic above
      if (!(board[i][i] == turn && board[j][j] == turn))
         didWin = false;

      // we should also check if the first check was successful!
      if (!didWin && !(board[j][i] == turn && board[i][j] == turn))
         didWin = false;
      else
         didWin = true;

      // if false, return right away
      if (!didWin)
         return didWin;

      */////////////////
   }
   return true;
}


/*
 *
 *
 * */
bool straightMatch(const char board[][size], char turn)
{
   int horCounter = 0;
   int verCounter = 0;
   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         if (board[j][i] == turn)
            verCounter++;

         if (board[i][j] == turn)
            horCounter++;
      }

      if (verCounter == size || horCounter == size)
         return true;
      
      verCounter = 0; 
      horCounter = 0; 
   }
   return false;
}
