#pragma once

#include <unordered_map>
#include <vector>
#include <string>

/*
    State of the Aho-Corasick automaton
*/

struct State{
    std::unordered_map<char, State*> children;
    State* failureLink = nullptr;
    std::vector<int> output;
};

/*
    Aho-Corasick automaton
*/

class AhoCorasick{
    private:
        State* root;
        std::vector<std::string> patterns;
        void clear(State* state);
    public:
        AhoCorasick() : root(new State()) {}
        ~AhoCorasick() { clear(root); };
        void insert(const std::string& pattern, int index);
};