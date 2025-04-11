#ifndef DOUBLE_HASH_FUNCTION_H
#define DOUBLE_HASH_FUNCTION_H

#include "IHashFunction.h" // Make sure this matches your actual interface file name
#include <string>
#include <functional>

class DoubleHashFunction : public IHashFunction {
public:
    size_t hash(const std::string& s) const override {
        size_t h1 = std::hash<std::string>{}(s);
        size_t h2 = std::hash<std::string>{}(std::to_string(h1));
        return h1 ^ (h2 << 1); // Combine the two hashes
    }
};

#endif // DOUBLE_HASH_FUNCTION_H
