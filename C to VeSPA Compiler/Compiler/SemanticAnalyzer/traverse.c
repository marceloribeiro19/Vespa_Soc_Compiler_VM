#include <errno.h>
#include "../Util/Util.h"
#include "../Util/Globals.h"
#include "../Util/Logger.h"
#include "../main.h"
#include "../SemanticAnalyzer/traverse.h"

SymbolTable_st* pGlobalSymTable;
SymbolTable_st* pCurrentScope;
static bool initialized = false;
static uint32_t errorCounter = 0;

static int globalMemoryLocation = 0;
static int localMemoryLocation = 0;

static void buildSymbolTables(TreeNode_st* pNode);
static void checkNode(TreeNode_st * pNode);

/**
 * @brief Post-order traversal of the AST, running a type-checking function at each node
 */
static void TypeCheckTraverse(TreeNode_st* pSintaxTree)
{
    traverse(pSintaxTree,nullProc,checkNode);
}

/**
 * @brief Pre-order traversal of the AST, running a symbol table function at each node 
 *        and building symbol tables for each scope
 */
static void SymbolTableTraverse(TreeNode_st* pSintaxTree)
{
    traverse(pSintaxTree,buildSymbolTables,nullProc);
}

/**
 * @brief reports a semantic error encountered during AST traverse
 */
static int semanticError(TreeNode_st* pNode, char * message)
{ 
     if (!message)
        return -EINVAL;

    errorCounter++;
    LOG_ERROR("Semantic error at line %d: %s\n", pNode->lineNumber, message);
    return 0;  
}

/**
 * @brief depth-first traversal of an AST

 * @param pNode pointer to the current AST node
 * @param preOrder pointer to the pre-order function to be applied at each node
 * @param postOrder pointer to the post-order function to be applied at each node
 */
void traverse (TreeNode_st* pNode, void (*preOrder) (TreeNode_st* ), void (*postOrder) (TreeNode_st* ))
{
    if (pNode != NULL)
    {
        preOrder(pNode);                                                      
  
        for ( int i = 0 ; i < pNode->childNumber ; i++ )
        {
            traverse (&pNode->pChilds[i], preOrder, postOrder); 
        }

        postOrder(pNode);                                                 
        traverse (pNode->pSibling,preOrder,postOrder);                                                        
    }
}

/**
 * @brief placeholder function that doesn't really do anything
 */
void nullProc(TreeNode_st * st)
{ 
    if (st==NULL) 
        return;
    else 
        return;
}

/**
 * @brief executes a semantic analysis on the AST, including
 *        symbol tables construction, type checking and errors report
 */
int executeSemanticAnalisys(TreeNode_st* pTreeRoot, SymbolTable_st** ppGlobalTable)
{
    if (!ppGlobalTable || !pTreeRoot)
        return -EINVAL;


    if(!initialized)
    {
        if(createSymbolTable(&pGlobalSymTable, NULL))
        {
            return 1;   //error creating symbol table
        }

        initialized = true;
    }

    *ppGlobalTable = pGlobalSymTable;
    pCurrentScope = pGlobalSymTable;

    SymbolTableTraverse(pTreeRoot);

    LOG_WARNING("STARTING TYPE CHECKING\n");
        
    // type checking is not performed if errors are detected during symbol tables construction
    if(errorCounter == 0)
    {
        TypeCheckTraverse(pTreeRoot);
    }

    if(errorCounter > 0)
    {
        LOG_ERROR(": %d error(s) found during semantic analisys!\n", errorCounter);
        return SEMANTIC_ERROR;
    }

    LOG_DEBUG("%d error(s) found during semantic analisys!\n", errorCounter);
    return SEMANTIC_OK;
}


/******************************************************************************************
******************************       TYPE CHECKING      **********************************
******************************************************************************************/

