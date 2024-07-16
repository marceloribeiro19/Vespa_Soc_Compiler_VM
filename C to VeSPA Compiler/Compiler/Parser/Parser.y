//--------------------------------------------------------------------------------------------------------------------//
// TODO List:
//  -Missing AST for variables of pointer type
//--------------------------------------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------------------------------------//
// Prologue
//--------------------------------------------------------------------------------------------------------------------//

%code requires {
#include "../Util/Globals.h"
}

%{
#include <stdint.h>
#include <errno.h>
#include "../main.h"
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Lexer/Lexer.h"
#include "../Util/Logger.h"

int yylex();
int yyerror(char* pStr);
const char* getTokenName(int tokenValue);
TreeNode_st* pTreeRoot;
static char* currentFunction;


%}

//--------------------------------------------------------------------------------------------------------------------//
// Token Types
//--------------------------------------------------------------------------------------------------------------------//
%token TOKEN_IF
%token TOKEN_EOF
%token TOKEN_ERROR   
%token TOKEN_ELSE
%token TOKEN_DO
%token TOKEN_WHILE
%token TOKEN_FOR
%token TOKEN_SWITCH
%token TOKEN_CASE
%token TOKEN_DEFAULT
%token TOKEN_RETURN
%token TOKEN_BREAK
%token TOKEN_INT
%token TOKEN_FLOAT
%token TOKEN_DOUBLE
%token TOKEN_CHAR
%token TOKEN_VOID
%token TOKEN_STRUCT                 // delayed
%token TOKEN_TYPEDEF                // delayed
%token TOKEN_CONTINUE
%token TOKEN_EXTERN
%token TOKEN_GOTO
%token TOKEN_LONG
%token TOKEN_ENUM                   // delayed           
%token TOKEN_SHORT
%token TOKEN_SIZEOF
%token TOKEN_STATIC
%token TOKEN_SIGNED
%token TOKEN_UNION                  // delayed
%token TOKEN_UNSIGNED
%token TOKEN_VOLATILE
%token TOKEN_ASSIGN
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_OVER
%token TOKEN_PERCENT
%token TOKEN_LEFT_PARENTHESES
%token TOKEN_RIGHT_PARENTHESES
%token TOKEN_LEFT_BRACE
%token TOKEN_RIGHT_BRACE
%token TOKEN_LEFT_BRACKET
%token TOKEN_RIGHT_BRACKET
%token TOKEN_TERNARY
%token TOKEN_SEMI
%token TOKEN_COLON
%token TOKEN_COMMA
%token TOKEN_INCREMENT
%token TOKEN_DECREMENT
%token TOKEN_BITWISE_AND     
%token TOKEN_BITWISE_OR
%token TOKEN_LOGICAL_AND
%token TOKEN_BITWISE_NOT
%token TOKEN_BITWISE_XOR
%token TOKEN_LOGICAL_NOT
%token TOKEN_LOGICAL_OR
%token TOKEN_EQUAL
%token TOKEN_NOT_EQUAL
%token TOKEN_LESS_THAN
%token TOKEN_GREATER_THAN
%token TOKEN_LESS_THAN_OR_EQUAL
%token TOKEN_GREATER_THAN_OR_EQUAL
%token TOKEN_RIGHT_SHIFT
%token TOKEN_LEFT_SHIFT
%token TOKEN_PLUS_ASSIGN
%token TOKEN_MINUS_ASSIGN
%token TOKEN_LEFT_SHIFT_ASSIGN
%token TOKEN_RIGHT_SHIFT_ASSIGN
%token TOKEN_BITWISE_AND_ASSIGN
%token TOKEN_BITWISE_OR_ASSIGN
%token TOKEN_BITWISE_XOR_ASSIGN
%token TOKEN_MULTIPLY_ASSIGN
%token TOKEN_DIVIDE_ASSIGN
%token TOKEN_MODULUS_ASSIGN
%token TOKEN_ARROW                  // delayed
%token TOKEN_CONSTANT
%token TOKEN_ASTERISK
%token TOKEN_ADDRESS_OF          
%token TOKEN_DOT                    // delayed  
%token TOKEN_FNUM
%token TOKEN_NUM
%token TOKEN_STR
%token TOKEN_ID
%token TOKEN_CNUM

// %define api.value.type is prefered over #define YYSTYPE
%define api.value.type {ParserObject_ut}

%left TOKEN_MINUS TOKEN_PLUS

//--------------------------------------------------------------------------------------------------------------------//
// Grammar Rules
//--------------------------------------------------------------------------------------------------------------------//
%%

// Rules for the overall program
R_PROGRAM               :   R_PROGRAM TOKEN_EOF 
                            {
                                pTreeRoot = $1.treeNode;
                                LOG_DEBUG("Reached end of file!\n");
                                return 0;
                            }
                        |   R_PROGRAM R_GLOBAL_STATEMENT 
                            {
                                TreeNode_st* pNode = $1.treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = $2.treeNode;
                                    $$.treeNode = $1.treeNode; 
                                }
                                else
                                {
                                    $$.treeNode = $2.treeNode;
                                }
                                pTreeRoot = $$.treeNode;
                            }
                        |   R_GLOBAL_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Global statements
R_GLOBAL_STATEMENT      :   R_VAR_DECLARATION 
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_FUNC_PROTOTYPE 
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_FUNC_IMPLEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;


