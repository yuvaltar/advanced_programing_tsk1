#include <string>
#include <functional>
#include <vector>
#include <iostream>
//creating the URL class
class URL{
// class members
private: 
    std::string url;

public:
    URL(const std:: string& url); //URL Constructor

    std::string getURL() const; //getURL function

    std::vector<size_t> hash(const std::vector<std::hash<std::string>>& hash_functions) const; //hash function

    bool operator==(const URL& compURL) const; //Creating == operator to check if 2 URL are the same

}; 


URL::URL(const std::string& url) : url(url) {}

std::string URL::getURL() const {
    return url;
}

//Compute hashes for the URL using multiple hash functions
std::vector<size_t> URL::hash(const std::vector<std::hash<std::string>>& hash_functions) const {
    std::vector<size_t> hash_values;
    for (const auto& hash_function : hash_functions) {
        hash_values.push_back(hash_function(url));
    }
    return hash_values;
}

bool URL::operator==(const URL& other) const {
    return url == other.url;
}