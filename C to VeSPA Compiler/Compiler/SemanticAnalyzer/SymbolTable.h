#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Util/Globals.h"
#include "../Util/TreeNode.h"

#define HASH_TABLE_SIZE     97
#define SYMBOL_NOT_FOUND    0
#define SYMBOL_FOUND        1
#define SYMBOL_ADDED        1
#define SYMBOL_ERROR        0

#define NO_MEMORY           -1      //used for function arguments


//Symbols types enum
typedef enum{
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_LABEL,
    SYMBOL_POINTER,
    SYMBOL_ARRAY
}SymbolType_et;

typedef enum{
    GLOBAL_SCOPE,
    ARGUMENT_SCOPE,
    FUNCTION_SCOPE
}VarScope_et;

//Function parameters struct
typedef struct parameter{
    char* name;
    VarType_et varType;
    SignQualifier_et varSign;
    ModQualifier_et varMod;
    bool isPointer;
}parameter_st;


// Symbol entry struct
typedef struct SymbolEntry
{
    SymbolType_et symbolType;       // Symbol type
    struct SymbolEntry* next;       // Next Entry Pointer (linked list to prevent collisions)
    char* name;                     // Symbol name

    VarType_et type;                // Variable Type
    SignQualifier_et signal;        // Variable signal
    ModQualifier_et modifier;       // Variable modifier
    VisQualifier_et visibility;     // Variable visibility   
    VarScope_et scopeLocation;      // Scope of the variable
    uint8_t paramPosition;          // position of the function parameter

    union
    {
        //pointers and variables
        uint32_t memoryLocation;                 // memory offset
        

        //functions
        struct
        {
            uint8_t parameterNumber;        // Number of Function Params
            parameter_st* parameters;       // List of parameters
            bool isImplemented;             // Flag to signal whether it's just the signature or the implementation
        }SymbolFunction_s;

        //arrays
        struct
        {
            uint32_t memoryLocation;             // Array Location
            uint32_t arraySize;             // Array size
        }SymbolArray_s;
    }symbolContent_u;
} SymbolEntry_st;


// Symbol table struct
typedef struct SymbolTable
{
    struct SymbolEntry* table[HASH_TABLE_SIZE]; // Symbol Table
    struct SymbolTable* enclosingScope;         // Pointer to Symbol Table of Enclosing Scope
    uint8_t parameterNumber;
} SymbolTable_st;


static int hash(const char* key);

int createSymbolTable(SymbolTable_st** ppsymTable, SymbolTable_st* enclosingScope);

int insertSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymEntry, char *symName, SymbolType_et symType);

int fetchSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymbol, char* name, int onlyCurrentScope);

void freeSymbolTable();

void printSymbolTables();

int addFunctionParams(SymbolEntry_st* pSymbol, struct parameter* pNewParam);
#endif 
