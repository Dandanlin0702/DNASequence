/**********************************************************************
***********************************************************************
File:          SpellCheck.cpp
Author:        Dandan Lin
Date:          3/28/2017

Description:  This SpellCheck program will
   1. Output all of the misspelled words in the provided document.
   2. Correct the misspelled words by conducting following
      a) Adding one character in each possible position
      b) Removing one character from the word
      c) Swapping adjacent characters in the word
**********************************************************************/

#include "QuadraticProbing.h"
#include "DoubleHashing.h"
#include "LinearProbing.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

template <typename HashTableType>
void SpellChecker(HashTableType &hash_table, const string &document_filename, const string &dictionary_filename) {
   cout << "\nSearching through " << document_filename << ". Checking for misspelled words now. \n\n";
   hash_table.MakeEmpty();

   ifstream in_dictionary(dictionary_filename);
   // Dictionary_word is the words in the dictionary document
   string dictionary_word;

   if (!in_dictionary.good()) {
      cout << "Unable to open dictionary " << dictionary_filename << ". Pease double check. \n";
   }

   // Insert dictionary into the Hash table
   while(in_dictionary >> dictionary_word) {
      if (dictionary_word.length() > 0) {
         hash_table.Insert(dictionary_word);
      }
   }

   ifstream in_document(document_filename);

   if (!in_document.good()) {
      cout << "Unable to open document file " << document_filename << ". Pease double check. \n";
   }

   string line;
   string target_word;
   vector<string> candidate_words;
   /* We first read the document word by word and convert all the uppercase strings to lowercase string and then check if it is in the dictionary
   */
   map<string, vector<string>> potential_wrong_words;
   map<string, vector<string>> ::iterator itr;

   while (in_document >> target_word && target_word.length() > 0) {
      for (size_t i = 0; i < target_word.length(); ++i) {
         if('\'' == target_word[i]) {
            while(i < target_word.length()) {
               target_word = target_word.substr(0, target_word.length()-i);
            }
         } else if (isalpha(target_word[i])) {
            target_word[i] = tolower(target_word[i]);
         } else if (target_word[i] == '-') {
            ;
         } else {
            target_word.erase(target_word.begin() + i);
  			   --i;
         }
      }

      // Start checking if the word is missspelled
      if (target_word.length() > 1 && !hash_table.Contains(target_word)) {
         bool word_found = false;

         // a) Adding one character in each possible position
         for (size_t i = 0; i < target_word.length(); ++i) {
            string temp1 = target_word;
            char ch;
            for (ch = 'a'; ch <= 'z'; ch++) {
               temp1.insert(i, 1, ch);
               if (hash_table.Contains(temp1)) {
                  word_found = true;
                  temp1 += "(case a)";
                  candidate_words.push_back(temp1);

                  temp1 = target_word;
               } else {
                  temp1 = target_word;
               }
            }
         } // Adding one character in each possible position finished

         // b) Removing one character from the word
         for (size_t i = 0; i < target_word.length(); ++i) {
            char target_char = target_word[i];
            // Remove the char
            auto itr = target_word.begin();
            itr += i;
			   target_word.erase(itr);

            if (!hash_table.Contains(target_word)) {
               target_word.insert(itr, target_char);
            } else {
               string temp1 = target_word;
               temp1 += "(case b)";
               candidate_words.push_back(temp1);
               target_word.insert(itr, target_char);
            }
         } // Removing one character finished

         // c) Swapping adjacent characters in the word
         for (size_t i = 0; i < target_word.length(); i++) {
            if (i != target_word.length()-1) {
               // Make the swap, then see if it succeeds.
	    	      swap(target_word[i], target_word[i+1]);
	    	      if (!hash_table.Contains(target_word)) {
                  // Put the words in original order
	    		      swap(target_word[i+1], target_word[i]);
               } else {
                  string temp1 = target_word;
                  temp1 += "(case c)";
                  candidate_words.push_back(temp1);
                  // Put the words in original order
                  swap(target_word[i+1], target_word[i]);
               }
            }
	      } // Swapping adjacent characters finished
         // Put the missspelled word and its complimentary to a map
         potential_wrong_words.insert(make_pair(target_word, candidate_words));
         candidate_words.clear();
      }
   }

   itr = potential_wrong_words.begin();
   cout << "Following words do not exist in the dictionary " << dictionary_filename << endl;
   while (itr != potential_wrong_words.end()) {
      if (itr->second.size() == 0) {
         cout << "\"" << itr->first << "\" is not in dictionary. \n   No correction found.\n";
      } else if (itr->second.size() >= 1) {
         cout << "\"" << itr->first << "\" is missspelled. Do you mean:\n   ";

         int j = 0;
         while (j != (itr->second).size()) {
            if (j == itr->second.size()-1) {
               cout << itr->first << " -> " << itr->second[j] << " ";
            } else {
               cout << itr->first << " -> " << itr->second[j] << "\n   ";
            }
            j++;
         }

         cout << endl;
      }
      itr++;
   }
   cout << endl;
   in_dictionary.close();
   in_document.close();
}

template <typename HashTableType>
void swap(char &A, char &B) {
   char temp = A;
   A = B;
   B = temp;
}

// Testing SpellCheck
int main(int argc, char **argv) {
   if (argc != 3) {
     cout << "Usage: " << argv[0] << " <documentfilename> <dictionaryfilename> " << endl;
     return 0;
   }

   const string documentfilename(argv[1]);
   const string dictionaryfilename(argv[2]);

   HashTableLinear<string> linear_probing_table;
   SpellChecker(linear_probing_table, documentfilename, dictionaryfilename);

   return 0;
}
