#include "Dictionary.h"
#include "Boggle.h"
#include <iomanip>
// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    // // initialize each entry of board to the empty string
    // // initialize every entry of the of visited to false (0)

    dict = Dictionary(DEFAULT_DICTFILE);


    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = "";
            visited[i][j] = false;
        }
}

Boggle::Boggle(string filename) {

    dict = Dictionary(filename);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = "";
            visited[i][j] = false;
        }
}


void Boggle::SetBoard(string board[4][4]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            this->board[i][j] = board[i][j];
}


void Boggle::SolveBoard(bool printBoard, ostream &output) {

    // When solving the board, you have the option of printing out the board or not
    // displays contents of board by row for both dictionaries
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            string word = "";
            SolveBoardHelper(i, j, word, printBoard, output);
        }

}

void Boggle::SolveBoardHelper(int row, int col, string &word, bool printBoard, ostream& output) {

    // Base Case
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE )   return;

    // Check if visited position
    // if not, keep track of paths taken and update word parameter
    if (visited[row][col])  return;

    visited[row][col] = word.size() + 1;
    word += board[row][col];

    // isPrefix method - to prevent exploring non-producible paths; update markings
    if (!dict.IsPrefix(word)) {
        word.erase(word.length() - 1);
        visited[row][col] = false;
        return;
    }

    if (dict.IsWord(word) && !wordsFound.IsWord(word)) {       // check word in dictionary, and
        wordsFound.AddWord(word);                                // not a duplicate in wordsFound dictionary

        while (word.length() > 0 && word[word.size()-1] == ' ')
            word.pop_back();

        if (printBoard) {
            output << "Word: " << word << endl
                   << "Number of Words: " << wordsFound.WordCount() << endl;
            PrintBoard(output);
        }
        else
            output << wordsFound.WordCount()
                   << setw(1) << left << "\t"
                   << left << word << endl;

    }

    SolveBoardHelper(row - 1, col, word, printBoard, output);      // North
    SolveBoardHelper(row - 1, col + 1, word, printBoard, output);  // North-East
    SolveBoardHelper(row, col + 1, word, printBoard, output);      // East
    SolveBoardHelper(row + 1, col + 1, word, printBoard, output);  // South-East

    SolveBoardHelper(row + 1, col, word, printBoard, output);      // South
    SolveBoardHelper(row + 1, col - 1, word, printBoard, output);  // South-West
    SolveBoardHelper(row, col - 1, word, printBoard, output);      // West
    SolveBoardHelper(row - 1, col - 1, word, printBoard, output);  // North-West

    word.erase(word.length() - 1);  // update parameters
    visited[row][col] = false;
}


void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}


void Boggle::PrintBoard(ostream &output) {
    // only for printing once we find a word and given if the user wants to display board


    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++)
            if (visited[i][j])  output << " \'" << board[i][j] << "\' ";
            else
                output << "  " << board[i][j] << "  ";
        output << "\t";

        for (int j = 0; j < BOARD_SIZE; j++)
            output << "  " << to_string(visited[i][j]) << "  ";
        output << endl;
    }
    output << endl;
}



















