#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <algorithm>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

// Error class
class BadDigit{
public:
    string Msg() { return "Error: Invalid string digit.";}
};
class DictionaryError{
    public:
        explicit DictionaryError(string msg) { this->msg = msg; }
        string Msg() { return msg;  }    // returns king of flavor
    private:
        string msg;
};
static int getIndexByChar(char c) {
    if (c == ' ' || !isalpha(c))  throw BadDigit();
    return (int)c - (int)'a';
}
static char getCharByIndex(int integer_val) {
    return (char)(integer_val + (int)'a');
}


class Dictionary
{
    /* Each path to a node represents a word
     * Not every path is a word
     * Part A: prefix tree or "Trie"
     */
    public:
        Dictionary();
        ~Dictionary();  // I will not require this
        Dictionary(const Dictionary& otherDict);    // copy constructor
        explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                    // that this is not a conversion constructor.

        Dictionary& operator=(const Dictionary& otherDict);
        void LoadDictionaryFile(string filename);
        void SaveDictionaryFile(string filename);

        void AddWord(string word);
        void MakeEmpty();

        bool IsWord(string word);
        bool IsPrefix(string word);
        int WordCount();  // Returns total number of words in dictionary

        string GetWord(int index);
        void PrintTree();

    private:

        class Node {
            //
            public:
                bool isWord;        // indicated end of word - path from root node
                Node *letters[NUM_CHARS];   // each node holds 26 pointers in an array - child nodes
                Node() {
                    /* letters: array of pointers
                     * index correspond to letter in alphabet */
                    isWord = false;
                    for (int i = 0; i < NUM_CHARS; i++)
                        letters[i] = nullptr;
                }
                // int getIndexByChar(char c){ return (int)c - (int)'a'; }
                // char getCharByIndex(int integer_val){ return (char)(integer_val + (int)'a'); }
                // It is strongly recommended you create a constructor
                // to set default values
        };
        Node* root;
        int numWords;     // numWords = SUM( All Node->isWord==True )

        // This function is used by the
        // copy constructor and the assignment operator.
        void copyOther(const Dictionary& otherDict);

        // Any private methods you need/want
        // You may change these helpers if you want, but you don't need to.
        void destroyHelper(Node* thisTree);
        void copyHelper(Node*& thisTree, Node* otherTree);
        void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);

        bool isWordHelper(Node*&, string, int);
        // bool isPrefixHelper(Node*&, string, int);
        void PrintHelper(Node *);
};

#endif //BOGGLE_DICTIONARY_H