// Local statement list
R_LOCAL_STATEMENT_LIST  :   %empty
                            {
                                $$.treeNode = NULL;
                            }
                            
                        |   R_LOCAL_STATEMENT_LIST R_LOCAL_STATEMENT
                            {
                                TreeNode_st* pNode = $1.treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = $2.treeNode;
                                    $$.treeNode = $1.treeNode; 
                                }
                                else
                                {
                                    $$.treeNode = $2.treeNode;
                                }
                            }

                        |   R_LOCAL_STATEMENT
                            { 
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Local statements
R_LOCAL_STATEMENT       :   R_IF_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_GOTO
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_SWITCH
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_BREAK
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_CONTINUE
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_DO_WHILE_LOOP
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_LABEL
                            {
                                $$.treeNode = $1.treeNode;
                            }    
                            
                        |   R_WHILE_LOOP
                            {
                                $$.treeNode = $1.treeNode;
                            }
                            
                        |   R_FOR_LOOP
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_COMPOUND_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_RETURN
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_VAR_DECLARATION
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_VAR_ASSIGNMENT
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_FUNC_CALL TOKEN_SEMI
                            {
                                $$.treeNode = $1.treeNode;
                            }   

                        |   R_INC_DEC TOKEN_SEMI
                            {
                                $$.treeNode = $1.treeNode;
                            }                       
                        ;


// Statements with braces                                                                 // Examples:
R_COMPOUND_STATEMENT    :   TOKEN_LEFT_BRACE R_LOCAL_STATEMENT_LIST TOKEN_RIGHT_BRACE     // { ... }
                            {
                                TreeNode_st* pNode = $2.treeNode;
                                TreeNode_st* pEnd;
                                TreeNode_st* pStart;
                                TreeNode_st* pNull;

                                if (pNode != NULL)
                                { 
                                    NodeCreate(&pEnd, NODE_END_SCOPE);
                                    NodeCreate(&pStart, NODE_START_SCOPE);

                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = pEnd;
                                    $$.treeNode = pStart;
                                    pStart->pSibling = $2.treeNode; 
                                }
                                else
                                {
                                    NodeCreate(&pNull, NODE_NULL);
                                    $$.treeNode = pNull;
                                }
                            }

                        |   TOKEN_LEFT_BRACE TOKEN_RIGHT_BRACE                            // {}
                            {
                                $$.treeNode = NULL;
                            }
                        ;


//--------------------------------------------------------------------------------------------------------------------//
// Flow Control
//--------------------------------------------------------------------------------------------------------------------//

// Flow control statements                      // Examples:
R_CONTINUE  :   TOKEN_CONTINUE TOKEN_SEMI       // continue;
                {
                    NodeCreate(&($$.treeNode), NODE_CONTINUE);
                }
            ;

R_BREAK     :   TOKEN_BREAK TOKEN_SEMI          // break;
                {
                    NodeCreate(&($$.treeNode), NODE_BREAK);
                }
            ;

R_GOTO      :   TOKEN_GOTO TOKEN_ID TOKEN_SEMI   // goto label;
                {
                    NodeCreate(&($$.treeNode), NODE_GOTO);
                    $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                }
            ;


// Rule to any SWITCH CASE implementation                               // Example: switch(var) { ... }                                                              
R_SWITCH    :   TOKEN_SWITCH TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_LEFT_BRACE R_SWITCH_BODY TOKEN_RIGHT_BRACE    
                {
                    NodeCreate(&($$.treeNode), NODE_SWITCH);
                    NodeAddChild($$.treeNode, $3.treeNode);
                    NodeAddChild($$.treeNode, $6.treeNode);
                }
            ;

// A SWITCH body can be composed by: a list of cases, a default only, or a list of cases and a default 
R_SWITCH_BODY   :   R_CASE_LIST R_DEFAULT                    // case 0:  ... default: ...
                    {
                        TreeNode_st* pNode = $1.treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = $2.treeNode;
                            $$.treeNode = $1.treeNode; 
                        }
                        else
                        {
                            $$.treeNode = $2.treeNode;
                        }
                    }

                |   R_CASE_LIST                             //Examples:     // case 0:  ... case 1: ...
                    {
                        $$.treeNode = $1.treeNode;
                    }

                |   R_DEFAULT                                // default: ...
                    {
                        $$.treeNode = $1.treeNode;
                    }    
                ;


// One or multiple CASEs                   // Examples:
R_CASE_LIST     :   R_CASE_LIST R_CASE     // case 0: ... case 1: ... case 2: ...
                    {
                        TreeNode_st* pNode = $1.treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = $2.treeNode;
                            $$.treeNode = $1.treeNode; 
                        }
                        else
                        {
                            $$.treeNode = $2.treeNode;
                        }
                    }

                |   R_CASE                 // case 0: ...
                    {
                        $$.treeNode = $1.treeNode;
                    }    
                ;   


// CASE format - case 1: stmts
R_CASE          :   TOKEN_CASE TOKEN_NUM TOKEN_COLON R_LOCAL_STATEMENT_LIST
                    {
                        NodeCreate(&($$.treeNode), NODE_CASE);
                        $$.treeNode->nodeData.dVal = $2.nodeData.dVal;

                        NodeAddChild($$.treeNode, $4.treeNode);
                    }
                |   TOKEN_CASE TOKEN_CNUM TOKEN_COLON R_LOCAL_STATEMENT_LIST
                    {
                        NodeCreate(&($$.treeNode), NODE_CASE);
                        $$.treeNode->nodeData.dVal = $2.nodeData.dVal;

                        NodeAddChild($$.treeNode, $4.treeNode);
                    }
                ;
                

// CASE "default" format - default: stmts    
R_DEFAULT       :   TOKEN_DEFAULT TOKEN_COLON R_LOCAL_STATEMENT_LIST
                    {
                        NodeCreate(&($$.treeNode), NODE_DEFAULT);

                        NodeAddChild($$.treeNode, $3.treeNode);
                    }
                ;


