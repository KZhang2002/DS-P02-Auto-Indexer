/**
 * Author: Kenny Zhang
 * Github: https://github.com/KZhang2002
 *
 * Project: Auto Indexer
 * Repository: https://github.com/SMUCSE2341/22s-pa02-KZhang2002
 *
 * Class: SMU CS 2341 (4649)
 *
 * Desc: Takes in two text files. One containing the book text and one containing the index terms.
 * Both files are parsed and put into DSVectors. The term list is used to search the book text
 * Outputs index containing terms in alphabetical order and page numbers the terms appear on
 *
 * TLDR: Book text file and terms text file go in. Index come out. Wheeeeeeeeeeeee!
 *
 * Date Released: 3/4/2022
 * Last Updated: 3/4/2022
 */

#include "catch.hpp"
#include <iostream>
#include "indexer.h"
#include "catch_setup.h" //Comment this line for faster runtimes.

int main(int argc, char** argv) {
    if(argc == 1) {
        runCatchTests();
    }
    else {
        //Creates file streams for command line arguments
        std::ifstream bookText(argv[1]);
        std::ifstream termList(argv[2]);
        std::ofstream output(argv[3]);

        //Creates indexer object and executes driver function
        indexer Jackson;
        Jackson.createIndex(bookText, termList, output);

        //Closes file streams
        bookText.close();
        termList.close();
        output.close();
    }
    return 0;
}
