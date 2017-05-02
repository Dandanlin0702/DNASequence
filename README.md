# DNASequence
Academic Project - An interactive console program, implemented using Hash Tables

### Project
   **Hashing**

### Completed Assignment
   All parts of the Assignment were completed
      - QuadraticProbing
      - LinearProbing
      - DoubleHashing
      - SpellCheck

      ### Background
         Note:
            Majority of codes in QuadraticProbing.h, LinearProbing.h and DoubleHashing.h were provided by the instructor.

            Following Functions Were Added for Completion of The Project:
               size_t NumberOfCollisions() {
                  return number_of_collisions;
               }

               size_t NumberOfItems() {
                  return current_size_;
               }

               size_t TableSize() {
                  return array_.capacity();
               }

               double LoadFactor() {
                  // Calculate LoadFactor
                  return static_cast<double>(NumberOfItems())/static_cast<double>(TableSize());
               }

            And the FindPos Function Was Edited.

### Problem Encountered
   No problems encountered

### Compilation & Execution
   **1. How To Compile**
      This project can be executed under linux environment, user who have the command line installed they can compile the project by simply typing:
         make (to compile CreateAndTestHash)
         makeall (to compile all the files)

   **2. How To Execute**
      CreateAndTestHash:
         User can run the CreateAndTestHash by input following command on terminal after Compiling
            CreateAndTestHash <words file name> <query words file name> <flag>
         Where
            <words file name> could be words.txt
            <query words file name> could be query_words.txt
            <flag> should be “quadratic” for quadratic probing, “linear” for linear probing, and “double” for double hashing
      SpellCheck
         User can execute the SpellCheck by using following command
            SpellCheck <document file> <dictionary file>
         Where
            <document file> can be either document1_short.txt or document1.txt
            <dictionary file> will be wordsEn.txt


### Files Included
   **Files Created For Project Completion**
      DoubleHashing.h
      LinearProbing.h
      SpellCheck.cpp

   **Files Provided By Instructor**
      QuadraticProbing.h
      CreateAndTestHash.cpp

   **Input Files Provided By Instructor For Testing**
      For TestHash:
         words.txt
         query_words.txt

      For SpellChecker
         document1.txt
         document1_short.txt
         wordsEn.txt

   **Compilation & Documentation**
      Makefile
      README.md

### Project Completed By
   Dandan Lin
   03/23/17

cd Documents/School/2017_Spring/335_System_Analysis/Assignment/Assignment_3/Hashing