// An IF statement can only be a simple IF or a IF ELSE                                                     
// The commonly seen ELSE IF is just a new IF statement inside the first ELSE                                   // Examples: 
R_IF_STATEMENT  :   TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT       // if (var==1) { stmts }
                    {
                        NodeCreate(&($$.treeNode), NODE_IF);

                        NodeAddChild($$.treeNode, $3.treeNode);                      // Condition:
                        NodeAddChild($$.treeNode, $5.treeNode);                      // if true
                    }

                |   TOKEN_IF TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT TOKEN_ELSE  R_LOCAL_STATEMENT     // if (var==1) { stmts } else { stmts }
                    {
                        NodeCreate(&($$.treeNode), NODE_IF);

                        NodeAddChild($$.treeNode, $3.treeNode);                      // Condition:
                        NodeAddChild($$.treeNode, $5.treeNode);                      // if true
                        NodeAddChild($$.treeNode, $7.treeNode);                      // else 
                    }
                ;


// The return statement can be used to return void or a value                         // Examples:
R_RETURN        :   TOKEN_RETURN TOKEN_SEMI                                           // return;
                    {
                        NodeCreate(&($$.treeNode), NODE_RETURN);
                        $$.treeNode->nodeData.sVal = currentFunction;
                    }
                    
                |   TOKEN_RETURN R_EXP TOKEN_SEMI                                     // return var;
                    {
                        NodeCreate(&($$.treeNode), NODE_RETURN);
                        NodeAddChild($$.treeNode, $2.treeNode);
                        $$.treeNode->nodeData.sVal = currentFunction;
                    }
                ;


//--------------------------------------------------------------------------------------------------------------------//
// Loop Statements
//--------------------------------------------------------------------------------------------------------------------//

R_WHILE_LOOP        :   TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT 
                        {

                            NodeCreate(&($$.treeNode), NODE_WHILE);
                        
                            NodeAddChild($$.treeNode, $3.treeNode);      // Condition
                            NodeAddChild($$.treeNode, $5.treeNode);      // if true
                        }
                        
                    |   TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI
                        {
                            NodeCreate(&($$.treeNode), NODE_WHILE);
                            NodeAddChild($$.treeNode, $3.treeNode);      // Condition
                        }
                    ;


R_DO_WHILE_LOOP     :   TOKEN_DO R_LOCAL_STATEMENT TOKEN_WHILE TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES TOKEN_SEMI
                        {
                            NodeCreate(&($$.treeNode), NODE_DO_WHILE);
                        
                            NodeAddChild($$.treeNode, $5.treeNode);      // Condition
                            NodeAddChild($$.treeNode, $2.treeNode);      // if true
                        }
                    ;

R_FOR_LOOP          :   TOKEN_FOR TOKEN_LEFT_PARENTHESES R_FOR_INIT_FIELD TOKEN_SEMI R_EXP TOKEN_SEMI R_FOR_ASSIGNMENT_FIELD TOKEN_RIGHT_PARENTHESES R_LOCAL_STATEMENT                    
                        {
                            TreeNode_st* pNode = $9.treeNode;
                            TreeNode_st* pNodeWhile;

                            if (pNode != NULL)
                            { 
                                while (pNode->pSibling != NULL)
                                {
                                    pNode = pNode->pSibling;    
                                }                                        
                                pNode->pSibling = $7.treeNode;
                            }
                            else
                            {
                                $$.treeNode = $7.treeNode;
                            }
                            
                            NodeCreate(&pNodeWhile, NODE_WHILE);
                        
                            NodeAddChild(pNodeWhile, $5.treeNode);      // Condition
                            NodeAddChild(pNodeWhile, $9.treeNode);      // if true
                            
                            $3.treeNode->pSibling = pNodeWhile;
                            $$.treeNode = $3.treeNode;
                        };


