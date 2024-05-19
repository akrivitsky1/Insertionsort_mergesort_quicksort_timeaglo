#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    // Open the two files that contain JSON objects
    std::ifstream file1(argv[1]); // opens object 1
    std::ifstream file2(argv[2]); //opens object 2
    // Read the contents of the files into json objects
    json json1; // json object 1
    json json2; //json object 2
    file1 >> json1; //writes it to json 1
    file2 >> json2; //writes it to json 2
    // Create a json object to store the output
    json output;
    // Create a json object to store the metadata
    json metadata;
    // Store the array size and name of each file in the metadata
    metadata["File1"]["arraySize"] = json1.begin()->size();  // If this doesn't work try json1.begin()->size()
    metadata["File1"]["name"] = argv[1]; // sets file1 to argv 1
    metadata["File1"]["numSamples"] = json1.size() - 1; //sets size to json1
    metadata["File2"]["arraySize"] = json2.begin()->size();  // If this doesn't work try json1.begin()->size()
    metadata["File2"]["name"] = argv[2]; //sets name to agrv 2
    metadata["File2"]["numSamples"] = json2.size() - 1; //sets it to json2 size 

    // Create a json object to store the mismatches
    json mismatches; //json object called mismatch
    int counter = 0; //integer called counter
    bool ifFoundCounter = false; //boolean called if foundcounter

    // Iterate through the elements of Sample1 in each file
    for (json::iterator it = json1.begin(); it != json1.end(); ++it) {
        mismatches.clear(); //clears mismatches
        if (it.key().find("Sample") != std::string::npos) { //if finds sample in file does it
            if(json2.find(it.key()) != json2.end()){ //if finds key in sample
                for (int i = 0; i < json1[it.key()].size(); i++) { //does it loop
                    // If the elements are not equal, store the mismatches in the mismatches object
                    if (json1[it.key()][i] != json2[it.key()][i]) { 
                        ifFoundCounter = true; //makes boolean true
                        mismatches[std::to_string(i)] = {json1[it.key()][i], json2[it.key()][i]}; //stores it in mismatches
                    }
                }
                if(ifFoundCounter){ //if true
                    counter++; //increment counter
                    ifFoundCounter = false; //set back to equal
                    // Store the mismatches in the output object
                    output[it.key()][argv[1]] = json1[it.key()]; 
                    output[it.key()]["Mismatches"] = mismatches;
                    output[it.key()][argv[2]] = json2[it.key()];
                }
            }
        }
    }
    // Store the number of samples with conflicting results in the metadata
    metadata["samplesWithConflictingResults"] = counter;
    // Store the metadata in the output object
    output["metadata"] = metadata;
    // Print the output
    std::cout << output.dump(5) << std::endl;
    return 0;
}