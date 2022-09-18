//
// Created by mark on 6/2/2021.
//

#include "DSString.h"

//constructors
DSString::DSString() {
    myString = nullptr;
}

DSString::DSString(const char* str) {
    if(str == nullptr) {
        myString = nullptr;
    } else {
        myString = new char[strlen(str) + 1];
        strcpy(myString, str);
    }
}

DSString::DSString(const DSString& str) {
    myString = new char[strlen(str.myString) + 1];
    strcpy(myString, str.myString);
}

DSString::~DSString() {
    delete[] myString;
}

///Operator Overloads

//Assignment Operators
DSString& DSString::operator= (const char* str){
    myString = new char[strlen(str) + 1];
    strcpy(myString, str);
    return *this;
}

DSString& DSString::operator= (const DSString& str){
    if (this != &str) {
        delete[] myString;
        myString = new char[strlen(str.myString) + 1];
        strcpy(myString, str.myString);
    }
    return *this;
}

//Overloaded non-modifying string concat
DSString DSString::operator+ (const DSString& str){
    DSString concat;
    concat.myString = new char[strlen(myString) + strlen(str.myString) + 1];
    concat = strcat(myString, str.myString);
    return concat;
}

DSString DSString::operator+ (const char* ltr){
    DSString concat;
    concat.myString = new char[strlen(myString) + 1];
    concat = strcat(myString, ltr);
    return concat;
}

//Relational Operators
bool DSString::operator== (const char* str){
    return strcmp(myString, str) == 0;
}
bool DSString::operator== (const DSString& str){
    return strcmp(myString, str.myString) == 0;
}

bool DSString::operator> (const char* str){
    return strcmp(myString, str) > 0;
}
bool DSString::operator> (const DSString& str){
    return strcmp(myString, str.myString) > 0;
}
bool DSString::operator< (const char* str){
    return strcmp(myString, str) < 0;
}
bool DSString::operator< (const DSString& str){
    return strcmp(myString, str.myString) < 0;
}

//Subscript Operator
char& DSString::operator[] (const int num){
    return myString[num];
}

//getLength() returns the number (count) of characters in the string.
//does not include null terminator
int DSString::getLength(){
    return strlen(myString);
}

/**
 * The substring method returns a string object that contains a
 * sequence of characters from this string object.
 *
 * param start - the index of where to start
 * param numChars - the number (count) of characters to copy into
 *    the substring
 * @return a DSString object containing the requested substring
 **/
DSString DSString::substring(int start, int numChars) {
    char str[numChars + 1];
    int ltrnum = 0;

    for (int i = start; i < start + numChars; i++) {
        str[ltrnum] = myString[i];
        ltrnum++;
    }

    str[ltrnum] = '\0';
    DSString substr = str;
    return substr;
}

/**
 * the c_str function returns a null-terminated c-string holding the
 * contents of this object.
 **/
char* DSString::c_str(){
    return myString;
}

/**
 * Overloaded stream insertion operator to print the contents of this
 * string to the output stream in the first argument.
 **/
std::ostream& operator<< (std::ostream& os, const DSString& str){
    os << str.myString;
    return os;
}

///My Functions

/**
 * Eliminates all non alpha characters from a string and makes all characters lowercase
 * @return - cleaned DSString
 */
DSString DSString::clean() {
    int curLtr = 0;
    int newCurLtr = 0;
    char temp[2048];

    while (myString[curLtr])
    {
        if(isalpha(myString[curLtr])) {
            temp[newCurLtr] = tolower(myString[curLtr]);
            newCurLtr++;
        }
        curLtr++;
    }
    temp[newCurLtr] = '\0';

    return DSString(temp);
}

/**
 * Makes all characters lowercase
 * @return - lowercased string
 */
DSString DSString::lowerStr() {
    int curLtr = 0;
    char temp[2048];

    while (myString[curLtr])
    {
        if(isalpha(myString[curLtr]) && isupper(myString[curLtr])) {
            temp[curLtr] = tolower(myString[curLtr]);
        } else {
            temp[curLtr] = myString[curLtr];
        }
        curLtr++;
    }
    temp[curLtr] = '\0';

    return DSString(temp);
}