R_FOR_INIT_FIELD    :   TOKEN_ID TOKEN_ASSIGN R_EXP                             // for(x=0; ; )  
                        {
                            TreeNode_st *pNode;

                            NodeCreate(&($$.treeNode), NODE_OPERATOR);
                            $$.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddNewChild($$.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = $1.nodeData.sVal;

                            NodeAddChild($$.treeNode, $3.treeNode);
                        }
                    ;

                    
R_FOR_ASSIGNMENT_FIELD  :   R_SIMPLE_VAR_ASSIGN           //for( ; ;x++)
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_COMPOUND_VAR_ASSIGN
                            {
                                $$.treeNode = $1.treeNode;
                            }

                        |   R_INC_DEC
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ; 


//--------------------------------------------------------------------------------------------------------------------//
// Misc
//--------------------------------------------------------------------------------------------------------------------//
// Label definition for the goto statement.             // Example: 
R_LABEL                 :   TOKEN_ID TOKEN_COLON        // TESTE:
                            {
                                NodeCreate(&($$.treeNode), NODE_LABEL);
                                $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                            }
                        ;

//--------------------------------------------------------------------------------------------------------------------//
// Function Related Rules
//--------------------------------------------------------------------------------------------------------------------//

// Function signature i.e. the function format. Doesn't include the ; or the {. Example: int addNumbers(int x, int y)
R_FUNC_SIGNATURE        :   R_VAR_PREAMBLE TOKEN_ID TOKEN_LEFT_PARENTHESES R_ARG_LIST TOKEN_RIGHT_PARENTHESES
                            {
                                NodeCreate(&($$.treeNode), NODE_FUNCTION);
                                $$.treeNode->nodeData.sVal = $2.nodeData.sVal;

                                NodeAddChild($$.treeNode, $1.treeNode);
                                NodeAddChild($$.treeNode, $4.treeNode);

                                currentFunction = $2.nodeData.sVal;
                            }
                        ;


// Function prototype is just a function signature followed by a semi
R_FUNC_PROTOTYPE        :   R_FUNC_SIGNATURE TOKEN_SEMI 
                            {
                                $$.treeNode = $1.treeNode;
                            }
                        ;

// Function implementation containing the function signature and a compound statement where it is implemented
R_FUNC_IMPLEMENT        :   R_FUNC_SIGNATURE R_COMPOUND_STATEMENT
                            {
                                $$.treeNode = $1.treeNode;
                                NodeAddChild($$.treeNode, $2.treeNode);
                            }
                        ;

//Function call
R_FUNC_CALL             :   TOKEN_ID TOKEN_LEFT_PARENTHESES R_EXP_LIST TOKEN_RIGHT_PARENTHESES 
                            {
                                NodeCreate(&($$.treeNode), NODE_FUNCTION_CALL);
                                $$.treeNode->nodeData.sVal = $1.nodeData.sVal;

                                NodeAddChild($$.treeNode, $3.treeNode);
                            }


// Rule for expression list, expressions separated by ','   // Examples:
R_EXP_LIST  :   %empty
                {
                    $$.treeNode = NULL;
                }
            
            |   R_EXP_LIST TOKEN_COMMA R_EXP                // exp , exp
                {
                    TreeNode_st* pNode = $1.treeNode;

                    if (pNode != NULL)
                    { 
                        while (pNode->pSibling != NULL)
                        {
                            pNode = pNode->pSibling;    
                        }                                        
                        pNode->pSibling = $3.treeNode;
                        $$.treeNode = $1.treeNode; 
                    }
                    else
                    {
                        $$.treeNode = $3.treeNode;
                    }
                    pTreeRoot = $$.treeNode;
                }

            |   R_EXP                                       // exp
                {
                    $$.treeNode = $1.treeNode;
                }
            ;


// Function argument list. Note: The argument list can be empty. Example: int x | int x, int y
R_ARG_LIST              :   %empty 
                            {
                                NodeCreate(&($$.treeNode), NODE_NULL);
                            }

                        |   R_ARG_LIST TOKEN_COMMA R_ARG
                            {
                                TreeNode_st *pNode = $1.treeNode;

                                if (pNode != NULL)
                                { 
                                    while (pNode->pSibling != NULL)
                                    {
                                        pNode = pNode->pSibling;    
                                    }                                        
                                    pNode->pSibling = $3.treeNode;
                                    $$.treeNode = $1.treeNode; 
                                }
                                else
                                {
                                    $$.treeNode = $3.treeNode;
                                }
                            }

                        |   R_ARG 
                            {
                                $$.treeNode = $1.treeNode;
                            }    
                        ;

// Function argument type. Example: int x | const char* pString.
R_ARG                   :   R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID 
                            {
                                NodeCreate(&($$.treeNode), NODE_PARAMETER);
                                $$.treeNode->nodeData.sVal = $4.nodeData.sVal;

                                $2.treeNode->pSibling = $1.treeNode;
                                $3.treeNode->pSibling = $2.treeNode;

                                NodeAddChild($$.treeNode, $3.treeNode);
                            }

                        |   R_SIGN_QUALIFIER R_TYPE_ALL TOKEN_ID 
                            {
                                NodeCreate(&($$.treeNode), NODE_PARAMETER);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                $2.treeNode->pSibling = $1.treeNode;

                                NodeAddChild($$.treeNode, $2.treeNode);
                            }

                        |   R_MOD_QUALIFIER R_TYPE_ALL TOKEN_ID 
                            {
                                NodeCreate(&($$.treeNode), NODE_PARAMETER);
                                $$.treeNode->nodeData.sVal = $3.nodeData.sVal;

                                $2.treeNode->pSibling = $1.treeNode;

                                NodeAddChild($$.treeNode, $2.treeNode);
                            }        

                        |   R_TYPE_ALL TOKEN_ID 
                            {
                                NodeCreate(&($$.treeNode), NODE_PARAMETER);
                                $$.treeNode->nodeData.sVal = $2.nodeData.sVal;

                                NodeAddChild($$.treeNode, $1.treeNode);
                            }
                        ;


//--------------------------------------------------------------------------------------------------------------------//
// Variable Related Rules
//--------------------------------------------------------------------------------------------------------------------//

// Variable declaration (simple or followed by its assignment).                         // Examples:
R_VAR_DECLARATION       :   R_VAR_PREAMBLE R_ID_LIST TOKEN_SEMI                         // int var1, var2;    -> int var1, var2;
                            {   
                                TreeNode_st* pNode =  $2.treeNode;

                                TreeNode_st nodePreambleCopy;
                                memcpy(&nodePreambleCopy, $1.treeNode, sizeof(TreeNode_st));
                                free($1.treeNode);

                                do
                                {
                                    if(pNode->nodeType == NODE_VAR_DECLARATION)
                                    {
                                        NodeAddChildCopy(pNode, &nodePreambleCopy);
                                    }

                                    pNode = pNode->pSibling;    
                                }while (pNode != NULL); 

                                $$.treeNode = $2.treeNode; 
                            }

                        |   R_ARR_DECLARATION
                            {
                                $$.treeNode = $1.treeNode; 
                            } 
                        ;    

//--------------------------------------------------------------------------------------------------------------------//
// ARRAYS
//--------------------------------------------------------------------------------------------------------------------//
// Array declaration                                                                                // Examples:
R_ARR_DECLARATION   :   R_VAR_PREAMBLE TOKEN_ID R_ARR_SIZE TOKEN_SEMI                               // int var [2];
                        {
                            NodeCreate(&($$.treeNode), NODE_ARRAY_DECLARATION);
                            $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                            
                            NodeAddChild($$.treeNode, $1.treeNode);
                            NodeAddChild($$.treeNode, $3.treeNode);
                        }      
                    ;    

// Dimensions of the array                                                                  // Examples:
R_ARR_SIZE          :   TOKEN_LEFT_BRACKET TOKEN_NUM TOKEN_RIGHT_BRACKET            // [2]
                        {
                            NodeCreate(&($$.treeNode), NODE_INTEGER);
                            $$.treeNode->nodeData.dVal = $2.nodeData.dVal;
                        }
                    ;


//Used only in variables declaration - Example: (int) x, y=2, z;
R_ID_LIST      :    R_ID_LIST TOKEN_COMMA TOKEN_ID                                
                    {
                        TreeNode_st *pNode;
                        TreeNode_st* pNewNode; 
                          
                        NodeCreate(&pNewNode, NODE_VAR_DECLARATION);
                        pNewNode->nodeData.sVal = $3.nodeData.sVal;

                        pNode = $1.treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = pNewNode;
                            $$.treeNode = $1.treeNode; 
                        }
                        else
                        {
                            $$.treeNode = pNewNode;
                        }
                    }

                |   R_ID_LIST TOKEN_COMMA R_SIMPLE_VAR_ASSIGN
                    {
                        TreeNode_st *pNode;
                        TreeNode_st* pNewNode;
                        pNode = $3.treeNode->pChilds;   //Var indentifier - first child


                        NodeCreate(&pNewNode, NODE_VAR_DECLARATION);
                        pNewNode->nodeData.sVal = pNode->nodeData.sVal;


                        pNode = $1.treeNode;

                        if (pNode != NULL)
                        { 
                            while (pNode->pSibling != NULL)
                            {
                                pNode = pNode->pSibling;    
                            }                                        
                            pNode->pSibling = pNewNode;
                            $$.treeNode = $1.treeNode; 
                        }
                        else
                        {
                            $$.treeNode = pNewNode;
                        }

                        pNewNode->pSibling = $3.treeNode;
                    }                    

                |   R_SIMPLE_VAR_ASSIGN
                    {
                        TreeNode_st *pNode;
                        pNode = $1.treeNode->pChilds;   //Var indentifier - first child

                        NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
                        $$.treeNode->nodeData.sVal = pNode->nodeData.sVal;

                        $$.treeNode->pSibling = $1.treeNode;
                    }

                |   TOKEN_ID
                    {
                        NodeCreate(&($$.treeNode), NODE_VAR_DECLARATION);
                        $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                    }
                ;

