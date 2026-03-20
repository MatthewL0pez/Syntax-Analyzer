#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Token.h"
#include <fstream> 
#include <string> 

class Parser {
    public:
    Parser(Lexer& lexer, std::ofstream& outFile, bool printRules = true);
    void Rat26S();
    void OptFunctionDefinitions();
    void FunctionDefintions();
    void Function();
    void ParameterList();
    void Parameter();
    void Qualifer();
    void Body();
    void OptDeclarationList();
    void DeclarationList();
    void Declaration();
    void IDs();
    void Empty();

    
    
    
         
    
    
    
    
    
    private: 
    Lexer& lexer_; //connects lexer 
    Token currentToken_; //stores current token being analyzed 
    std::ofstream& out_; // this gives the output file 
    bool printRules_; //allows for the printing of the grammar rules to be printed or not 
    void advance(); //moves to next token 
    void match(int expectedCategory, const std::string& expectedLexeme = ""); //checks if token matches 
    void printToken(); //prints token + lexeme 
    void printProduction(const std::string& rule); //prints grammar rule 
    void error(const std::string& message); //hanndles sytax errors
    bool isQualifier() const; //checks if token is int bool or real 







};
#endif 