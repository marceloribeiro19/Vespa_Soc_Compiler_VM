#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "Types.h"

#define FLAG_REGISTER 1

typedef enum
{
    OP_PLUS,                    // 0
    OP_MINUS,                   // 1
    OP_RIGHT_SHIFT,             // 2
    OP_LEFT_SHIFT,              // 3
    OP_MULTIPLY,                // 4
    OP_DIVIDE,                  // 5
    OP_REMAIN,                  // 6
    OP_GREATER_THAN,            // 7
    OP_LESS_THAN_OR_EQUAL,      // 8
    OP_GREATER_THAN_OR_EQUAL,   // 9
    OP_LESS_THAN,               // 10
    OP_EQUAL,                   // 11
    OP_NOT_EQUAL,               // 12
    OP_LOGICAL_AND,             // 13
    OP_LOGICAL_OR,              // 14
    OP_LOGICAL_NOT,             // 15
    OP_BITWISE_AND,             // 16
    OP_BITWISE_NOT,             // 17
    OP_BITWISE_OR,              // 18
    OP_BITWISE_XOR,             // 19
    OP_ASSIGN,                  // 20
    OP_PLUS_ASSIGN,             // 21
    OP_MINUS_ASSIGN,            // 22
    OP_MODULUS_ASSIGN,          // 23
    OP_LEFT_SHIFT_ASSIGN,       // 24
    OP_RIGHT_SHIFT_ASSIGN,      // 25
    OP_BITWISE_AND_ASSIGN,      // 26
    OP_BITWISE_OR_ASSIGN,       // 27
    OP_BITWISE_XOR_ASSIGN,      // 28
    OP_MULTIPLY_ASSIGN,         // 29
    OP_DIVIDE_ASSIGN,           // 30
    OP_SIZEOF,                  // 31
    OP_NEGATIVE,
    OP_NOT_DEFINED
}OperatorType_et;

typedef enum
{
    TYPE_CHAR = 0,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE, 
    TYPE_STRING,
    TYPE_VOID
}VarType_et;

typedef enum
{
    SIGN_SIGNED,
    SIGN_UNSIGNED
}SignQualifier_et;

typedef enum
{
    MOD_NONE,
    MOD_CONST,
    MOD_VOLATILE
}ModQualifier_et;

typedef enum
{
    VIS_NONE,
    VIS_STATIC,
    VIS_EXTERN
}VisQualifier_et;


typedef enum
{
    NODE_SIGN = 0,
    NODE_MISC,
    NODE_VISIBILITY,  
    NODE_MODIFIER, 
    NODE_TYPE,                        

    NODE_OPERATOR,         
    NODE_TERNARY,                         
    NODE_IDENTIFIER,        
    NODE_STRING,          
    NODE_INTEGER,           
    NODE_FLOAT,
    NODE_CHAR,
    NODE_STRUCT,

    NODE_IF,               
    NODE_WHILE,            
    NODE_DO_WHILE,                           
    NODE_RETURN,             
    NODE_CONTINUE,           
    NODE_BREAK,

    NODE_GOTO,
    NODE_LABEL,

    NODE_SWITCH,            
    NODE_CASE,               
    NODE_DEFAULT, 

    NODE_REFERENCE,           
    NODE_POINTER,              
    NODE_POINTER_CONTENT,
    NODE_TYPE_CAST,           

    NODE_POST_DEC,           
    NODE_PRE_DEC,            
    NODE_POST_INC,           
    NODE_PRE_INC,  

    NODE_VAR_DECLARATION,
    NODE_ARRAY_DECLARATION,
    NODE_ARRAY_INDEX,

    NODE_FUNCTION,
    NODE_FUNCTION_CALL,
    NODE_PARAMETER,

    NODE_NULL,
    NODE_END_SCOPE,
    NODE_START_SCOPE,

    NODE_TYPE_NOT_DEFINED
}NodeType_et;

typedef union
{
    double fVal;
    long int dVal;
    char* sVal;
}NodeData_ut;

#endif