
#include "Parser.h"
#include <cstdlib>
#include <iostream>

Parser::Parser(Lexer& lexer, std::ofstream& outFile, bool printRules)
    : lexer_(lexer), out_(outFile), printRules_(printRules) {
    advance();
}

void Parser::advance() {
    currentToken_ = lexer_.lexer();
    printToken();
}

void Parser::printToken() {
    out_ << "Token: " << tokenName(currentToken_.tokenCategory)
         << " Lexeme: " << currentToken_.lexeme << '\n';
}

void Parser::printProduction(const std::string& rule) {
    if (printRules_) {
        out_ << rule << '\n';
    }
}

void Parser::match(int expectedCategory, const std::string& expectedLexeme) {
    if (currentToken_.tokenCategory != expectedCategory) {
        error("unexpected token category");
    }

    if (!expectedLexeme.empty() && currentToken_.lexeme != expectedLexeme) {
        error("expected lexeme '" + expectedLexeme + "'");
    }

    advance();
}

void Parser::error(const std::string& message) {
    out_ << "Syntax Error at line " << currentToken_.numberLine
         << ": " << message
         << " | Found token: " << tokenName(currentToken_.tokenCategory)
         << " | Lexeme: " << currentToken_.lexeme << '\n';

    std::cerr << "Syntax Error at line " << currentToken_.numberLine
              << ": " << message
              << " | Found token: " << tokenName(currentToken_.tokenCategory)
              << " | Lexeme: " << currentToken_.lexeme << std::endl;

    std::exit(1);
}

bool Parser::isQualifier() const {
    return currentToken_.tokenCategory == T_Keyword &&
           (currentToken_.lexeme == "integer" ||
            currentToken_.lexeme == "boolean" ||
            currentToken_.lexeme == "real");
}

// R1
void Parser::Rat26S() {
    printProduction("<Rat26S> -> <Opt Function Definitions> @ <Opt Declaration List> <Statement List> @");

    OptFunctionDefinitions();
    match(T_Seperator, "@");
    OptDeclarationList();


}

// R2
void Parser::OptFunctionDefinitions() {
    printProduction("<Opt Function Definitions> -> <Function Definitions> | <Empty>");

    if (currentToken_.tokenCategory == T_Keyword &&
        currentToken_.lexeme == "function") {
        FunctionDefinitions();
    } else {
        Empty();
    }
}

// R3
void Parser::FunctionDefinitions() {
    printProduction("<Function Definitions> -> <Function> <Function Definitions> | <Function>");

    Function();

    if (currentToken_.tokenCategory == T_Keyword &&
        currentToken_.lexeme == "function") {
        FunctionDefinitions();
    }
}

// R4
void Parser::Function() {
    printProduction("<Function> -> function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>");

    match(T_Keyword, "function");
    match(T_Identifier);
    match(T_Seperator, "(");
    OptParameterList();
    match(T_Seperator, ")");
    OptDeclarationList();
    Body();
}

// R5
void Parser::OptParameterList() {
    printProduction("<Opt Parameter List> -> <Parameter List> | <Empty>");

    if (currentToken_.tokenCategory == T_Identifier) {
        ParameterList();
    } else {
        Empty();
    }
}

// R6
void Parser::ParameterList() {
    printProduction("<Parameter List> -> <Parameter> , <Parameter List> | <Parameter>");

    Parameter();

    if (currentToken_.tokenCategory == T_Seperator &&
        currentToken_.lexeme == ",") {
        match(T_Seperator, ",");
        ParameterList();
    }
}

// R7
void Parser::Parameter() {
    printProduction("<Parameter> -> <IDs> <Qualifier>");
    IDs();
    Qualifier();
}

// R8
void Parser::Qualifier() {
    printProduction("<Qualifier> -> integer | boolean | real");

    if (currentToken_.tokenCategory == T_Keyword &&
        currentToken_.lexeme == "integer") {
        match(T_Keyword, "integer");
    } else if (currentToken_.tokenCategory == T_Keyword &&
               currentToken_.lexeme == "boolean") {
        match(T_Keyword, "boolean");
    } else if (currentToken_.tokenCategory == T_Keyword &&
               currentToken_.lexeme == "real") {
        match(T_Keyword, "real");
    } else {
        error("expected qualifier (integer, boolean, or real)");
    }
}

// R9
void Parser::Body() {
    printProduction("<Body> -> { <Opt Declaration List> <Statement List> }");

    match(T_Seperator, "{");
    OptDeclarationList();


    match(T_Seperator, "}");
}

// R10
void Parser::OptDeclarationList() {
    printProduction("<Opt Declaration List> -> <Declaration List> | <Empty>");

    if (isQualifier()) {
        DeclarationList();
    } else {
        Empty();
    }
}

// R11
void Parser::DeclarationList() {
    printProduction("<Declaration List> -> <Declaration> ; <Declaration List> | <Declaration> ;");

    Declaration();
    match(T_Seperator, ";");

    if (isQualifier()) {
        DeclarationList();
    }
}

// R12
void Parser::Declaration() {
    printProduction("<Declaration> -> <Qualifier> <IDs>");
    Qualifier();
    IDs();
}

// R13
void Parser::IDs() {
    printProduction("<IDs> -> <Identifier> , <IDs> | <Identifier>");

    match(T_Identifier);

    if (currentToken_.tokenCategory == T_Seperator &&
        currentToken_.lexeme == ",") {
        match(T_Seperator, ",");
        IDs();
    }
}

// R29
void Parser::Empty() {
    printProduction("<Empty> -> ε");
}