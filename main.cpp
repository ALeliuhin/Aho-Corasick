#include <iostream>
#include <fstream>
#include "Aho-Corasick.hpp"

std::string read_file(const std::string& filepath) {
    std::ifstream text_file(filepath);
    if (text_file.is_open()) {
        std::string text;
        std::string line;
        while (getline(text_file, line)) {
            text += line + "\n";
        }
        text_file.close();
        return text;
    }
    throw std::runtime_error("Unable to open file: " + filepath);
}

void main_menu(const std::string& text) {
    bool running = true;
    while (running) {
        std::cout << "┌─────────────────────────────────┐" << std::endl;
        std::cout << "│          Aho-Corasick           │" << std::endl;
        std::cout << "├───┬─────────────────────────────┤" << std::endl;
        std::cout << "│ 1.│ Search for patterns         │" << std::endl;
        std::cout << "├───┼─────────────────────────────┤" << std::endl;
        std::cout << "│ 2.│ Exit                        │" << std::endl;
        std::cout << "└───┴─────────────────────────────┘" << std::endl;

        int option;
        std::cout << "Enter your choice: ";
        if (!(std::cin >> option)) { 
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();      
            std::cin.ignore(1000, '\n'); 
            continue;       
        }

        int n;
        std::vector<std::string> patterns;
        AhoCorasick ac;
        std::vector<std::tuple<int, int, int>> results;

        switch (option) {
            case 1:
                std::cout << "Enter the number of patterns: ";
                if (!(std::cin >> n)) {
                    std::cout << "Invalid input. Please enter a number.\n";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    continue;
                }

                patterns.resize(n);
                std::cout << "Enter the patterns: " << std::endl;

                for (int i = 0; i < n; i++) {
                    std::cin >> patterns[i];
                }
                ac.build(patterns);

                results = ac.search(text);

                std::cout << "Results:\n";
                for (const auto& result : results) {
                    int start, end, pattern_index;
                    std::tie(start, end, pattern_index) = result;
                    std::cout << "Pattern \"" << patterns[pattern_index]
                              << "\" occurs at positions [" << start << ", " << end << "]\n";
                }
                break;

            case 2:
                running = false;
                break;

            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}


int main(int argc, char const* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return -1;
    }
    std::string filepath = argv[1];
    std::string text;

    try {
        text = read_file(filepath);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    main_menu(text);
    return 0;
}
