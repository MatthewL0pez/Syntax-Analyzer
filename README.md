# Syntax Analyzer

This part of the project will use `lexer()` from Assignment 1 to get tokens first, then the parser will check whether the token stream follows the Rat26S grammar rules. THATS THE 29 LISTED ONES 

The syntax analyzer should:

- use the token list from the lexer
- check the program using the Rat26S grammar rules
- print the token type and lexeme character 
- print the production rules used
- show syntax errors if the string is invalid

---

# New files as of 3/10 to WORK ON...
In `include/`
- `Parser.h`

In `src/`
- `Parser.cpp`

# How work will be divided...

## Person 1 does: 
- setting up the main parser structure and handling top-level grammar rules.

- create main parser class setup
- make sure parser helper functions are good
- create the beginning/top level grammar rules
- handle declarations and parameter rules
- help make the parser flow start correctly from `<Rat26S>`

### Parser rules for Person 1
- `R1  <Rat26S>`
- `R2  <Opt Function Definitions>`
- `R3  <Function Definitions>`
- `R4  <Function>`
- `R5  <Opt Parameter List>`
- `R6  <Parameter List>`
- `R7  <Parameter>`
- `R8  <Qualifier>`
- `R9  <Body>`
- `R10 <Opt Declaration List>`
- `R11 <Declaration List>`
- `R12 <Declaration>`
- `R13 <IDs>`
- `R29 <Empty>`

### Files person 1 works on... 
- `include/Parser.h`
- `src/Parser.cpp`



## Person 2 does:
- responsible for statement parsing and control-flow rules

- create statement related grammar functions
- handle assignment, if, return, print, scan, while, and compound statements
- make sure statement lists parse correctly

### Parser rules for Person 2
- `R14 <Statement List>`
- `R15 <Statement>`
- `R16 <Compound>`
- `R17 <Assign>`
- `R18 <If>`
- `R19 <Return>`
- `R20 <Print>`
- `R21 <Scan>`
- `R22 <While>`

### Files person 2 works on...
- `src/Parser.cpp`



## Person 3 does:
- responsible for the condition and expression part of the grammar.

- create the relational operator parsing
- create the arithmetic expression parsing
- rewrite left recursive grammar rules into parser form
- help with syntax error handling and final parser connection in `main.cpp`

### Perser rules for Person 3
- `R23 <Condition>`
- `R24 <Relop>`
- `R25 <Expression>`
- `R26 <Term>`
- `R27 <Factor>`
- `R28 <Primary>`

### Files Person 3 works on...
- `src/Parser.cpp`
- `src/main.cpp`