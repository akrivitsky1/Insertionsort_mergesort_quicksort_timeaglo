// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int& compares, int& memaccesses);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& compares, int& memaccesses);
int Partition(std::vector<int>* numbers, int i, int k, int &comparisons, int &memaccesses);