//--------------------------------------------------------------------------------------------------------------------//
// VARIABLE ASSIGN
//--------------------------------------------------------------------------------------------------------------------//           
// Rule to assign a value to a variable.                                                // Example:
R_VAR_ASSIGNMENT    :   R_SIMPLE_VAR_ASSIGN TOKEN_SEMI                                  //var = 1;
                        {                                                               //var &= 4;
                            $$.treeNode = $1.treeNode;
                        }

                    |   R_COMPOUND_VAR_ASSIGN TOKEN_SEMI
                        {
                            $$.treeNode = $1.treeNode;
                        }

                    |   R_ARRAY_INDEX TOKEN_ASSIGN R_EXP TOKEN_SEMI      //array[1] = 3;
                        {
                            NodeCreate(&($$.treeNode), NODE_OPERATOR);
                            $$.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddChild($$.treeNode, $1.treeNode);
                            NodeAddChild($$.treeNode, $3.treeNode);
                        } 

                    |   R_POINTER_CONTENT TOKEN_ASSIGN R_EXP TOKEN_SEMI     // *pointer = 3;
                        {
                            NodeCreate(&($$.treeNode), NODE_OPERATOR);
                            $$.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddChild($$.treeNode, $1.treeNode);
                            NodeAddChild($$.treeNode, $3.treeNode);
                        }     
                    ;


