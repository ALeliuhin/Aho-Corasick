#include <iostream>
#include "Aho-Corasick.hpp"

int main() {
    AhoCorasick ac;
    ac.build({"he", "she", "his", "hers", "good"});
    auto results = ac.search("ahishers");

    for (const auto& result : results) {
        int start, end, pattern_index;
        std::tie(start, end, pattern_index) = result; // unpacking tuple into separate variables

        std::cout << "Pattern index: " << pattern_index
                  << ", starts at: " << start
                  << ", ends at: " << end << std::endl;
    }

    return 0;
}
