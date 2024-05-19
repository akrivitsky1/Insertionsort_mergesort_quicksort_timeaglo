// Edited code:
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks
#include "quicksort.h"
#include <ctime>

void QuickSort(std::vector<int>* numbers, int& compares, int& memaccesses) {
    QuickSortRecurse(numbers, 0, numbers->size() - 1, compares, memaccesses);
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& compares, int& memaccesses) {
    int j = 0;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }
    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k, compares, memaccesses);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    QuickSortRecurse(numbers, i, j, compares, memaccesses); // change function to have memaccess and compares
    QuickSortRecurse(numbers, j + 1, k, compares, memaccesses);

    return;
}
int Partition(std::vector<int>* numbers, int i, int k, int &comparisons, int &memaccesses) {
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    memaccesses++; //adds to mem acccesss
    pivot = (*numbers)[midpoint];

    l = i;
    h = k;

    while (!done) {
        comparisons++; //increases comparison count
        memaccesses += 1; //increases mem access count
        /* Increment l while numbers[l] < pivot */
        while ((*numbers)[l] < pivot) {
            ++l;
            comparisons++; //increases comparison count
            memaccesses += 1; //increases mem access count
        }
        comparisons++;
        memaccesses += 1;
        /* Decrement h while pivot < numbers[h] */
        while (pivot < (*numbers)[h]) {
            --h;
            comparisons++; //increases comparison count
            memaccesses += 1; //increases mem access count
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = (*numbers)[l];
            (*numbers)[l] = (*numbers)[h];
            (*numbers)[h] = temp;
            ++l;
            --h;
            memaccesses += 4; //increases mem access count
        }
    }
    return h;
}
