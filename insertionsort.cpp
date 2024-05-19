// Edited code
// Insertion Sort
//
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"
#include <ctime>

void InsertionSort(std::vector<int>* numbers, int &compares, int &memaccess) {
    int i = 0;
    int j = 0;
    int temp = 0;  // Temporary variable for swap
    for (i = 1; i < numbers->size(); ++i) {
        j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (true) { //goes til loop is over
            if(j > 0) { 
                compares +=1; //compare variable counting num of compares
                memaccess += 2; //counting number of mem access
                if((*numbers)[j] < (*numbers)[j - 1]){ //if element previous is greater than element in front
                    temp = (*numbers)[j]; //swaps
                    (*numbers)[j] = (*numbers)[j - 1]; //swaps
                    (*numbers)[j - 1] = temp; //swaps
                    j--;
                    memaccess += 4; //adds to memaccess
                }else{
                    break; //breaks the loop
                }
            }else{
                break; //breaks the loop
            }   
        }
    }
    return;
}            