/**
 * Removes all punctuation from a DSString
 * @return unpunctuated string
 */
DSString DSString::removePunct() {
    int curLtr = 0;
    char temp[2048];

    while (myString[curLtr]) {
        if (ispunct(myString[curLtr]) != 0) {
            temp[curLtr] = ' ';
        } else {
            temp[curLtr] = myString[curLtr];
        }
        curLtr++;
    }
    temp[curLtr] = '\0';

    return DSString(temp);
}

/**
 * Creates a vector of all the words in a DSString.
 * @return - vector of words from string
 */
DSVector<DSString> DSString::decompose() {
    int curLtr = 0;
    int wordStart = 0;
    int wordLen = 0;
    char buffer = myString[0];
    int i = 1;
    DSVector<DSString> vect;

    //Continually reads characters until a space is encountered
    //If the next character is not also a space and the substring
    //does not have a length of 0, the word is added to the wordList
    //wordLen increases with every letter and resets to 0 after a word is found
    //wordStart is set to curLtr after the end of a word is found
    while(buffer != '\0') {
        if(buffer == ' ' && myString[curLtr + 1] != ' ') {
            vect.push_back(DSString(substring(wordStart, wordLen)));
            i++;
            wordStart = curLtr + 1;
            wordLen = 0;
        }
        curLtr++;
        wordLen++;
        buffer = myString[curLtr];
    }
}

/**
 * Returns the index of word "word"'s position. Checks if there is a space before and after the word.
 * @param word - word being searched for
 * @return - index of word
 */
int DSString::findWord(DSString word) {
    DSString str = lowerStr();
    for (int i = 0; i < this->getLength(); i++) {
        if (myString[i] == word[0] && (i == 0 || isalpha(myString[i - 1]) == 0)) {
            int j = 1;
            i++;
            while (j < word.getLength()) {
                if (myString[i] == word[j]) {
                    j++;
                    i++;
                    if (j == word.getLength()) {
                        if (i == this->getLength() || isalpha(myString[i]) == 0) {
                            return i - word.getLength();
                        }
                    }
                    continue;
                }
                break;
            }
        }
    }
    return -1;
}

/**
 * Returns the index of word "word"'s position. Only searches indices after "pos".
 * Checks if there is a space before and after the word.
 * @param word - word being searched for
 * @param pos - position where search should start
 * @return index of word
 */
int DSString::findWord(DSString word, int pos) {
    DSString str = lowerStr();
    for (int i = pos; i < this->getLength(); i++) {
        if (myString[i] == word[0] && (i == 0 || isalpha(myString[i - 1]) == 0)) {
            int j = 1;
            i++;
            while (j < word.getLength()) {
                if (myString[i] == word[j]) {
                    j++;
                    i++;
                    if (j == word.getLength()) {
                        if (i == this->getLength() || isalpha(myString[i]) == 0) {
                            return i - word.getLength();
                        }
                    }
                    continue;
                }
                break;
            }
        }
    }
    return -1;
}

/**
 * Returns the index of word "word"'s position
 * @param word - word being searched for
 * @return - index of word
 */
int DSString::find(DSString word) {
    DSString temp = DSString(myString);
    temp.lowerStr();
    for (int i = 0; i < this->getLength(); i++) {
        if (temp[i] == word[0]) {
            int j = 1;
            i++;
            while (j < word.getLength()) {
                if (temp[i] == word[j]) {
                    j++;
                    i++;
                    if (j == word.getLength()) {
                        return i - word.getLength();
                    }
                    continue;
                }
                break;
            }
        }
    }
    return -1;
}

/**
 * Returns the index of word "word"'s position. Only searches indices after "pos".
 * @param word - word being searched for
 * @param pos - position where search should start
 * @return index of word
 */
int DSString::find(DSString word, int pos) {
    DSString temp = DSString(myString);
    temp.lowerStr();
    for (int i = pos; i < this->getLength(); i++) {
        if (temp[i] == word[0]) {
            int j = 1;
            i++;
            while (j < word.getLength()) {
                if (temp[i] == word[j]) {
                    j++;
                    i++;
                    if (j == word.getLength()) {
                        return i - word.getLength();
                    }
                    continue;
                }
                break;
            }
        }
    }
    return -1;
}