int pointerAssignCheck(TreeNode_st* pCurrentNode, VarType_et pLeftVarType, TreeNode_st* pRightValue)
{
    if (pRightValue->nodeType == NODE_IDENTIFIER)        //pointer = pointer    
    {
        if(pRightValue->pSymbol->symbolType != SYMBOL_POINTER && pRightValue->pSymbol->symbolType != SYMBOL_ARRAY)
        {
            semanticError(pCurrentNode, "Assignemt to a non a pointer expression! \n");
            return SEMANTIC_ERROR;
        }
    }
    else if (pRightValue->nodeType == NODE_REFERENCE)
    {
        if(pRightValue->pSymbol->symbolType == SYMBOL_ARRAY)
        {
            if(pRightValue->childNumber == 0)       //ptr = &array (not permited)
            {
                semanticError(pCurrentNode, "Incompatible assignemt! \n");
                return SEMANTIC_ERROR; 
            }
        } 
        else if(pRightValue->pSymbol->symbolType != SYMBOL_VARIABLE)
        {
            semanticError(pCurrentNode, "Incompatible assignemt! \n");
            return SEMANTIC_ERROR; 
        }
    }
    else if (pRightValue->nodeType == NODE_STRING)
    {
        if(pLeftVarType != TYPE_CHAR)
        {
            semanticError(pCurrentNode, "Can not assign a literal string to a non char pointer! \n");
            return SEMANTIC_ERROR; 
        }
        else
            return SEMANTIC_OK;
    }
    else if (pRightValue->nodeType == NODE_POINTER)
    {
        TreeNode_st* pChild_aux;
        pChild_aux = &pCurrentNode->pChilds[1];
        pChild_aux = &pChild_aux->pChilds[1];

        if(pRightValue->nodeVarType != pLeftVarType)
        {
            semanticError(pCurrentNode, "Typecast type and pointer type don't match! \n");
            return SEMANTIC_ERROR; 
        }
        else if (pChild_aux->nodeVarType != TYPE_CHAR && pChild_aux->nodeVarType != TYPE_INT && 
                 pChild_aux->nodeVarType != TYPE_SHORT && pChild_aux->nodeVarType != TYPE_LONG)
        {
            semanticError(pCurrentNode, "Typecast type not supported!\n");
            return SEMANTIC_ERROR; 
        }
    }
    else
    {
        semanticError(pCurrentNode, "Incompatible assignemt! \n");
        pCurrentNode->nodeVarType = TYPE_VOID;
        return SEMANTIC_ERROR;   
    }
    return SEMANTIC_OK;
}


/**
 * @brief Checks the type of an operator, the operation validity
 *        and the type and compatibility of the operands
 *
 * @param pNode pointer to the operator AST node
 */
