#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

// Local Include
#include "termcolor/termcolor.hpp"
#include "tabulate/table.hpp"
#include "tabulate/color.hpp"
#include "tabulate/font_style.hpp"
#include "indicators/progress_bar.hpp"
#include "indicators/termcolor.hpp"

void displayHelp() {
    std::cout << termcolor::cyan
              << "Usage: wct [options] [file]\n\n"
              << "Options:\n"
              << "  -c    Count bytes\n"
              << "  -l    Count lines\n"
              << "  -w    Count words\n"
              << "  -m    Count characters\n"
              << "  -h    Show this help message\n\n"
              << "If no options are provided, -c, -l, and -w are enabled by default.\n"
              << "You can provide a file or use standard input.\n"
              << termcolor::reset;
}

void displayProgressBar(const std::string& message) {
    indicators::ProgressBar bar{
        indicators::option::BarWidth{50},
        indicators::option::Start{"["},
        indicators::option::End{"]"},
        indicators::option::Fill{"="},
        indicators::option::Lead{">"},
        indicators::option::Remainder{" "},
        indicators::option::ShowPercentage{true},
        indicators::option::ForegroundColor{indicators::Color::green},
        indicators::option::ShowElapsedTime{false}
    };

    for (int i = 0; i <= 100; ++i) {
        bar.set_progress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
    }

    std::cout << std::endl;
}

void countFile(std::istream &input, const std::string &fileName, bool countBytes, bool countLines, bool countWords, bool countChars) {
    displayProgressBar(fileName);

    size_t bytes = 0, lines = 0, words = 0, chars = 0;
    std::string line;

    while (std::getline(input, line)) {
        lines++;
        bytes += line.size() + 1;
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            words++;
            chars += word.size();
        }
    }

    using namespace tabulate;
    Table table;
    table.add_row({"Metric", "Count"});

    if (countLines) table.add_row({"Lines", std::to_string(lines)});
    if (countWords) table.add_row({"Words", std::to_string(words)});
    if (countBytes) table.add_row({"Bytes", std::to_string(bytes)});
    if (countChars) table.add_row({"Characters", std::to_string(chars)});

    table[0].format()
        .font_color(Color::yellow)
        .font_style({FontStyle::bold});

    std::cout << termcolor::green << "File: " << fileName << termcolor::reset << std::endl;
    std::cout << table << std::endl;
}

int main(int argc, char *argv[]) {
    bool countBytes = false, countLines = false, countWords = false, countChars = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            displayHelp();
            return 0;
        }
    }

    // Parsing arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-c") countBytes = true;
        else if (arg == "-l") countLines = true;
        else if (arg == "-w") countWords = true;
        else if (arg == "-m") countChars = true;
    }

    if (!countBytes && !countLines && !countWords && !countChars) {
        countBytes = countLines = countWords = true;
    }

    if (argc > 1 && argv[argc - 1][0] != '-') {
        std::ifstream file(argv[argc - 1]);
        if (!file) {
            std::cerr << termcolor::red << "Error: Unable to open file " << argv[argc - 1] << termcolor::reset << std::endl;
            return 1;
        }
        countFile(file, argv[argc - 1], countBytes, countLines, countWords, countChars);
    } else {
        std::cout << termcolor::green << "Reading from standard input. Press Ctrl+D to finish." << termcolor::reset << std::endl;
        countFile(std::cin, "Standard Input", countBytes, countLines, countWords, countChars);
    }

    return 0;
}
