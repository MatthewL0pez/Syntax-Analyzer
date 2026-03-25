#include <iostream>
#include <fstream>
#include <string>

#include "Lexer.h"
#include "Parser.h"
#include "Tokens.h"

int main(int argc, char* argv[]) {

    // make sure there is at least one input file
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file> [output_file]" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];

    // create lexer using input file
    Lexer lexer(inputFileName);

    if (!lexer.isOpen()) {
        std::cerr << "Error: could not open input file: " << inputFileName << std::endl;
        return 1;
    }

    // if second argument exists, use it as output file
    std::ofstream outFile;
    bool useOutFile = false;

    if (argc >= 3) {
        std::string outputFileName = argv[2];
        outFile.open(outputFileName);

        if (!outFile.is_open()) {
            std::cerr << "Error: could not open output file: " << outputFileName << std::endl;
            return 1;
        }

        useOutFile = true;
    }

    // if no output file provided, default output file
    if (!useOutFile) {
        outFile.open("syntax_output.txt");

        if (!outFile.is_open()) {
            std::cerr << "Error: could not create default output file." << std::endl;
            return 1;
        }
    }

    // create parser and start parsing
    Parser parser(lexer, outFile, true);

    parser.Rat26S();

    outFile << "\nParsing completed successfully.\n";
    std::cout << "Parsing completed successfully." << std::endl;

    outFile.close();
    return 0;
}