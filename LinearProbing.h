/**********************************************************************
   File:    LinearProbing.h
   Author:  Dandan Lin
   Date:    3/28/2017
**********************************************************************/

#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

// Linear probing implementation.
template <typename HashedObj>
class HashTableLinear {
   public:
      enum EntryType {ACTIVE, EMPTY, DELETED};

      explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size)) { MakeEmpty(); }

      bool Contains(const HashedObj & x, size_t &number_of_probes) const {
         return IsActive(FindPos(x, number_of_probes));
      }

      bool Contains(const HashedObj & x) const {
         return IsActive(FindPos(x));
      }

      void MakeEmpty() {
         current_size_ = 0;
         for (auto &entry : array_)
            entry.info_ = EMPTY;
      }

   bool Insert(const HashedObj & x) {
      // Insert x as active
      size_t current_pos = FindPos(x);
      if (IsActive(current_pos))
         return false;

      array_[current_pos].element_ = x;
      array_[current_pos].info_ = ACTIVE;

      // Rehash; see Section 5.5
      if (++current_size_ > array_.size() / 2)
         Rehash();
      return true;
   }

   bool Insert(HashedObj && x) {
      // Insert x as active
      size_t current_pos = FindPos(x);
      if (IsActive(current_pos))
         return false;

      array_[current_pos] = std::move(x);
      array_[current_pos].info_ = ACTIVE;

      // Rehash; see Section 5.5
      if (++current_size_ > array_.size() / 2)
         Rehash();

      return true;
   }

   bool Remove(const HashedObj & x) {
   size_t current_pos = FindPos(x);
   if (!IsActive(current_pos))
   return false;

   array_[current_pos].info_ = DELETED;
      return true;
   }

/*******************************************************************************
   Five public functions added to compute:
      NumberOfCollisions
      NumberOfProbes
      NumberOfItems
      LoadFactor
      TableSize
*******************************************************************************/
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
/*
   size_t NumberOfProbes() {
      return number_of_probes;
   }
*/
/*******************************************************************************
*******************************************************************************/

   private:
      struct HashEntry {
         HashedObj element_;
         EntryType info_;

         HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY):element_{e}, info_{i} { }

         HashEntry(HashedObj && e, EntryType i = EMPTY) :element_{std::move(e)}, info_{ i } {}
      };

/*******************************************************************************
Two Private members added for computeing NumberOfCollisions and NumberOfProbes
*******************************************************************************/
      mutable size_t number_of_collisions = 0;
      //mutable size_t number_of_probes = 1;
/*******************************************************************************
*******************************************************************************/

      std::vector<HashEntry> array_;
      size_t current_size_;

      bool IsActive(size_t current_pos) const {
         return array_[current_pos].info_ == ACTIVE;
      }

      size_t FindPos(const HashedObj & x) const {
         size_t offset = 1;
         size_t current_pos = InternalHashFirst(x);

         while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
            number_of_collisions++; // Count the number of collisions

            current_pos += offset;  // Compute ith probe.

            offset ++;
            if (current_pos >= array_.size()) {
               current_pos -= array_.size();
            }
         }
         return current_pos;
      }

      size_t FindPos(const HashedObj & x, size_t &number_of_probes) const {
         size_t offset = 1;
         size_t current_pos = InternalHashFirst(x);

         while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
            number_of_collisions++; // Count the number of collisions
            number_of_probes ++;

            current_pos += offset;  // Compute ith probe.

            offset ++;
            if (current_pos >= array_.size()) {
               current_pos -= array_.size();
            }
         }
         return current_pos;
      }

      void Rehash() {
         std::vector<HashEntry> old_array = array_;

         // Create new double-sized, empty table.
         array_.resize(NextPrime(2 * old_array.size()));
         for (auto & entry : array_)
            entry.info_ = EMPTY;

         // Copy table over.
         current_size_ = 0;
         for (auto & entry :old_array)
            if (entry.info_ == ACTIVE)
               Insert(std::move(entry.element_));
      }

      size_t InternalHashFirst(const HashedObj & x) const {
         static std::hash<HashedObj> hf;
         return hf(x) % array_.size( );
      }
};

   #endif
