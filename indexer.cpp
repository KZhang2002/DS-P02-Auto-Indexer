///Indxer cpp file
///Contains function definitions.
///Created by Kenny Zhang

#include "indexer.h"

//Indexers:
//These are empty because there isn't any real need to create anything on construction
indexer::indexer() {

}

indexer::indexer(const indexer&) {

}

indexer::~indexer() {

}

//Driver Function:
/**
 * Creates index from two files, bookText and termList, and outputs this index to "output"
 * @param bookText - Full book text with page numbers
 * @param termList - List of terms to search for
 * @param output - File index should be printed to
 */
void indexer::createIndex(std::ifstream &bookText, std::ifstream &termList, std::ofstream &output) {
    parseTextFile(bookText);
    parseTermsFile(termList);
    //Jackson.outputBookText(); //Uncomment this line if you want to view how the program is parsing the book text.

    removeTermDupes();
    alphabetizeTerms();
    autoIndex();

    sortPageNumbers();
    removePgNumDupes();

    outputIndex(output);
}

/**
 * Parses a file and inputs the data into the indexer's bookTxt
 * @param file - book text file
 */
void indexer::parseTextFile(std::ifstream& file) {
    DSVector<struct para> paraVect; //paragraph vector buffer

    if (file.is_open()) {

        while(file.peek() != EOF) {
            char pgNum[4]; //page number
            char text[2048] = "null"; //text buffer
            struct para temp; //paragraph buffer

            file.ignore(256, '<'); //Skips first character
            file.getline(pgNum, 4, '>'); //gets page number
            if (strcmp(pgNum, "-1") == 0) {
                break; //Stops parsing once page number -1 is reached
            }
            temp.pgNum = DSString(pgNum);
            file.clear();

            do {
                file.getline(text, 90, '\n'); //gets page text
                temp.paraTxt = DSString(text).lowerStr(); //inputs page text as lower case
                file.clear();
                paraVect.push_back(temp); //adds text to paragraph vector buffer
            } while (file.peek() != '<' && file.peek() != EOF);
        }
    }
    bookTxt = paraVect; //sets indexer's book text to paragraph vector buffer
}

/**
 * Parses file and inputs text into the indexer's terms
 * @param file - index terms file
 */
void indexer::parseTermsFile(std::ifstream& file) {
    DSVector<struct term> termVect; //Paragraph vector

    if (file.is_open()) {
        while(file.peek() != EOF) {
            char txt[2048] = "null"; //text buffer
            struct term temp; //term buffer

            file.getline(txt, 2048, '\n'); //gets term text
            temp.word = DSString(txt).lowerStr();
            file.clear();

            termVect.push_back(temp);
        }
    }
    terms = termVect;
}

/**
 * Outputs book text to file "parsetest.txt"
 * @note THIS IS A DEBUG FUNCTION
 */
void indexer::outputBookText() {
    std::ofstream output;
    output.open("parsetest.txt");

    if (output.is_open()) {
        for (int i = 0; i < bookTxt.getSize(); i++) {
            output << "Pg num: " << bookTxt[i].pgNum << '\n';
            output << "Paragraph Text: " << '\n' << bookTxt[i].paraTxt << '\n';
        }
    } else {
        std::cout << "Error has occurred: file is not open" << std::endl;
    }
    output << "End of file";
}

/**
 * Parses bookTxt for terms found in "terms" vector.
 * Adds page number in para's pgNum list to term's pgNum list if term is found.
 */
void indexer::autoIndex() {
    DSString curPgNum("null");
    for (int i = 0; i < bookTxt.getSize(); i++) {
        for (int j = 0; j < terms.getSize(); j++) {
            if (bookTxt[i].paraTxt.removePunct().lowerStr().findWord(terms[j].word.removePunct().lowerStr()) != -1) {
                terms[j].pgNums.push_back(bookTxt[i].pgNum);
            }
        }
    }
}

/**
 * Creates index. Creates letter headers. Outputs term name and page numbers to "output"
 * @param output - File the index is written to
 */
