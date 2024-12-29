#include "Aho-Corasick.hpp"
#include <string>
#include <queue>

void AhoCorasick::clear(State* state) {
    if (!state) return; 
    for (auto& [_, child] : state->children) {
        clear(child);
    }
    delete state;
}

void AhoCorasick::insert(const std::string& pattern, int index){
    State* current = root;
    for(char ch : pattern){
        if(!current->children[ch]){
            current->children[ch] = new State;
        }
        current = current->children[ch];
    }
    current->output_indexes.push_back(index);
}

void AhoCorasick::build(const std::vector<std::string>& words){
    patterns = words;

    // Building a simple NFA
    for(size_t i = 0; i < words.size(); i++){
        insert(words[i], i);
    }

    std::queue<State*> q;
    for(auto& [ch, state] : root->children){
        state->failureLink = root;
        q.push(state);
    }

    while(!q.empty()){
        State* current = q.front();
        q.pop();
        
        for(auto& [ch, child] : current->children){
            State* failure = current->failureLink;
            while(failure && !failure->children[ch]){
                failure = failure->failureLink;
            }
            child->failureLink = (failure) ? failure->children[ch] : root;

            if(child->failureLink){
                child->output_indexes.insert(
                    child->output_indexes.end(),
                    child->failureLink->output_indexes.begin(),
                    child->failureLink->output_indexes.end()
                );
            }
            
            q.push(child);
        }
    }
}

std::vector<std::tuple<int, int, int>> AhoCorasick::search(const std::string& text) {
    State* current = root;
    std::vector<std::tuple<int, int, int>> results;

    for (size_t i = 0; i < text.size(); i++) {
        char ch = text[i];

        while (current && !current->children[ch]) {
            current = current->failureLink;
        }
        current = (current) ? current->children[ch] : root;

        for (int pattern_index : current->output_indexes) {
            int start = i - patterns[pattern_index].size() + 1;
            int end = i;
            results.emplace_back(start, end, pattern_index);
        }
    }
    return results;
}
