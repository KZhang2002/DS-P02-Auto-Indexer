//Prototypes, design, and comments done by Mark Fontenot
//Implementation done by Kenny Zhang

#ifndef PA01_SENTIMENT_DSSTRING_H
#define PA01_SENTIMENT_DSSTRING_H

#include <iostream>
#include <cstring>
#include "DSVector.h"

class DSString{

private:
    char* myString;

public:

    /**
     * Constructors and destructor
     **/
    DSString();
    DSString(const char* str);
    DSString(const DSString&);
    ~DSString();

    /**
     * Overloaded Assignment Operators
     */
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);

    /**
     * Overloaded non-modifying string concat
     * @return
     */
    DSString operator+ (const DSString&);
    DSString operator+ (const char*);

    /**
     * Standard relational operators.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a DSString object
     *    one that takes a null-terminated c-string
     *
     **/

    bool operator== (const char*);
    bool operator== (const DSString&);
    bool operator> (const DSString&);
    bool operator> (const char*);
    bool operator< (const DSString& str);
    bool operator< (const char* str);

    /**
     * Subscript operator to access a particular character of a DSString object
     * @return the character requested by reference
     */
    char& operator[] (const int);

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength();

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/
    DSString substring(int start, int numChars);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str();

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream&, const DSString&);


    ///My Functions

    DSString clean();
    DSString lowerStr();
    DSString removePunct();

    DSVector<DSString> decompose();

    int findWord(DSString word);
    int findWord(DSString word, int pos);

    int find(DSString word);
    int find(DSString word, int pos);
};



#endif //PA01_SENTIMENT_DSSTRING_H
