#pragma once

#include <unordered_map>
#include <vector>
#include <string>

/*
    State of the Aho-Corasick automaton
*/

struct State{
    std::unordered_map<char, State*> children; // implies transitions to other states
    State* failureLink = nullptr;
    std::vector<int> output_indexes; // final states of NFA
};

/*
    Aho-Corasick automaton
*/

class AhoCorasick{
    private:
        State* root;
        // std::vector<std::string> patterns;
        void clear(State* state);
    public:
        std::vector<std::string> patterns;
        AhoCorasick() : root(new State()) {}
        ~AhoCorasick() { clear(root); };
        void insert(const std::string& pattern, int index);
        void build(const std::vector<std::string>& patterns);
        std::vector<std::tuple<int, int, int>> search(const std::string& text);
};