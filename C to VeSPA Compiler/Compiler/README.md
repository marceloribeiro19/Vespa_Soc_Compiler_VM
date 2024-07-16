# RocketC - Final Compiler

This project is organized as follows:
- Lexer: Contains all files related to the lexical analyzer.
- Parser: Contains all files related to the syntactic analyzer. 
- Util: General purpose utility files, as well as some typedefs and constants.
- Semantic analyzer: Contains all files related to the symbol tables and typechecking
- Optimization: Contains all files related to the Constant Folding optimization applied directly to the AST
- Code Generation: Contains all files related to the Code Generation
- Output: Contains the output of the compiler

## Makefile
The Makefile included with this project allows to generate only specific
components (i.e. only the lexer, or only the parser), or to fully generate the project.
For building the complete project, just run "make all" under the project root.

## Testing
- For testing the lexer, after running make, just go to the "Output" folder and
run ./RocketC <SrcFile.c> --parse

- Another way to test is changing the TestCodeGen.c file and execute the commands:
"make all"
"make run"

## Output
- A "Rocket.asm" file is generated in the Output folder
- Along with the C code provided it always generates the assembly functions that perform Division/Multiplication/Remain operations at the top of the file in case multiplications are used. Those functions implement * / and % using RL and RR instructions.
- These functions are very large
- At the console output it can also be checked the generated AST, the symbol tables created and the semantic errors. 