void indexer::outputIndex(std::ofstream &output) {
    //Creates intiial letter header for terms
    char letter = terms[0].word[0];
    if (isalpha(letter))
        letter = toupper(letter);
    output << "[" << letter << "]" << '\n';


    for (int i = 0; i < terms.getSize(); i++) {
        //Creates new letter header if word starts with a new letter
        if (terms[i].word[0] != tolower(letter)) {
            letter = toupper(terms[i].word[0]);
            output << "[" << letter << "]" << '\n';
        }

        int numChar = terms[i].word.getLength() + 2; //number of characters in the current line (includes spaces)
        output << terms[i].word << ": ";
        for (int j = 0; j < terms[i].pgNums.getSize(); j++) {
            //if numChar is greater than 60, creates new line
            if (numChar + terms[i].pgNums[j].getLength() + 2 > 60 && j > 0) {
                output << "\n" << "    ";
                numChar = 4;
            }

            //if pgNum is the last number to be printed, does not print comma after number
            if (j != terms[i].pgNums.getSize() - 1) {
                output << terms[i].pgNums[j] << ", ";
            } else {
                output << terms[i].pgNums[j];
            }

            //Adds the number of characters added to the line
            if (j > 0) {
                numChar += terms[i].pgNums[j].getLength() + 2;
            } else {
                numChar += terms[i].pgNums[j].getLength();
            }
        }
        output << "\n";
    }
}

/**
 * Alphabetizes terms in the term list. Uses selection sort.
 */
void indexer::alphabetizeTerms() {
    //printTerms(); //Debug command, prints terms in the term list to console
    for (int i = terms.getSize() - 1; i >= 0; i--) {
        term temp;
        temp.word = terms[i].word;
        temp.pgNums = terms[i].pgNums;

        int numIndex = i;
        for (int j = i - 1; j >= 0; j--) {
            if (terms[j].word < temp.word) {
                temp.word = terms[j].word;
                temp.pgNums = terms[j].pgNums;
                numIndex = j;
            }
        }
        terms.pop(numIndex);
        terms.push_back(temp);
        //printTerms(); //Debug command, shows changes to term list order as sort progresses
    }
}

/**
 * Compares two pgNum strings. Converts string to int. Used in sortPageNumbers() as a comparison functor
 * @param a
 * @param b
 * @return True if a is less than b
 * @return False if a is greater than b
 */
bool compareDSStringNums(DSString a, DSString b) {
    int numA = std::atoi(a.c_str());
    int numB = std::atoi(b.c_str());
    return (numA < numB);
}

/**
 * Sorts page numbers from lowest to highest. Uses compareDSStringNums() as a comparison functor.
 */
void indexer::sortPageNumbers() {
    for (int i = 0; i < terms.getSize(); i++) {
        std::sort(terms[i].pgNums.begin(), terms[i].pgNums.end(), compareDSStringNums);
    }
}

/**
 * Removes duplicate page numbers.
 * @note works only if list has been sorted before hand.
 */
void indexer::removePgNumDupes() {
    for (int i = 0; i < terms.getSize(); i++) {
        int curIndex = 1;
        while (curIndex < terms[i].pgNums.getSize()) {
            if (terms[i].pgNums[curIndex] == terms[i].pgNums[curIndex - 1]) {
                terms[i].pgNums.pop(curIndex); //pops element at curIndex if it is a duplicate
            } else {
                curIndex++;
            }
        }
    }
}

/**
 * Removes duplicate terms.
 * @details Searches every item in list to see if it matches the current item
 * @details Does this for every term
 * @note pretty inefficient, could definitely be optimized.
 */
void indexer::removeTermDupes() {
    int curIndex = 0;
    while (curIndex < terms.getSize()) {
        int i = curIndex + 1;
        while (i < terms.getSize()) {
            if (terms[curIndex].word == terms[i].word) {
                terms.pop(i);
            }
            i++;
        }
        curIndex++;
    }
}

/**
 * Prints each element's term name and index number in the term list to console
 * @note THIS IS A DEBUG FUNCTION
 */
void indexer::printTerms() {
    cout << "--List Start--" << endl;
    for(int i = 0; i < terms.getSize(); i++) {
        cout << "index " << i << ": " << terms[i].word << " | ";
    }
    cout << "--List End--" << endl;
}


