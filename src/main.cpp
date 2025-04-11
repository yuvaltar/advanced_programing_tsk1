//main.cpp file
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "BloomFilter.h" 
#include "StdHashFunction.h"
#include "DoubleHashFunction.h"


// --- Sample Hash Function Implementations ---



int main() {
    std::string configLine;
    // read a line from keyboard
    if (!std::getline(std::cin, configLine)) {
        return 1; // Exit if no line provided
    }
    
    std::istringstream configStream(configLine); // Create a stream from the string configLine so we can read from it like it's input.

    int filterSize; 

    configStream >> filterSize; // putting the first argument into filter size 
    
    // The following integers indicate which hash functions to use:
    // 1 for StdHashFunction, 2 for DoubleHashFunction, etc.
    std::vector<std::shared_ptr<IHashFunction>> hashFunctions;
    int hashType;
    // while there is still numbers from user aka (1,2...) like hash funcs
    while (configStream >> hashType) {
        if (hashType == 1) {
            hashFunctions.push_back(std::make_shared<StdHashFunction>());       // for 1 push std into hash vector
        } else if (hashType == 2) {
            hashFunctions.push_back(std::make_shared<DoubleHashFunction>());    // for 2 push Dstd into hash vector
        } else {
            // For any unsupported type, default to StdHashFunction.
            hashFunctions.push_back(std::make_shared<StdHashFunction>());       // for unknown number use std
        }
    }
    // If no hash function is specified, default to one StdHashFunction.
    if (hashFunctions.empty()) {
        hashFunctions.push_back(std::make_shared<StdHashFunction>());
    }
    
    // Create the Bloom Filter using the specified bit array size and hash functions.
    BloomFilter bloom(filterSize, hashFunctions);
    BlackList bl;
    
    // Process commands in an infinite loop
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue; // Skip empty lines.
        }
        
        std::istringstream iss(line);
        int command;
        iss >> command;
        
        std::string url;
        iss >> url; // Expect the URL to be the second token.
        if (url.empty()) {
            continue; // If the URL is missing, ignore this line.
        }
        URL newURL(url); 
        if (command == 1) {
            // Command "1 [URL]" means add the URL to the Bloom filter.
            
            bloom.add(newURL);
        } else if (command == 2) {
            // Command "2 [URL]" means check if the URL is blacklisted.
            // Checks the bloomfilter itself
            if (bloom.possiblyContains(newURL)) {
                // If there is a match within the bloom filter, it checks the blacklist to avoid false-positives.
                bool isBlacklisted = bl.contains(newURL);
                // Printing the relevant true/false
                std::cout << "true, " << (isBlacklisted ? "true" : "false") << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        }
        }
        // If the command does not match the expected format, the line is ignored.
        return 0;
    }
// Uses the built-in std::hash.
// class StdHashFunction : public IHashFunction {
// public:
//     size_t hash(const std::string &s) const override {
//         return std::hash<std::string>{}(s);
//     }
// };

// // A simple "double hash" function demonstration.
// // It applies std::hash once to the input and then rehashes the result.
// class DoubleHashFunction : public IHashFunction {
// public:
//     size_t hash(const std::string &s) const override {
//         size_t h1 = std::hash<std::string>{}(s);
//         size_t h2 = std::hash<std::string>{}(std::to_string(h1));
//         // Combine the two values; here we XOR and shift as an example.
//         return h1 ^ (h2 << 1);
//     }
// };