R_COMPOUND_VAR_ASSIGN:   TOKEN_ID R_COMPOUND_ASSIGN_OPERATOR R_EXP                               // var &= 1
                        {
                            TreeNode_st *pNode;

                            NodeAddNewChild($2.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = $1.nodeData.sVal;

                            NodeAddChild($2.treeNode, $3.treeNode);

                            $$.treeNode = $2.treeNode;
                        }
                    ;


R_SIMPLE_VAR_ASSIGN:  TOKEN_ID TOKEN_ASSIGN R_EXP                                     // var = 1 
                        {
                            TreeNode_st *pNode;

                            NodeCreate(&($$.treeNode), NODE_OPERATOR);
                            $$.treeNode->nodeData.dVal = OP_ASSIGN;

                            NodeAddNewChild($$.treeNode, &pNode, NODE_IDENTIFIER);
                            pNode->nodeData.sVal = $1.nodeData.sVal;

                            NodeAddChild($$.treeNode, $3.treeNode);
                        }
                    ;                                                         


// Variable declarations can have a visibility qualifier (extern/static), a type qualifier (volatile/const), a sign qualifier.
// (signed/unsigned) and must explicitly specify a type (short, int, float...).                                             // Examples:
R_VAR_PREAMBLE          :   R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL                     // static const unsigned int var 
                            {
                                $4.treeNode->pSibling = $1.treeNode;
                                $1.treeNode->pSibling = $2.treeNode;
                                $2.treeNode->pSibling = $3.treeNode;
                                $$.treeNode = $4.treeNode;
                            }
                                                
                        |   R_VISIBILITY_QUALIFIER R_MOD_QUALIFIER R_TYPE_ALL                                      // static const int var
                            {
                                $3.treeNode->pSibling = $1.treeNode;
                                $1.treeNode->pSibling = $2.treeNode;
                                $$.treeNode = $3.treeNode;
                            }                 
                                            
                        |   R_VISIBILITY_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL                                     // static signed int var 
                            {
                                $3.treeNode->pSibling = $1.treeNode;
                                $1.treeNode->pSibling = $2.treeNode;
                                $$.treeNode = $3.treeNode;
                            }               
                                            
                        |   R_MOD_QUALIFIER R_SIGN_QUALIFIER R_TYPE_ALL                                            // const signed int var 
                            {
                                $3.treeNode->pSibling = $1.treeNode;
                                $1.treeNode->pSibling = $2.treeNode;
                                $$.treeNode = $3.treeNode;
                            }          
                                                       
                        |   R_VISIBILITY_QUALIFIER R_TYPE_ALL                                                      // static int var 
                            {
                                $2.treeNode->pSibling = $1.treeNode;
                                $$.treeNode = $2.treeNode;
                            }                 
                                                    
                        |   R_MOD_QUALIFIER R_TYPE_ALL                                                             // const int var  
                            {
                                $2.treeNode->pSibling = $1.treeNode;
                                $$.treeNode = $2.treeNode;
                            }                                                
                                      
                        |   R_SIGN_QUALIFIER R_TYPE_ALL                                                            // signed int var  
                            {
                                $2.treeNode->pSibling = $1.treeNode;
                                $$.treeNode = $2.treeNode;
                            }                                      
                                                 
                        |   R_TYPE_ALL                                                                           // int var 
                            {
                                $$.treeNode = $1.treeNode; 
                            }
                        ; 

//--------------------------------------------------------------------------------------------------------------------//
// Expressions
//--------------------------------------------------------------------------------------------------------------------//
// Main expression rule
R_EXP       :   TOKEN_MINUS R_EXP
                {
                    NodeCreate(&($$.treeNode), NODE_OPERATOR);
                    $$.treeNode->nodeData.dVal = OP_MINUS;

                    NodeAddChild($$.treeNode, $2.treeNode);  
                }

            |   R_EXP R_ARITHMETIC_OPERATOR R_TERM
                {
                    NodeAddChild($2.treeNode, $1.treeNode); 
                    NodeAddChild($2.treeNode, $3.treeNode); 

                    $$.treeNode = $2.treeNode;
                }

            |   R_EXP R_CONDITION_OPERATOR R_TERM
                {
                    NodeAddChild($2.treeNode, $1.treeNode); 
                    NodeAddChild($2.treeNode, $3.treeNode); 

                    $$.treeNode = $2.treeNode;
                }

            |   R_EXP R_BITWISE_OPERATOR R_TERM
                {
                    NodeAddChild($2.treeNode, $1.treeNode); 
                    NodeAddChild($2.treeNode, $3.treeNode); 

                    $$.treeNode = $2.treeNode; 
                }

            |   TOKEN_BITWISE_NOT R_TERM                   // ~
                {
                    NodeCreate(&($$.treeNode), NODE_OPERATOR);
                    $$.treeNode->nodeData.dVal = OP_BITWISE_NOT;
                    NodeAddChild($$.treeNode, $2.treeNode); 
                }    

            |   R_EXP R_LOGIC_OPERATOR R_TERM
                {
                    NodeAddChild($2.treeNode, $1.treeNode); 
                    NodeAddChild($2.treeNode, $3.treeNode); 

                    $$.treeNode = $2.treeNode;
                }

            |   R_EXP TOKEN_TERNARY R_EXP TOKEN_COLON R_EXP
                {
                    NodeCreate(&($$.treeNode), NODE_TERNARY);

                    NodeAddChild($$.treeNode, $1.treeNode); 
                    NodeAddChild($$.treeNode, $3.treeNode); 
                    NodeAddChild($$.treeNode, $5.treeNode);   
                }

            |   R_TERM
                {
                    $$.treeNode = $1.treeNode;
                }
            ;



// Prioritize operators, and minimize rule duplication
R_TERM      :   R_TERM R_PRIORITY_OPERATOR R_OPERAND 
                {
                    NodeAddChild($2.treeNode, $1.treeNode); 
                    NodeAddChild($2.treeNode, $3.treeNode); 
                    
                    $$.treeNode = $2.treeNode;
                }
                
            |   R_OPERAND
                {
                    $$.treeNode =  $1.treeNode;
                }
            ;

// Simplify parsing, prioritize operators, and minimize rule duplication
R_OPERAND   :   R_INC_DEC
                {
                    $$.treeNode =  $1.treeNode;
                }

            |   TOKEN_LOGICAL_NOT R_FACTOR
                {
                    NodeCreate(&($$.treeNode), NODE_OPERATOR);
                    $$.treeNode->nodeData.dVal = OP_LOGICAL_NOT;

                    NodeAddChild($$.treeNode, $2.treeNode);
                }

            |   R_TYPE_CAST R_FACTOR
                {
                    NodeAddChild($1.treeNode, $2.treeNode);
                    $$.treeNode = $1.treeNode;
                }

            |   R_FACTOR
                {
                    $$.treeNode =  $1.treeNode; 
                }
            ;



//Factor contains the atomic units within expressions, like numbers, IDs, etc.  // Examples:
R_FACTOR    :   TOKEN_LEFT_PARENTHESES R_EXP TOKEN_RIGHT_PARENTHESES            // (exp)
                {
                    $$.treeNode =  $2.treeNode;
                }

            |   R_ARRAY_INDEX
                {
                    $$.treeNode =  $1.treeNode;
                }
                
            |   TOKEN_MINUS TOKEN_NUM                                           // -1
                {   
                    NodeCreate(&($$.treeNode), NODE_INTEGER);
                    $$.treeNode->nodeData.dVal = -$2.nodeData.dVal;
                }    

            |   TOKEN_NUM                                                       // 1
                {   
                    NodeCreate(&($$.treeNode), NODE_INTEGER);
                    $$.treeNode->nodeData.dVal = $1.nodeData.dVal;
                }

            |   TOKEN_ID                                                        // a
                {
                    NodeCreate(&($$.treeNode), NODE_IDENTIFIER);
                    $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                }

            |   R_POINTER_CONTENT                                               // *a
                {
                    $$.treeNode = $1.treeNode;
                }

            |   TOKEN_MINUS TOKEN_FNUM                                         // 1.5
                {
                    NodeCreate(&($$.treeNode), NODE_FLOAT);
                    $$.treeNode->nodeData.fVal = -$2.nodeData.fVal;
                }     

            |   TOKEN_FNUM                                                     // 1.5
                {
                    NodeCreate(&($$.treeNode), NODE_FLOAT);
                    $$.treeNode->nodeData.fVal = $1.nodeData.fVal;
                } 

            |   TOKEN_CNUM                                                      // 'c'
                {
                    NodeCreate(&($$.treeNode), NODE_CHAR);
                    $$.treeNode->nodeData.dVal = $1.nodeData.dVal;
                }      
                   
            |   TOKEN_STR                                                      // "abc"
                {
                    NodeCreate(&($$.treeNode), NODE_STRING);
                    $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                }

            |   TOKEN_BITWISE_AND R_ARRAY_INDEX                               // &a
                {
                    NodeCreate(&($$.treeNode), NODE_REFERENCE);
                    NodeAddChild($$.treeNode, $2.treeNode);  
                }
            ;

            |   TOKEN_BITWISE_AND TOKEN_ID                                     // &a
                {
                    NodeCreate(&($$.treeNode), NODE_REFERENCE);
                    $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                }

            |   R_FUNC_CALL
                {
                    $$.treeNode = $1.treeNode;
                }
            ;


R_ARRAY_INDEX:  TOKEN_ID TOKEN_LEFT_BRACKET R_EXP TOKEN_RIGHT_BRACKET           // a[x]
                {
                    NodeCreate(&($$.treeNode), NODE_ARRAY_INDEX);
                    $$.treeNode->nodeData.sVal = $1.nodeData.sVal;

                    NodeAddChild($$.treeNode, $3.treeNode);  
                }
            ;                


R_POINTER_CONTENT:  TOKEN_ASTERISK TOKEN_ID
                    {
                        NodeCreate(&($$.treeNode), NODE_POINTER_CONTENT);
                        $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                    }
                ;  


// Increment/Decrement group
R_INC_DEC   :   R_PRE_INCREMENT
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_POST_INCREMENT
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_PRE_DECREMENT
                {
                    $$.treeNode = $1.treeNode;
                }

            |   R_POST_DECREMENT
                {
                    $$.treeNode = $1.treeNode;
                }
            ;


// Increment/Decrement types                                            // Examples:
R_PRE_INCREMENT     :   TOKEN_INCREMENT TOKEN_ID                        // ++a
                        {
                            NodeCreate(&($$.treeNode), NODE_PRE_INC);
                            $$.treeNode->nodeData.sVal = $2.nodeData.sVal;
                        }
                    ;


R_POST_INCREMENT    :   TOKEN_ID TOKEN_INCREMENT                        // a++
                        {
                            NodeCreate(&($$.treeNode), NODE_POST_INC);
                            $$.treeNode->nodeData.sVal = $1.nodeData.sVal; 
                        }
                    ;


R_PRE_DECREMENT     :   TOKEN_DECREMENT TOKEN_ID                        // --a
                        {
                            NodeCreate(&($$.treeNode), NODE_PRE_DEC);
                            $$.treeNode->nodeData.sVal = $2.nodeData.sVal; 
                        }
                    ;


R_POST_DECREMENT    :   TOKEN_ID TOKEN_DECREMENT                        // a--
                        {
                            NodeCreate(&($$.treeNode), NODE_POST_DEC);
                            $$.treeNode->nodeData.sVal = $1.nodeData.sVal;
                        }
                    ;


//--------------------------------------------------------------------------------------------------------------------//
// Operators
//--------------------------------------------------------------------------------------------------------------------//

// Arithmetic operators                                             // Operators:
R_ARITHMETIC_OPERATOR   :   TOKEN_PLUS                              // +    
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_PLUS;
                            } 

                        |   TOKEN_MINUS                             // -
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_MINUS;
                            }

                        |   TOKEN_RIGHT_SHIFT                       // >>
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_RIGHT_SHIFT;
                            }

                        |   TOKEN_LEFT_SHIFT                        // <<
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_LEFT_SHIFT;
                            }
                        ;

