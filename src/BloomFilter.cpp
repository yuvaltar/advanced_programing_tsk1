// bloomfilter.cpp file
#include "BloomFilter.h"

// class members
private:
    size_t m_size;
    std::vector<bool> bitArray;  
    std::vector<std::shared_ptr<IHashFunction>> hashFunctions;

    //size_t x = std::hash<std::string>{}("ihvb");

// constructor 
BloomFilter::BloomFilter(size_t size, const std::vector<std::shared_ptr<IHashFunction>>& hashFunctions)
    : m_size(size), bitArray(size, false), hashFunctions(hashFunctions) {} 

// too add the
void BloomFilter::add(const std::string& item) { // 1 to add the url bit to the black list
    for (const auto& hf : hashFunctions) { // getting an hash func and goes over them in for loop
        size_t hashValue = hf->hash(item); // the value returnd by the hash
        size_t index = hashValue % m_size; // modulo operation
        bitArray[index] = true;            // mark the singhed bit as true
    }
}
// to check if the url is in the black list
bool BloomFilter::possiblyContains(const std::string& item) const { // 2 
    for (const auto& hf : hashFunctions) { // getting an hash func and goes over them in for loop
        size_t hashValue = hf->hash(item); //
        size_t index = hashValue % m_size;
        if (!bitArray[index])
            return false;
    }
    return true;
}

const std::vector<bool>& BloomFilter::getBitArray() const {
    return bitArray;
}

void BloomFilter::setBitArray(const std::vector<bool>& bits) {
    if(bits.size() == m_size) {
        bitArray = bits;
    }
}

