#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;
int main(int argc, char** argv) {
    if (argc != 2) { //parsing the arguments
        cout << "Usage: sortedverification file.json" << endl; //error if missing args
        return 1; //end code
    }
//parse json file
    json data = json::parse(ifstream(argv[1])); //sets it to a json data
    json result; //creating json result
    int samplesWithInversions = 0; //integer with samples of inversions
    for (json::iterator it = data.begin(); it != data.end(); ++it) { //for loop going through the data
        if (it.key().find("Sample") != string::npos) { //if it is equal to sample
            json inversions; //create json object inversions
            int inversionsCounter = 0; //integer counting inversions
            for (int i = 0; i < it.value().size() - 1; i++) { //for loop getting value 
                if (it.value()[i] > it.value()[i + 1]) { //if value is greater than next one
                    inversionsCounter++; //increment inversions
                    inversions[to_string(i)].push_back(it.value()[i]); //push it back to inversions
                    inversions[to_string(i)].push_back(it.value()[i + 1]); //push back to inversions
                }
            }
            if (inversionsCounter > 0) { //has inversions
                samplesWithInversions++; //increase count 
                result[it.key()]["ConsecutiveInversions"] = inversions; //pushback to result
                result[it.key()]["sample"] = it.value(); //push the value to result
            }
        }
    }
    result["metadata"] = data["metadata"]; //add to file
    result["metadata"]["file"] = argv[1]; //add to file
    result["metadata"]["samplesWithInversions"] = samplesWithInversions; //add to file
    cout << result.dump(4) << endl; //clears json object
    return 0; //ends
}