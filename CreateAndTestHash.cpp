/**********************************************************************
File:          CreateAndTestHash.cpp
Author:        Dandan Lin
Date:          3/28/2017

Description:  This is a tseting program, whcich does following
              A) Read all words from a given text file words.txt and insert them into a hash table.
              After the table is created print out the total number of elements in the table (N), the size of table (T), the load factor (N/T), the total number of collisions (C), and the average number of collisions (C/N).

              B) Check whether each word in another given file query_words.txt is in the hash table or not. For each word that is found print the word, the string “Found” and the number of probes used. For each word not found, print the word, the string “Not Found” and the number of probes used.
**********************************************************************/

#include "QuadraticProbing.h"
#include "DoubleHashing.h"
#include "LinearProbing.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void
TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "\nTestFunctionForHashTables..." << endl;
  cout << "Words filename: \n   " << words_filename << endl;
  cout << "Query filename: \n   " << query_filename << endl;
  hash_table.MakeEmpty();

  // Read all words from a given text file words.txt & insert them into a hash table.
  ifstream in_words(words_filename);
  ifstream in_query(query_filename);
  string word, query;

  if (!in_words.good()) {
     cout << "Unable to open file " << words_filename << ". Pease double check. \n";
  }

  while (in_words.good()) {
     while (in_words >> word) {
        hash_table.Insert(word);
     }
  }

  size_t number_of_collisions = hash_table.NumberOfCollisions();
  size_t number_of_items = hash_table.NumberOfItems();
  size_t table_size = hash_table.TableSize();
  double load_factor = hash_table.LoadFactor();

  cout << "Collisions: \n   " << number_of_collisions << endl;
  cout << "Number of items: \n   " << number_of_items << endl;
  cout << "Size of hash table: \n   " << table_size << endl;
  cout << "Load factor: \n   " << load_factor << endl;
  cout << "Average number of collisions: \n   " << static_cast<double>(number_of_collisions)/static_cast<double>(number_of_items) << endl;
  cout << endl;

/******************************************************************************************
   Check whether each word in another given file query_words.txt is in the hash table
   or not. For each word that is found print the word, the string “Found” and the
   number of probes used. For each word not found, print the word, the string “Not
   Found” and the number of probes used.
*******************************************************************************************/

   if (!in_query.good()) {
      cout << "Unable to open file " << query_filename << ". Pease double check. \n";
   }

   while (in_query.good()) {
      while (getline(in_query, query)) {
         size_t number_of_probes = 1;
         if (hash_table.Contains(query, number_of_probes)) {
            //size_t number_of_probes = hash_table.NumberOfProbes();
            cout << "\"" << query << "\" Found. \n   Number of probes: " << number_of_probes << endl;
         } else if (!hash_table.Contains(query, number_of_probes)) {
            //size_t number_of_probes = hash_table.NumberOfProbes();
            cout << "\"" << query << "\" Not Found. \n   Number of probes: " << number_of_probes << endl;
         }
      }
   }

   cout << endl;
}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Uknown tree type \n   " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
