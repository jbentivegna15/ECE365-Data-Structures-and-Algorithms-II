/*
Joseph Bentivegna
Professor Sable
DSA2 Project 1
This project involved the creation of a hash table and implementing
it into a spell checker program which takes an input file and
determines if a word is spelled correctly from a dictionary inserted
into the hash table.
*/

#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string.h>

int main() {

  std::string dictPath;
  std::string inputPath;
  std::string outputPath;
  std::string line;
  std::string combinedWord;
  bool ignore, longWord, wordDone, finished;
  char c;
  int i, cNUM, lineCount;
  char word [100];

  //instantiate hash table
  hashTable *dictionary = new hashTable(50000);

  std::cout << "Enter name of dictionary: ";
  std::cin >> dictPath;

  clock_t begin = clock();

  std::ifstream dictList (dictPath.c_str());
  if (!dictList) {
    std::cout << "Error: could not open " << dictPath << std::endl;
  }

  //open dictionary file and insert it into the hash table
  if (dictList.is_open()) {
    while (!dictList.eof()) {
      std::getline(dictList, line);
      for (int i = 0; i < line.length(); i++) {
        line[i] = std::tolower(line[i]);
      }
      dictionary->insert(line);
    }
    dictList.close();
  }

  clock_t end = clock();
  double elapsed_secs = ((double)(end-begin)) / CLOCKS_PER_SEC;
  std::cout << "Total time (in seconds): " << elapsed_secs << std::endl;

  std::cout << "Enter name of input file: ";
  std::cin >> inputPath;

  std::cout << "Enter name of output file: ";
  std::cin >> outputPath;

  std::ifstream spellCheck (inputPath.c_str());
  if (!spellCheck) {
    std::cout << "Error: could not open " << inputPath << std::endl;
  }

  std::ofstream outputFile (outputPath.c_str());
  if (!outputFile) {
    std::cout << "Error: could not open " << outputPath << std::endl;
  }

  clock_t begin1 = clock();

  ignore = false;
  longWord = false;
  wordDone = false;
  memset(word, 0, sizeof(word));
  i = 0;
  lineCount = 1;
  combinedWord = "";
  finished = false;

  //read input file one character at a time into a buffer
  if (spellCheck.is_open()) {
    while (!spellCheck.eof()) {
      while (spellCheck.get(c)) {
        //change characters to lowercase
        c = std::tolower(c);
        cNUM = c;

        //check if valid character
        if ((cNUM > 47 and cNUM < 58) or (cNUM > 96 and cNUM < 123) or (cNUM == 45) or (cNUM == 39)) {
          //ignore if number
          if (cNUM > 47 and cNUM < 58) {
            ignore = true;
          }

          finished = false;
          word[i] = c;
          i++;

          if (i > 20) {
            longWord = true;
          }

        } else {
          if (finished == false) {
            wordDone = true;
            finished = true;
          }
        }

        //if non-valid character, determine output
        if (wordDone == true and word[0] != '\0') {
          if (longWord == true and ignore == false) {
            for (int j = 0; j < 20; j++) {
              combinedWord = combinedWord + word[j];
            }
            outputFile << "Long word at line " << lineCount << ", starts: " << combinedWord << std::endl;
            memset(word, 0, sizeof(word));
            i = 0;
            ignore = false;
            longWord = false;
            wordDone = false;
            combinedWord = "";
          } else if (ignore == false) {
            combinedWord = word;
            if (dictionary->contains(combinedWord) != true) {
              outputFile << "Unknown word at line " << lineCount << ": " << combinedWord << std::endl;
            }
            memset(word, 0, sizeof(word));
            i = 0;
            ignore = false;
            longWord = false;
            wordDone = false;
            combinedWord = "";
          } else {
            memset(word, 0, sizeof(word));
            i = 0;
            ignore = false;
            longWord = false;
            wordDone = false;
            combinedWord = "";
          }
         }

        //for counting number of lines
        if (cNUM == 10) {
          lineCount++;
        }
      }
    }
  }

  clock_t end1 = clock();
  double elapsed_secs1 = ((double)(end1-begin1)) / CLOCKS_PER_SEC;
  std::cout << "Total time (in seconds): " << elapsed_secs1 << std::endl;

  spellCheck.close();
  outputFile.close();
  return 0;
}
