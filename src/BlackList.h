#ifndef BLACKLIST_H
#define BLACKLIST_H

#include <list>
#include "URL.h" // Assuming you have a URL class with operator== defined

class BlackList {
private:
    std::list<URL> blacklist;

public:
    void addUrl(const URL& url);
    bool contains(const URL& url) const;
};

#endif // BLACKLIST_H