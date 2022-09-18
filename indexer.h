///Indexer header file
///Contains function prototypes and variable declarations
///Created by Kenny Zhang

#ifndef INC_21F_PA02_INDEXER_H
#define INC_21F_PA02_INDEXER_H

#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <fstream>
#include <algorithm>

/**
 * Used to store every line of text from the book text file.
 * It is called para because this was originally written to store every paragraph.
 * @memberof paraTxt - paragraph text
 * @memberof pgNum - paragraph page number
 */
struct para {
    DSString paraTxt;
    DSString pgNum;
};

/**
 * Terms parsed from terms list file.
 * Each term includes the actual term string and a vector of page numbers it appears on.
 * @memberof word - term
 * @memberof pgNums - page number vector
 */
struct term {
    DSString word;
    DSVector<DSString> pgNums;
};

class indexer {

private:
    DSVector<term> terms; ///List of terms taken from the termslist file
    DSVector<struct para> bookTxt; ///Text of book that is being searched

public:
    //Constructors
    indexer();
    indexer(const indexer&);
    ~indexer();

    //Driver Function
    void createIndex(std::ifstream& bookText, std::ifstream& termList, std::ofstream& output);

    //File Parsers
    void parseTextFile(std::ifstream& file);
    void parseTermsFile(std::ifstream& file);

    //Index Creator
    void autoIndex();

    //Index Sorter/Cleaner
    void alphabetizeTerms();
    void sortPageNumbers();
    void removePgNumDupes();
    void removeTermDupes();

    //Index Output
    void outputIndex(std::ofstream &output);

    //Debug Functions
    void outputBookText();
    void printTerms();

};


#endif //INC_21F_PA02_INDEXER_H
