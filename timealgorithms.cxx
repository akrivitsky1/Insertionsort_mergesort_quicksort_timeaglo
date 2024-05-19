#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "json.hpp"
#include "mergesort.h"
#include "insertionsort.h"
#include "quicksort.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    // Check for valid number of arguments
    if (argc != 2) { // if argc not equal 2
        std::cerr << "Usage: timealgorithms file.json" << std::endl; //prints error message
        return 1; //ends code
    }

    // Open the JSON file
    std::ifstream json_file(argv[1]); //opens jsonfile
    json json_data; //new json object
    json_file >> json_data; //write json object to file



    // Create the CSV file
    std::ofstream csv_file("timealgorithms.csv"); //new files called timealgorithms
    //write to file
    csv_file << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl; 
    //write to terminal
    std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;
    // Iterate through each sample in the JSON file
    for (json::iterator it = json_data.begin(); it != json_data.end(); ++it) {
        if (it.key().find("Sample") != std::string::npos) { //if equal to sample
            // Get the sample name
            std::string sample_name = it.key(); 
            // Get the array to be sorted
            std::vector<int> numbers = it.value(); //numbers is equal to value
            std::vector<int> copy1 = numbers; //copy the numbers
            std::vector<int> copy2 = numbers; //copy the numbers
            std::vector<int> copy3 = numbers; //copy the numbers

            // Run Insertion Sort
            clock_t start_time = clock(); //start clock
            int insertion_sort_compares = 0; //set new integer
            int insertion_sort_memaccess = 0; //set new integer
            InsertionSort(&copy1, insertion_sort_compares, insertion_sort_memaccess); //run insertion sort
            clock_t end_time = clock(); //end clock time
            double insertion_sort_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //find clock time

            // Run Merge Sort
            start_time = clock(); //start clock
            int merge_sort_compares = 0; //new integer for compares
            int merge_sort_memaccess = 0; //new integer for mem access
            MergeSort(&copy2, merge_sort_compares, merge_sort_memaccess); //run mergesort
            end_time = clock(); //end clock
            double merge_sort_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //get time

            // Run Quick Sort
            //start_time = clock();
            int quick_sort_compares = 0; // new int for compares
            int quick_sort_memaccess = 0; //new int for mem access
            start_time = clock(); //start clock
            QuickSort(&copy3, quick_sort_compares, quick_sort_memaccess); //run quicksort
            end_time = clock(); //end clock
            double quick_sort_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //get clock time

            // Write the data to the CSV file
            csv_file << sample_name << "," << std::fixed << std::setprecision(6) << insertion_sort_time << "," << insertion_sort_compares << "," << insertion_sort_memaccess << "," << merge_sort_time << "," << merge_sort_compares << "," << merge_sort_memaccess << "," << quick_sort_time << "," << quick_sort_compares << "," << quick_sort_memaccess << std::endl;
            std::cout <<  sample_name << "," << std::fixed << std::setprecision(6) << insertion_sort_time << "," << insertion_sort_compares << "," << insertion_sort_memaccess << "," << merge_sort_time << "," << merge_sort_compares << "," << merge_sort_memaccess << "," << quick_sort_time << "," << quick_sort_compares << "," << quick_sort_memaccess << std::endl;
    
        }
    }    
    return 0;
}