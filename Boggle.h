#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H


#include <string>
#include "Dictionary.h"



using namespace std;

const int BOARD_SIZE = 4;
const string DEFAULT_DICTFILE = "dictionary.txt";

class BoardNotInitialized {
    public:
        explicit BoardNotInitialized(string msg) { this->msg = msg; }
        string Msg() { return msg;  }
    private:
        string msg;
};




class Boggle {
    // Recursive backtracking used in the amaze example for Erickson class
    // General idea: Start at each position and then explore all paths originating at the
    //               position being careful not to re-visit grid positions
    // The solution will start with SolveBoard function; which serves as a 'wrapper' for
    // another SolveBoardHelper
    /*
      For each position on the board
        (Find all of the words on the board starting at this position)
                                OR
        (Call SolveBoardHelper starting at the current board position)

            01 02 03 04
            05 06 07 08
            09 10 11 12
            13 14 15 16
     */


public:
    Boggle();  // load "dictionary.txt" into dict
               // initialize each entry of board to the empty string
               // initialize every entry of the of visited to false (0)

    explicit Boggle(string filename);  // load filename into dict
                                       // customized dictionary to load into
                                       // the dictionary variable



    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]); // copy each entry of board to this->board
                                                         // deep copy - using for-loop


    /* Function:
     * Precondition: printBoard to display using the kind of
     * Postcondition:
     */
    void SolveBoard(bool printBoard, ostream& output);

    void SaveSolve(string filename);   // Saves all the words from the last solve.
                                       // Calls the SaveDictionaryFile for the wordsFound
    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;           // all valid words loaded from a dictionary file
                               //
    Dictionary wordsFound;             // words found on the board

    string board[BOARD_SIZE][BOARD_SIZE];    // the board itself
                                             // holds a character matrix

    int visited[BOARD_SIZE][BOARD_SIZE];     // allows us to keep track of letters
                                             // that we've already used before, and
                                             // the path on the board

    void PrintBoard(ostream& output);  // takes 2 different ostreams : cout or ofstream

    int getWordCount(string);


    // recursively check the surrounding 8 positions
    // void SolveBoardHelper(/* Put any parameters you want/need here */);
    void SolveBoardHelper(int, int, string &, bool, ostream&);
};

#endif //BOGGLE_BOGGLE_H
