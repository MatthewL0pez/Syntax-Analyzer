#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Tokens.h"
#include <fstream>
#include <string>

class Parser {
public:
    Parser(Lexer& lexer, std::ofstream& outFile, bool printRules = true);

    // ===== PERSON 1 / TOP-LEVEL RULES =====
    void Rat26S();
    void OptFunctionDefinitions();
    void FunctionDefinitions();
    void Function();
    void OptParameterList();
    void ParameterList();
    void Parameter();
    void Qualifier();
    void Body();
    void OptDeclarationList();
    void DeclarationList();
    void Declaration();
    void IDs();
    void Empty();

    // ===== PERSON 2 / STATEMENTS =====
    void StatementList();
    void Statement();
    void Bracket();
    void Assign();
    void If();
    void Return();
    void Print();
    void Scan();
    void While();

    // ===== PERSON 3 / EXPRESSIONS =====
    void Condition();
    void Relop();
    void Expression();
    void ExpressionPrime();
    void Term();
    void TermPrime();
    void Factor();
    void Primary();

private:
    Lexer& lexer_;              // connects parser to lexer
    Token currentToken_;        // current token being analyzed
    std::ofstream& out_;        // output file stream
    bool printRules_;           // controls grammar rule printing

    // ===== HELPER FUNCTIONS =====
    void advance();  
    void match(int expectedCategory, const std::string& expectedLexeme = "");
    void printToken();
    void printProduction(const std::string& rule);
    void error(const std::string& message);

    // ===== HELPER CHECKS =====
    bool isQualifier() const;
    bool isStatementStart() const;
    bool isRelopToken() const;
    bool isExpressionStart() const;
};

#endif