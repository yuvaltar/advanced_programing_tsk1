#include "BlackList.h"
#include <algorithm>

void BlackList::addUrl(const URL& url) {
    blacklist.push_back(url);
}

bool BlackList::contains(const URL& url) const {
    return std::find(blacklist.begin(), blacklist.end(), url) != blacklist.end();
}