// Priority operators                                               // Operators:
R_PRIORITY_OPERATOR     :   TOKEN_ASTERISK                          // *
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_MULTIPLY;
                            }

                        |   TOKEN_OVER                              // /
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_DIVIDE;
                            }

                        |   TOKEN_PERCENT                           // %
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_REMAIN;
                            }
                        ;

// Condition operators                                              // Operators:
R_CONDITION_OPERATOR    :   TOKEN_GREATER_THAN                      // >
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_GREATER_THAN;
                            }

                        |   TOKEN_LESS_THAN_OR_EQUAL                // <=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_LESS_THAN_OR_EQUAL;
                            }

                        |   TOKEN_GREATER_THAN_OR_EQUAL             // >=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_GREATER_THAN_OR_EQUAL;
                            }

                        |   TOKEN_LESS_THAN                         // <
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_LESS_THAN;
                            }

                        |   TOKEN_EQUAL                             // ==
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_EQUAL;
                            }

                        |   TOKEN_NOT_EQUAL                         // !=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_NOT_EQUAL;
                            }
                        ;

// Logic operators                                                  // Operators:
R_LOGIC_OPERATOR        :   TOKEN_LOGICAL_AND                       // &&
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_LOGICAL_AND;
                            }

                        |   TOKEN_LOGICAL_OR                        // ||
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_LOGICAL_OR;
                            }
                        ;

// Bitwise operators                                                // Operators:
R_BITWISE_OPERATOR      :   TOKEN_BITWISE_AND                       // &
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_AND;
                            }

                        |   TOKEN_BITWISE_OR                        // |
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_OR;
                            }

                        |   TOKEN_BITWISE_XOR                       // ^
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_XOR;
                            }
                        ;

