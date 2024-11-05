#include "Dictionary.h"


Dictionary::Dictionary() {
    numWords = 0;
    root = new Node();
}

Dictionary::Dictionary(const Dictionary &otherDict) {

    root = new Node();
    copyOther(otherDict);
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();
    root = new Node();
    copyHelper(root, otherDict.root);
    numWords = otherDict.numWords;
}


void Dictionary::copyHelper(Node *&thisTree, Node *otherTree) {
    if (!otherTree) {
        thisTree = nullptr;
        return;
    }
    thisTree->isWord = otherTree->isWord;

    for(int i = 0; i < NUM_CHARS; i++) {
        if (otherTree->letters[i] != nullptr)
            thisTree->letters[i] = new Node;
        copyHelper(thisTree->letters[i], otherTree->letters[i]);
    }
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {

    if (this != &otherDict)
        copyOther(otherDict);
    return *this;
}



Dictionary::~Dictionary() {
    destroyHelper(root);
}

void Dictionary::destroyHelper(Node *thisTree) {

    if (!thisTree)  return;

    for (int i = 0; i < NUM_CHARS; i++)
        destroyHelper(thisTree->letters[i]);

    thisTree = nullptr;
    delete thisTree;
}


Dictionary::Dictionary(string filename) {
    numWords = 0;
    root = new Node();
    root->isWord = false;
    LoadDictionaryFile(filename);
}



void Dictionary::LoadDictionaryFile(string filename) {
    // Load all word saved to a file
    ifstream inFile(filename);
    if (!inFile.is_open())
        throw DictionaryError("File could not be opened");

    string line;
    while (inFile >> line)
        AddWord(line);

    inFile.close();
}

void Dictionary::SaveDictionaryFile(string filename) {
    // Will Save all the words added to the tree into a file
    ofstream out;
    out.open(filename);
    SaveDictionaryHelper(root, "", out);
}

void Dictionary::SaveDictionaryHelper(Node *curr, string currPrefix, ofstream &outFile) {

    if (!curr) return;

    if (curr->isWord)
        outFile << currPrefix << " " << endl;

    for (int i = 0; i < NUM_CHARS; i++)
        SaveDictionaryHelper(curr->letters[i], currPrefix + (char)(i+(int)'a'), outFile);
}



void Dictionary::AddWord(string word) {
    // iterate through each char in given the word
    // calculate index associated with char (cond valid character in function)
    // check nodes existence in path and create if necessary
    Node *curr = root;                                       // start at the root

    for (int i = 0; i < word.size(); i++){

        int charIndex = word[i] - 'a';
        if (charIndex < 'a'-'a' || charIndex > 'z'-'a')              // Note uppercase also invalid
            throw DictionaryError("Invalid character");
        if (curr->letters[charIndex] == nullptr)
            curr->letters[charIndex] = new Node();

        curr = curr->letters[charIndex];
    }
    curr->isWord = true;     // at end of path for given word
    numWords++;
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);
    numWords = 0;
}


bool Dictionary::IsWord(string word) {
   
    if (numWords == 0)  return false;
    return isWordHelper(root, word, 0);
}


bool Dictionary::isWordHelper(Node *&subNode, string word, int index) {
    if (!subNode)   return false;
    if (index < word.size() && subNode->letters[(int)word[index] - (int)'a'])
        return isWordHelper(subNode->letters[(int)word[index] - (int)'a'], word, 1 + index);

    if (index == word.size())
        return subNode->isWord;
}

bool Dictionary::IsPrefix(string word) {
    Node *curr = root;

    for (char c : word) {
        if (!curr->letters[c - 'a'])
            return false;
        curr = curr->letters[c - 'a'];
    }
    return true;
}


int Dictionary::WordCount() {
    return numWords;
}

