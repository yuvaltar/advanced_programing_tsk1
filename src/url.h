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



bool URL::operator==(const URL& other) const {
    return url == other.url;
}