// Assign operators                                                  // Operators:
R_COMPOUND_ASSIGN_OPERATOR: TOKEN_PLUS_ASSIGN                       // +=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_PLUS_ASSIGN;
                            }

                        |   TOKEN_MINUS_ASSIGN                      // -=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_MINUS_ASSIGN;
                            }
                            
                        |   TOKEN_MODULUS_ASSIGN                    // %=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_MODULUS_ASSIGN;
                            }
                            
                        |   TOKEN_LEFT_SHIFT_ASSIGN                 //<<=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_LEFT_SHIFT_ASSIGN;
                            }

                        |   TOKEN_RIGHT_SHIFT_ASSIGN                // >>=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_RIGHT_SHIFT_ASSIGN;
                            }
                            
                        |   TOKEN_BITWISE_AND_ASSIGN                // &=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_AND_ASSIGN;
                            }

                        |   TOKEN_BITWISE_OR_ASSIGN                 // |=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_OR_ASSIGN;
                            }

                        |   TOKEN_BITWISE_XOR_ASSIGN                // ^=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_BITWISE_XOR_ASSIGN;
                            }

                        |   TOKEN_MULTIPLY_ASSIGN                   // *=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_MULTIPLY_ASSIGN;
                            }

                        |   TOKEN_DIVIDE_ASSIGN                     // /=
                            {
                                NodeCreate(&($$.treeNode), NODE_OPERATOR);
                                $$.treeNode->nodeData.dVal = OP_DIVIDE_ASSIGN;
                            }
                        ;


//--------------------------------------------------------------------------------------------------------------------//
// TYPPES (VARIABLES AND FUNCTIONS)
//--------------------------------------------------------------------------------------------------------------------//

// Type cast
R_TYPE_CAST             :   TOKEN_LEFT_PARENTHESES R_TYPE_ALL TOKEN_RIGHT_PARENTHESES                   
                            {
                                NodeCreate(&($$.treeNode), NODE_TYPE_CAST);
                                NodeAddChild($$.treeNode, $2.treeNode);
                            }
                        ;


// Union between the pointer and standard types.
R_TYPE_ALL                  :   R_TYPE 
                                {
                                    $$.treeNode = $1.treeNode;  
                                }
                                
                            |   R_TYPE_PTR
                                {
                                    $$.treeNode = $1.treeNode;
                                }
                            ;


// Standard C data types but with pointer.
R_TYPE_PTR                  :   R_TYPE TOKEN_ASTERISK
                                {  
                                    NodeCreate(&($$.treeNode), NODE_POINTER);

                                    NodeAddChild($$.treeNode, $1.treeNode);                                
                                }
                            ;                                      
           
            
// Standard C data types. 
// Doesn't account for user defined types (aka typedefs), as this will need a symbol table.     // Data Types:
R_TYPE                      :   TOKEN_CHAR                                                      // Char  
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_CHAR;
                                }

                            |   TOKEN_SHORT                                                     // Short
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_SHORT;
                                }

                            |   TOKEN_INT                                                       // Int
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_INT;
                                }

                            |   TOKEN_LONG                                                      // Long
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_LONG;
                                }

                            |   TOKEN_FLOAT                                                     // Float
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_FLOAT;
                                }
                                
                            |   TOKEN_DOUBLE                                                    // Double
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_DOUBLE;
                                }

                            |   TOKEN_LONG TOKEN_DOUBLE                                         // Long Double
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_LONG_DOUBLE;
                                }
                            |   TOKEN_VOID 
                                {
                                    NodeCreate(&($$.treeNode), NODE_TYPE);
                                    $$.treeNode->nodeData.dVal = TYPE_VOID;
                                }   
                            ;


// Functions and variables can be marked as either static or extern, never both at the same time.
R_VISIBILITY_QUALIFIER      :   TOKEN_STATIC
                                {
                                    NodeCreate(&($$.treeNode), NODE_VISIBILITY);
                                    $$.treeNode->nodeData.dVal = (long int) VIS_STATIC;    
                                }

                            |   TOKEN_EXTERN
                                {
                                    NodeCreate(&($$.treeNode), NODE_VISIBILITY);
                                    $$.treeNode->nodeData.dVal = (long int) VIS_EXTERN;     
                                }
                            ;


// Types can be marked as constant, volatile, or have no type qualifier.
// Here is also some other more advanced qualifiers not being considered.
R_MOD_QUALIFIER             :   TOKEN_CONSTANT
                                {
                                    NodeCreate(&($$.treeNode), NODE_MODIFIER);
                                    $$.treeNode->nodeData.dVal = (long int) MOD_CONST;
                                } 

                            |   TOKEN_VOLATILE
                                {
                                    NodeCreate(&($$.treeNode), NODE_MODIFIER);
                                    $$.treeNode->nodeData.dVal = (long int) MOD_VOLATILE; 
                                }
                            ;

// Types can be marked as signed or unsigned, in C, if none is specified, the type defaults to signed.
R_SIGN_QUALIFIER            :   TOKEN_SIGNED 
                                {
                                    NodeCreate(&($$.treeNode), NODE_SIGN);
                                    $$.treeNode->nodeData.dVal = (long int) SIGN_SIGNED; 
                                }

                            |   TOKEN_UNSIGNED
                                {
                                    NodeCreate(&($$.treeNode), NODE_SIGN);
                                    $$.treeNode->nodeData.dVal = (long int) SIGN_UNSIGNED;
                                }
                            ;
%%


//--------------------------------------------------------------------------------------------------------------------//
// Code
//--------------------------------------------------------------------------------------------------------------------//
int executeParser(TreeNode_st** ppTreeRoot)
{
    int ret;

    if (!ppTreeRoot)
        return -EINVAL;
    
    ret = initLexer();
    if (ret < 0)
    {
        LOG_ERROR("Failed to get source file!\n");
        return ret; 
    }

    LOG_WARNING("\n--------------Parser Start--------------\n");

    ret = yyparse();

    *ppTreeRoot = pTreeRoot;

    return ret;
}


int yyerror(char* pStr)
{
    if (!pStr)
        return -EINVAL;

    LOG_ERROR("Error at line: %lu | Error was: %s\n", getLineNumber(), pStr);

    return 0;
}


const char* getTokenName(int tokenValue) 
{
    return yysymbol_name(YYTRANSLATE(tokenValue));
}
