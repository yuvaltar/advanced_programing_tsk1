// bloomfilter.cpp file
#include "BloomFilter.h"

// constructor 

BloomFilter::BloomFilter(size_t size, const std::vector<std::shared_ptr<IHashFunction>>& hashFunctions)
    : m_size(size), bitArray(size, false), hashFunctions(hashFunctions) {} 

void BloomFilter::add(const std::string& item) { 
    for (const auto& hf : hashFunctions) {
        size_t hashValue = hf->hash(item);
        size_t index = hashValue % m_size;
        bitArray[index] = true;
    }
}

bool BloomFilter::possiblyContains(const std::string& item) const {
    for (const auto& hf : hashFunctions) {
        size_t hashValue = hf->hash(item);
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