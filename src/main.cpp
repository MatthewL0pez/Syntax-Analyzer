#include <iostream>
#include <fstream>
#include <string>

#include "Lexer.h"
#include "Tokens.h"

int main(int argc, char* argv[]) {

    //makes sure theres at least one input file
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file> [output_file]" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];

    // create the lexer using the input file name
    Lexer lexer(inputFileName);

    if (!lexer.isOpen()) {
        std::cerr << "Error: could not open input file: " << inputFileName << std::endl; //checks if file is acctually opened 
        return 1;
    }

    // if there's a second arguemnt it will print out the oupt to that file instead of terminal
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

    std::ostream& out = useOutFile ? static_cast<std::ostream&>(outFile) : std::cout;// this is for either a file or temrnal as output 


    out << "Token\t\tLexeme" << std::endl;
    out << "-----------------------------" << std::endl;

    // calls lexer until we hit end of file 
    while (true) {
        Token t = lexer.lexer(); //gets next token 

        if (t.tokenCategory == T_FileEnd) {   //stops when we reahc end of file 
            break;
        }

        out << tokenName(t.tokenCategory) << "\t\t" << t.lexeme << std::endl;
    }

    if (useOutFile) {
        outFile.close(); //closes output file 
    }

    return 0;
}