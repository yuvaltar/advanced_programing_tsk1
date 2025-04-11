//main.cpp file
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "BloomFilter.h" // Assumes BloomFilter and URL classes are declared here

// --- Sample Hash Function Implementations ---

// Uses the built-in std::hash.
class StdHashFunction : public IHashFunction {
public:
    size_t hash(const std::string &s) const override {
        return std::hash<std::string>{}(s);
    }
};

// A simple "double hash" function demonstration.
// It applies std::hash once to the input and then rehashes the result.
class DoubleHashFunction : public IHashFunction {
public:
    size_t hash(const std::string &s) const override {
        size_t h1 = std::hash<std::string>{}(s);
        size_t h2 = std::hash<std::string>{}(std::to_string(h1));
        // Combine the two values; here we XOR and shift as an example.
        return h1 ^ (h2 << 1);
    }
};

int main() {
    std::string configLine;
    // Read the first configuration line (e.g., "256 2 1")
    if (!std::getline(std::cin, configLine)) {
        return 1; // Exit if no configuration input is provided.
    }
    
    std::istringstream configStream(configLine);
    int filterSize;
    configStream >> filterSize;
    
    // The following integers indicate which hash functions to use:
    // 1 for StdHashFunction, 2 for DoubleHashFunction, etc.
    std::vector<std::shared_ptr<IHashFunction>> hashFunctions;
    int hashType;
    while (configStream >> hashType) {
        if (hashType == 1) {
            hashFunctions.push_back(std::make_shared<StdHashFunction>());
        } else if (hashType == 2) {
            hashFunctions.push_back(std::make_shared<DoubleHashFunction>());
        } else {
            // For any unsupported type, default to StdHashFunction.
            hashFunctions.push_back(std::make_shared<StdHashFunction>());
        }
    }
    // If no hash function is specified, default to one StdHashFunction.
    if (hashFunctions.empty()) {
        hashFunctions.push_back(std::make_shared<StdHashFunction>());
    }
    
    // Create the Bloom Filter using the specified bit array size and hash functions.
    BloomFilter bloom(filterSize, hashFunctions);
    
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
        
        if (command == 1) {
            // Command "1 [URL]" means add the URL to the Bloom filter.
            URL newURL(url); 
            bloom.add(newURL);
        } else if (command == 2) {
            // Command "2 [URL]" means check if the URL is blacklisted.
            // Since we don't have the blacklist manager yet, we simply output the Bloom filter's result.
            URL queryURL(url);
            bool result = bloom.possiblyContains(queryURL);
            std::cout << (result ? "true" : "false") << std::endl;
        }
        // If the command does not match the expected format, the line is ignored.
    }
    
    return 0;
}