static int checkOperator(TreeNode_st * pNode)
{
    SymbolEntry_st* pEntryChild1;
    SymbolEntry_st* pEntryChild2;
    SymbolEntry_st* pEntryAux;
    TreeNode_st* pChild1;
    TreeNode_st* pChild2;

    int varType1;
    int varType2;

    switch(pNode->nodeData.dVal)
    {
        // Valid examples:  !int_var
        case OP_LOGICAL_NOT:
        case OP_BITWISE_NOT:
            pChild1 = &pNode->pChilds[0];

            varType1 = pChild1->nodeVarType;
            
            if (varType1 == TYPE_VOID  || varType1 == TYPE_STRING || varType1 == TYPE_DOUBLE ||
                varType1 == TYPE_FLOAT || varType1 == TYPE_LONG_DOUBLE)
            {
                semanticError(pNode, "Operands types don't match!\n");
                return SEMANTIC_ERROR;
            }
            else
            {
                pNode->nodeVarType = pChild1->nodeVarType;
            }
            break;        


        // Valid examples:  pointer = pointer           char* char_var = "string"
        //                  pointer = &array[2]         int_var = int_var
        case OP_ASSIGN:
        case OP_PLUS_ASSIGN:
        case OP_MINUS_ASSIGN:
            TreeNode_st* pChild_aux;
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            varType1 = pChild1->nodeVarType;

            if(pChild2->nodeType == NODE_TYPE_CAST)
            {
                varType2 = pChild2->nodeVarType;
                pChild2 = pChild2->pChilds;
                pChild2->nodeVarType = varType2;            // TESTE
            }
            else
            {
                varType2 = pChild2->nodeVarType;
            }

            if(pChild1->pSymbol != NULL)
            {
                if(!(pChild1->pSymbol->symbolType == SYMBOL_POINTER && varType2 == TYPE_STRING && varType1 == TYPE_CHAR) && (varType1 != varType2))
                {
                    semanticError(pNode, "Operands types don't match!\n");
                    return SEMANTIC_ERROR; 
                }


                switch (pChild1->nodeType)
                {
                case NODE_POINTER_CONTENT:
                case NODE_ARRAY_INDEX:
                    if (pChild2->nodeType == NODE_REFERENCE) 
                    {
                        semanticError(pNode, "Incompatible reference to pointer assignemt! \n");   
                        return SEMANTIC_ERROR;
                    }
                    else if (pChild2->nodeType == NODE_IDENTIFIER) 
                    {
                        if(pChild2->pSymbol->symbolType == SYMBOL_POINTER)
                        {
                            semanticError(pNode, "Incompatible pointer assignemt! \n");
                            return SEMANTIC_ERROR;
                        }
                    }
                    break;


                case NODE_IDENTIFIER:
                    if (pChild1->pSymbol->symbolType == SYMBOL_POINTER) 
                    {
                        return pointerAssignCheck(pNode, pChild1->nodeVarType, pChild2);
                    } 
                    else if(pChild1->pSymbol->symbolType == SYMBOL_FUNCTION) 
                    {
                        semanticError(pNode, "Assignment to function is not permited! \n");
                        return SEMANTIC_ERROR;   
                    }
                    else
                    {
                        if(pChild2->pSymbol != NULL && pChild2->pSymbol->symbolType == SYMBOL_POINTER && pChild2->nodeType != NODE_POINTER_CONTENT){
                            semanticError(pNode, "Incompatible pointer to identifier assignemt! \n");
                            return SEMANTIC_ERROR; 
                        }
                        else if(pChild2->nodeType == NODE_REFERENCE)
                        {
                            semanticError(pNode, "Incompatible reference to identifier assignemt! \n");
                            return SEMANTIC_ERROR;   
                        }
                    }
                    break;  
                

                default:
                    semanticError(pNode, "Default incompatible assignemt! \n");
                    pNode->nodeVarType = TYPE_VOID;
                    break;
                }

                pNode->nodeVarType = varType1;
            }
            break;


        // Valid examples:  char_var / char_var     double_var / double_var
        //                  int_var / int_var       float_var / float_var
        case OP_DIVIDE:
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            // can't divide by zero
            if(((pChild2->nodeType == NODE_INTEGER) && (pChild2->nodeData.dVal == 0)) || ((pChild2->nodeType == NODE_FLOAT) && (pChild2->nodeData.fVal == 0.0)))
            {
                semanticError(pNode, "Division by zero is not supported\n");
                return SEMANTIC_ERROR;
            }
            else
            {
                varType1 = pChild1->nodeVarType;
                varType2 = pChild2->nodeVarType;

                if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                    (varType2 == TYPE_STRING || varType2 == TYPE_VOID ))
                {
                    semanticError(pNode, "Invalid operand type!\n");
                    return SEMANTIC_ERROR;
                }
                else if (varType1 != varType2)
                {
                    semanticError(pNode, "Operands types don't match!\n");
                    return SEMANTIC_ERROR;
                }                
                else
                {
                    pNode->nodeVarType = varType1;
                }
            }
            break;


        // Valid examples:  int_var + int_var       char_var == char_var
        //                   double_var >= double_var
        case OP_PLUS:
        case OP_MINUS:
        case OP_MULTIPLY:
        case OP_EQUAL:
        case OP_NOT_EQUAL:
        case OP_GREATER_THAN:
        case OP_LESS_THAN:
        case OP_LESS_THAN_OR_EQUAL:
        case OP_GREATER_THAN_OR_EQUAL:
        case OP_LOGICAL_AND:
        case OP_LOGICAL_OR:  
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            varType1 = pChild1->nodeVarType;
            varType2 = pChild2->nodeVarType;

            if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                (varType2 == TYPE_STRING || varType2 == TYPE_VOID )) 
            {               
                semanticError(pNode, "Invalid operand type!\n");
                return SEMANTIC_ERROR;
            }
            else if (varType1 != varType2)
            {
                semanticError(pNode, "Operands types don't match!\n");
                return SEMANTIC_ERROR;
            }
            else
            {
                pNode->nodeVarType = varType1;
            }
            break;


        // Valid examples:  int_var & int_var       char_var << char_var
        case OP_BITWISE_AND_ASSIGN:
        case OP_BITWISE_OR_ASSIGN:
        case OP_BITWISE_XOR_ASSIGN:
        case OP_BITWISE_AND:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
        case OP_RIGHT_SHIFT:
        case OP_LEFT_SHIFT:
        case OP_REMAIN:
            pChild1 = &pNode->pChilds[0];
            pChild2 = &pNode->pChilds[1];

            varType1 = pChild1->nodeVarType;
            varType2 = pChild2->nodeVarType;

            if (!(varType1 == TYPE_INT || varType1 == TYPE_CHAR || varType1 == TYPE_SHORT || varType1 == TYPE_LONG ||
                varType2 == TYPE_INT || varType2 == TYPE_CHAR || varType2 == TYPE_SHORT || varType2 == TYPE_LONG)) 
            {
                semanticError(pNode, "Operands with floating point are not supported!\n");
                return SEMANTIC_ERROR;
            }
            else if(varType1 != varType2)
            {
                semanticError(pNode, "Operands types don't match!\n");
                return SEMANTIC_ERROR;
            }
            else
            {
                pNode->nodeVarType = varType1;
            }
            break;   
    }
}

