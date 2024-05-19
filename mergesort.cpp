// Merge Sort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"
void MergeSort(std::vector<int>* numbers, int& compares, int& memaccess) {
    MergeSortRecurse(numbers, 0, numbers->size() - 1, compares, memaccess);
}

void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& compares, int& memaccess) { //adds the memaccess and compares storage
    int j = 0;
    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSortRecurse(numbers, i, j, compares, memaccess);
        MergeSortRecurse(numbers, j + 1, k, compares, memaccess);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k, compares, memaccess);
    }
}
void Merge(std::vector<int>* numbers, int i, int j, int k, int& compares, int& memaccess) { //adds the memaccess and compares storage
    int mergedSize = k - i + 1;                // Size of merged partition
    int mergePos = 0;                           // Position to insert merged number
    int leftPos = 0;                           // Position of elements in left partition
    int rightPos = 0;                           // Position of elements in right partition
    std::vector<int> mergedNumbers;
    mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
    // for merged numbers

    leftPos = i;                               // Initialize left partition position
    rightPos = j + 1;                           // Initialize right partition position

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        memaccess += 4;  // increment memory accesses for reading left and right partitions
        if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
            mergedNumbers[mergePos] = (*numbers)[leftPos];
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = (*numbers)[rightPos];
            ++rightPos;
        }
        ++mergePos;
        ++compares;  // increment number of compares
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        memaccess += 2;  // increment memory accesses for reading left partition
        mergedNumbers[mergePos] = (*numbers)[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        memaccess += 2;  // increment memory accesses for reading right partition
        mergedNumbers[mergePos] = (*numbers)[rightPos];
        ++rightPos;
        ++mergePos;
    }

// Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        memaccess += 2; // increment memory access for writing to numbers
        (*numbers)[i + mergePos] = mergedNumbers[mergePos];
    }
}