/**
 * @brief Checks the semantic validity of an AST node and specifies its type
 *
 * @param pNode pointer to the AST node to be checked
 */
static void checkNode(TreeNode_st * pNode)
{   
    TreeNode_st* pChild1;
    TreeNode_st* pChild2;

    switch(pNode->nodeType)
    {
        case NODE_OPERATOR:
            checkOperator(pNode);
            break;

        case NODE_IDENTIFIER:
            if(pNode->pSymbol != NULL)
            {
                if(pNode->childNumber > 0)
                {
                    pChild1 = &pNode->pChilds[0];
                    if(pChild1->nodeType == NODE_TYPE_CAST)
                    {
                        pNode->nodeVarType = pChild1->nodeVarType;  
                    }
                }
                else
                {
                    pNode->nodeVarType = pNode->pSymbol->type; 
                }
            }
            break;


        case NODE_FUNCTION_CALL:
            if(pNode->pSymbol != NULL)
            {
                if(!pNode->pSymbol->symbolContent_u.SymbolFunction_s.isImplemented)      //check if is not implemented
                {
                    semanticError(pNode, "Implicit declaration of function\n");
                }
                else if(pNode->childNumber > 0)                                     //check is has arguments 
                {
                    parameter_st* pParam = pNode->pSymbol->symbolContent_u.SymbolFunction_s.parameters;

                    pChild1 = &pNode->pChilds[0];

                    for(int i = 0; i < pNode->pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
                    {   
                        if(pParam[i].isPointer)
                        {
                            pointerAssignCheck(pNode, pParam[i].varType, pChild1);
                        }

                        if(!(pParam[i].isPointer && pChild1->nodeVarType == TYPE_STRING && pParam[i].varType == TYPE_CHAR))
                        {
                            if(pChild1->nodeVarType != pParam[i].varType)
                            {
                                semanticError(pNode, "Incompatible type for argument\n");
                            }
                        }

                        pChild1 = pChild1->pSibling;
                    }
                }

                pNode->nodeVarType = pNode->pSymbol->type;
            }           
            break;  

        case NODE_STRING:
            pNode->nodeVarType = TYPE_STRING;
            break;

        case NODE_INTEGER:
            pNode->nodeVarType = TYPE_INT;
            break;

        case NODE_FLOAT:
            pNode->nodeVarType = TYPE_FLOAT;
            break;


        // Valid examples:  array[int_var]      array[short_var]
        case NODE_ARRAY_INDEX:
            if(pNode->pSymbol != NULL)
            {
                if ((pNode->pChilds->nodeVarType != TYPE_INT) && (pNode->pChilds->nodeVarType != TYPE_LONG) && (pNode->pChilds->nodeVarType != TYPE_SHORT))
                {
                    semanticError(pNode, "Array index must be an INT, LONG or SHORT!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
                else
                {
                    pNode->nodeVarType = pNode->pSymbol->type;
                }
            }
            break;


        // Valid examples:  pointer ++      -- double_var
        case NODE_POST_DEC:
        case NODE_PRE_DEC:
        case NODE_POST_INC:
        case NODE_PRE_INC:
            if(pNode->pSymbol != NULL)
            {
                if((pNode->pSymbol->symbolType == SYMBOL_VARIABLE))
                {
                    if(pNode->pSymbol->modifier == MOD_CONST)
                    {
                        semanticError(pNode, "Assignment of read-only variable!\n");
                    }
                    else
                    {
                        pNode->nodeVarType = pNode->pSymbol->type;
                    }
                }
                else if(pNode->pSymbol->symbolType == SYMBOL_POINTER)
                {   
                    pNode->nodeVarType = pNode->pSymbol->type;
                }
                else
                {
                    semanticError(pNode, "Operand type not supported!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
            }  
            break;

        // Valid examples:  case 2      case char_var
        case NODE_CASE:
            if(pNode->childNumber > 0)
            {
                if((pNode->pChilds[0].nodeVarType != TYPE_INT) && (pNode->pChilds[0].nodeVarType != TYPE_CHAR))
                {
                    printf("CASE TYPE: %d\n",pNode->pChilds[0].nodeVarType);
                    semanticError(pNode, "Case condition type must be a INT or CHAR!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
            }
            break;

        case NODE_DO_WHILE:
        case NODE_SWITCH:
        case NODE_WHILE:
        case NODE_IF:
            if((pNode->pChilds[0].nodeVarType == TYPE_STRING) || (pNode->pChilds[0].nodeVarType == TYPE_VOID))
            {
                semanticError(pNode, "Condition type can't be a STRING or VOID!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            break;


        // Valid examples:  (double_var) ? float_var : float_var
        case NODE_TERNARY:
            if((pNode->pChilds[0].nodeVarType == TYPE_STRING) || (pNode->pChilds[0].nodeVarType == TYPE_VOID))
            {
                semanticError(pNode, "Condition type can't be a STRING or VOID!\n");
                pNode->nodeVarType = TYPE_VOID;
            }
            else
            {
                pChild1 = &pNode->pChilds[1];
                pChild2 = &pNode->pChilds[2];
                int varType1 = pChild1->nodeVarType;
                int varType2 = pChild2->nodeVarType;

                if ((varType1 == TYPE_STRING || varType1 == TYPE_VOID ) ||
                    (varType2 == TYPE_STRING || varType2 == TYPE_VOID )) 
                {
                    semanticError(pNode, "Invalid operands types!\n");
                }
                else if(varType1 != varType2)
                {
                    semanticError(pNode, "Operands types don't match!\n");
                }
                else
                {
                    pNode->nodeVarType = varType1;
                }
            }
            break;    


        case NODE_RETURN:
            if(pNode->pSymbol != NULL && pNode->childNumber > 0)
            {
                pChild1 = &pNode->pChilds[0];

                int varType = pNode->pSymbol->type;

                if(pChild1->nodeVarType == varType)
                {
                    pNode->nodeVarType = varType;
                }
                else
                {
                    semanticError(pNode, "Incompatible return type!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
            } 
            break;   


        // Valid_examples:  &pointer      &array
        case NODE_REFERENCE:
            TreeNode_st* pNodeAux;

            pNodeAux = (pNode->childNumber != 0) ? pNodeAux = &pNode->pChilds[0] : pNode;

            if(pNodeAux->pSymbol != NULL)
            {
                if(pNodeAux->pSymbol->symbolType == SYMBOL_ARRAY || pNodeAux->pSymbol->symbolType == SYMBOL_VARIABLE)
                {
                    pNode->nodeVarType = pNode->pSymbol->type;
                }
                else
                {
                    semanticError(pNode, "Invalid use of '&'!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
            }           
            break;


        // Valid examples:  *pointer
        case NODE_POINTER_CONTENT:
            if(pNode->pSymbol != NULL)
            {
                if(pNode->pSymbol->symbolType == SYMBOL_POINTER)
                {
                    pNode->nodeVarType = pNode->pSymbol->type;
                }
                else
                {
                    semanticError(pNode, "Can't reference a non pointer variable!\n");
                    pNode->nodeVarType = TYPE_VOID;
                }
            }            
            break; 

        case NODE_TYPE_CAST:
            pChild1 = &pNode->pChilds[0];

             if (pChild1->nodeType == NODE_POINTER)
            {
                pChild1 = &pChild1->pChilds[0];
            }

            pNode->nodeVarType = pChild1->nodeData.dVal;
            break; 
    }
}




/*****************************************************************************************
 ****************************       BUILD SYMBOLS TABLES       ***************************
******************************************************************************************/

/**
 * @brief goes through all the siblings in the preamble and saves qualifiers

 * @param pNode current node
 * @param type 
 * @param sign 
 * @param modifier
 * @param visibility
 */
static int setMemoryLocation(int* varLocation, VarType_et varType, int multiplier)
{
    int* currentLocation;

    if(pCurrentScope == pGlobalSymTable)
    {
        currentLocation = &globalMemoryLocation;
    }
    else
    {
        currentLocation = &localMemoryLocation;
    }

    *varLocation = *currentLocation; 

    switch(varType)
    {
        case TYPE_CHAR:
            *currentLocation += 1*multiplier;
            break;

        case TYPE_SHORT:
            *currentLocation += 1*multiplier;
            break;    
  
        case TYPE_LONG:
        case TYPE_INT:
        case TYPE_FLOAT:
            *currentLocation += 1*multiplier;
            break;

        case TYPE_DOUBLE:
            *currentLocation += 1*multiplier;
            break;   

        case TYPE_LONG_DOUBLE:
            *currentLocation += 1*multiplier;
            break; 

        default:
            LOG_DEBUG("Invalid variable type");
            break;                                 
    }
}


/**
 * @brief goes through all the siblings in the preamble and saves qualifiers

 * @param pNode current node
 * @param type 
 * @param sign 
 * @param modifier
 * @param visibility
 */
static void setVariblesType(TreeNode_st* pNode, VarType_et* type, SignQualifier_et* sign, ModQualifier_et* modifier, VisQualifier_et* visibility)
{
    TreeNode_st* pNodeTemp = pNode;
    *sign = 0;
    *modifier = 0;
    *visibility = 0;

    while (pNodeTemp != NULL)
    {
        switch(pNodeTemp->nodeType)
        {
            case NODE_TYPE:
                *type = pNodeTemp->nodeData.dVal;
                break;

            case NODE_SIGN:
                *sign = pNodeTemp->nodeData.dVal;
                break;

            case NODE_MODIFIER:
                *modifier = pNodeTemp->nodeData.dVal;
                break;

            case NODE_VISIBILITY:
                *visibility = pNodeTemp->nodeData.dVal;
                break;       

            default:
                LOG_DEBUG("Invalid node");
                break;
        }
        pNodeTemp = pNodeTemp->pSibling;
    }
}



/**
 * @brief generate the symbol tables, according to the current node 

 * @param pNode current node 
 */
static void buildSymbolTables(TreeNode_st* pNode)
{
    /*
    Flag to signal that you have entered a new scope (when '{') but not created the table
    Tables are only created if there are new declarations in the scope 
    */
    static bool tablePending = false; 
    
    /*
    Flag to signal that it is a function
    In functions, the tables are created when the signature appears to pass the parameters
    */
    static bool tableFunction = false;
    SymbolEntry_st* pNewSymbol;
    TreeNode_st* pNodeArgs;
    uint8_t parametersNum = 0;

    switch (pNode->nodeType)
    {
        // Variables declaration
        case NODE_VAR_DECLARATION:
            if(tablePending)
            {
                //Create a new symbol table if tablePending = 1
                SymbolTable_st* ppsymTable;
                createSymbolTable(&ppsymTable, pCurrentScope);
                pCurrentScope = ppsymTable;
                tablePending = false;
            }

            TreeNode_st* pNodeChild = pNode->pChilds;
            SymbolType_et symType;

            //If it's a pointer, the type is in the child of that node
            if(pNodeChild->nodeType == NODE_POINTER)
            {
                pNodeChild = pNodeChild->pChilds;
                symType = SYMBOL_POINTER;
            }
            else
            {
                symType = SYMBOL_VARIABLE;
            }


            if(pNodeChild->nodeData.dVal == TYPE_VOID)
            {
                semanticError(pNode, "Can not declare a 'void' variable!\n");
            }

            //inserts the new symbol into the table if it doesn't exist
            if( insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, symType) == SYMBOL_ADDED)
            { 
                setMemoryLocation(&pNewSymbol->symbolContent_u.memoryLocation, pNodeChild->nodeData.dVal, 1);

                setVariblesType(pNodeChild, 
                                &pNewSymbol->type,
                                &pNewSymbol->signal,
                                &pNewSymbol->modifier,
                                &pNewSymbol->visibility);

                pNewSymbol->scopeLocation = (pCurrentScope == pGlobalSymTable) ? GLOBAL_SCOPE : FUNCTION_SCOPE;
                pNode->pSymbol = pNewSymbol;
            }
            else
            {
                semanticError(pNode, "Symbol Redefinition!\n");
            }
            break;


        //Array declaration
        case NODE_ARRAY_DECLARATION:     
            if(tablePending)
            {
                //Create a new symbol table if tablePending = 1
                SymbolTable_st* ppsymTable;
                createSymbolTable(&ppsymTable, pCurrentScope);
                pCurrentScope = ppsymTable;
                tablePending = false;
            }

            TreeNode_st* pNodePreamble = &pNode->pChilds[0];

            if(pNodePreamble->nodeData.dVal == TYPE_VOID)
            {
                semanticError(pNode, "Can not declare a 'void' array!\n");
            }
            //inserts the new symbol into the table if it doesn't exist
            else if( insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_ARRAY) == SYMBOL_ADDED)
            { 
                TreeNode_st* pNodeSize = &pNode->pChilds[1];

                setVariblesType(pNodePreamble, 
                                &pNewSymbol->type,
                                &pNewSymbol->signal,
                                &pNewSymbol->modifier,
                                &pNewSymbol->visibility);


                int arraySize = pNodeSize->nodeData.dVal;
                pNewSymbol->symbolContent_u.SymbolArray_s.arraySize = arraySize;    
                setMemoryLocation(&pNewSymbol->symbolContent_u.SymbolArray_s.memoryLocation, pNodePreamble->nodeData.dVal, arraySize);           
            
                pNode->pSymbol = pNewSymbol;
                pNode->pSymbol->scopeLocation = (pCurrentScope == pGlobalSymTable) ? GLOBAL_SCOPE : FUNCTION_SCOPE;   
            }
            else
            {
                semanticError(pNode, "Symbol Redefinition!\n");
            }
            break;


        //Function prototip and implementation
        case NODE_FUNCTION:
            localMemoryLocation = 0;

            //check if exist arguments
            if(pNode->pChilds[1].nodeType != NODE_NULL)
                pNodeArgs = &pNode->pChilds[1];
            else    
                pNodeArgs = NULL; 

            //inserts the new symbol into the table if it doesn't exist
            if(insertSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_FUNCTION) == SYMBOL_ADDED)
            {
                TreeNode_st* pNodePreamble = &pNode->pChilds[0];


                //sets the return type
                setVariblesType(pNodePreamble, 
                                &pNewSymbol->type,
                                &pNewSymbol->signal,
                                &pNewSymbol->modifier,
                                &pNewSymbol->visibility); 


                //adds the function arguments 
                while (pNodeArgs != NULL)
                {
                    parameter_st pParam;
                    VisQualifier_et notUsed;
                    TreeNode_st* pNodeAux;

                    pParam.name = pNodeArgs->nodeData.sVal;

                    if(pNodeArgs->pChilds->nodeType == NODE_POINTER)
                    {
                        pNodeAux = pNodeArgs->pChilds->pChilds;
                        pParam.isPointer = true;
                    }
                    else
                    {
                        pNodeAux = pNodeArgs->pChilds;
                        pParam.isPointer = false;
                    }

                    setVariblesType(pNodeAux, 
                                    &pParam.varType,
                                    &pParam.varSign,
                                    &pParam.varMod,
                                    &notUsed);

                    addFunctionParams(pNewSymbol, &pParam);

                    pNodeArgs = pNodeArgs->pSibling;

                    parametersNum++;
                }

                pNode->pSymbol = pNewSymbol;
            }
            else 
            {
                 //count the function arguments 
                while (pNodeArgs != NULL)
                {
                    pNodeArgs = pNodeArgs->pSibling;

                    parametersNum++;
                }
            }

            if(pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented == true)
            {
                semanticError(pNode, "Function redefinition!\n");
            }
            else
            {
                //if has three children you have the implementation of the function
                if(pNode->childNumber > 2)
                {
                    pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented = true;

                    //creates a new symbol table 
                    SymbolTable_st* ppsymTable;
                    createSymbolTable(&ppsymTable, pCurrentScope);
                    pCurrentScope = ppsymTable;
                    tableFunction = true;

                    //puts all parameters in the new scope
                    if(pNode->pChilds[1].nodeType != NODE_NULL)
                    {
                        parameter_st* paramList = pNewSymbol->symbolContent_u.SymbolFunction_s.parameters;
                        TreeNode_st* pArgs = pNode->pChilds + 1;

                        for(int i = 0; i < pNewSymbol->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
                        {
                            SymbolEntry_st* pParamSym;
                            insertSymbol(pCurrentScope, &pParamSym, paramList[i].name, (paramList[i].isPointer) ? SYMBOL_POINTER : SYMBOL_VARIABLE);
                            pParamSym->type = paramList[i].varType;
                            pParamSym->signal = paramList[i].varSign;
                            pParamSym->symbolContent_u.memoryLocation = NO_MEMORY;

                            //Add symbol point to parameter
                            pParamSym->scopeLocation = ARGUMENT_SCOPE;
                            pParamSym->paramPosition = i;
                            pArgs->pSymbol = pParamSym;
                            pArgs = pArgs->pSibling;
                        }
                    }

                    pNode->pSymbol = pNewSymbol;
                }
                else
                {
                    pNewSymbol->symbolContent_u.SymbolFunction_s.isImplemented = false;
                }

                pCurrentScope->parameterNumber = parametersNum;
            }
            break;

        //pointer content (*p), go to and identifier
        case NODE_POINTER_CONTENT:
        case NODE_IDENTIFIER:
            //check if the symbol already exists
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
                semanticError(pNode, "Symbol Not Defined!\n");
            else    
                pNode->pSymbol = pNewSymbol;    

            break;

        //variable reference (&a)
        case NODE_REFERENCE:
            //if it has no children, the name of the token is in the node data

            TreeNode_st * auxNode;
            auxNode = (pNode->childNumber == 0) ? pNode : &pNode->pChilds[0];
            
            if(fetchSymbol(pCurrentScope, &pNewSymbol, auxNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
                semanticError(pNode, "Symbol Not Defined!\n");
            else
                pNode->pSymbol = pNewSymbol;    

            break;    
        

        //label (init:)
        case NODE_LABEL:
            //inserts the label into the table if it doesn't exist
            if(insertSymbol(pGlobalSymTable, &pNewSymbol, pNode->nodeData.sVal, SYMBOL_LABEL) == SYMBOL_ERROR) 
                semanticError(pNode, "Label Redefinition!\n");
            else
                pNode->pSymbol = pNewSymbol;

            break;


        case NODE_GOTO:
            //check if the symbol already exists
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_NOT_FOUND)
                semanticError(pNode, "Symbol Not Defined!\n");
            else    
                pNode->pSymbol = pNewSymbol;  

            break;   



        case NODE_RETURN:
            if(fetchSymbol(pGlobalSymTable, &pNewSymbol, pNode->nodeData.sVal, true) == SYMBOL_NOT_FOUND)
                semanticError(pNode, "Symbol not found!\n");
            else
                pNode->pSymbol = pNewSymbol;     

            break;    


        //Array value (array[x])
        case NODE_ARRAY_INDEX:
            //check if the token exists
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_FOUND)
            {
                TreeNode_st* pNodeIndex = &pNode->pChilds[0];
                uint32_t arrSize = pNewSymbol->symbolContent_u.SymbolArray_s.arraySize;
                
                if(pNodeIndex->nodeType != NODE_IDENTIFIER)
                {
                    //checks if the index excced the array size
                    if (pNodeIndex->nodeData.dVal >= arrSize)
                    {
                        semanticError(pNode, "Index out of range!\n");
                    }
                    else if(pNodeIndex->nodeData.dVal < 0)
                    {
                        semanticError(pNode, "Invalid array index: can not be a negative number!\n");
                    }
                }

                pNode->pSymbol = pNewSymbol;
            }
            else
            {
                semanticError(pNode, "Symbol Not Defined!\n");
            }
            break;       


        //function call
        case NODE_FUNCTION_CALL:
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) == SYMBOL_FOUND)
            {
                TreeNode_st* pNodeParameters  = &pNode->pChilds[0];
                int functionParameterNumber = pNewSymbol->symbolContent_u.SymbolFunction_s.parameterNumber;
                int parameterCount = 0;

                //checks if is passed the correct arguments number
                while(pNodeParameters != NULL)
                {
                    parameterCount++;
                    pNodeParameters = pNodeParameters->pSibling;
                }

                if(parameterCount != functionParameterNumber)
                {
                    char errorMessage[100];
                    snprintf(errorMessage, sizeof(errorMessage), "%s arguments for function call, expected %d, have %d \n",
                                                 (parameterCount > functionParameterNumber ? "Too many" : "Too few"),
                                                 functionParameterNumber, parameterCount);
                    semanticError(pNode, errorMessage);
                }

                pNode->pSymbol = pNewSymbol;
            }
            else
            {
                semanticError(pNode, "Function Not Defined!\n");
            }
            break;             


        case NODE_START_SCOPE:
            if(!tableFunction)
                tablePending = true;
            else 
                tableFunction = false;    
            break;


        case NODE_END_SCOPE:
            if(!tablePending)
                pCurrentScope = pCurrentScope->enclosingScope;
            else    
                tablePending = false;
            break;            


        case NODE_POST_DEC:
        case NODE_PRE_DEC:
        case NODE_POST_INC:
        case NODE_PRE_INC:
            if(fetchSymbol(pCurrentScope, &pNewSymbol, pNode->nodeData.sVal, false) != SYMBOL_FOUND)
                semanticError(pNode, "Symbol Not Defined!\n");
            else
                pNode->pSymbol = pNewSymbol;

            break;

        default:
            break;
    }


    pNode->pScope = pCurrentScope;
}