#include <errno.h>
#include <stdio.h>
#include "../Util/Logger.h"
#include "../Util/Util.h"
#include "../main.h"
#include "../SemanticAnalyzer/SymbolTable.h"

#define NOT_APPLICABLE  (0xFFFFFFFF)

static int tablesNumber = 0;
static SymbolTable_st** allSymbolsTables;  //all created


/// @brief functio
/// @param key (symbol name)
/// @return hash value// Hash function
static int hash(const char *key)
{
    int hashValue = 0;
    int i = 0;
    while (key[i] != '\0')
        hashValue = ((hashValue << 4) + key[i++]) % HASH_TABLE_SIZE;

    return hashValue;
}


/// @brief  Function to create a new symbol table
///         Note: Global scope recommended to receive enclosingScope = NULL
/// @param ppSymTable
/// @param enclosingScope
/// @return
int createSymbolTable(SymbolTable_st** ppSymTable, SymbolTable_st* enclosingScope)
{
    SymbolTable_st* pSymTable;

    if (!ppSymTable)
        return -EINVAL;

    *ppSymTable = (SymbolTable_st*) calloc(1, sizeof(SymbolTable_st));

    if (!(*ppSymTable))
    {
        LOG_DEBUG("Failed to allocate memory for new symbol table!\n");
        return -ENOMEM;
    }

    pSymTable = (SymbolTable_st*) (*(ppSymTable));

    pSymTable->enclosingScope = enclosingScope;

    // Initialize hash table
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        pSymTable->table[i] = NULL;      // Initialize each entry to NULL
    }

    allSymbolsTables = reallocarray(allSymbolsTables, tablesNumber + 1, sizeof(SymbolTable_st*));
    if (!allSymbolsTables)
    {
        LOG_DEBUG("Failed to allocate memory while trying to add a table pointer\n");
        return -ENOMEM;
    }

    allSymbolsTables[tablesNumber++] = (*ppSymTable);

    return 0;
}


/// @brief Function to get symbol from symbol table
/// @param pSymTable
/// @param ppSymbol
/// @param name
/// @param onlyCurrentScope
/// @return error handling or symbol presence flag
int fetchSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymbol, char* name, int onlyCurrentScope)
{
    if (!pSymTable || !ppSymbol)
        return -EINVAL;

    int index = hash(name);  // Assuming you have a separate hash function

    // Traverse the linked list at the hash index
    SymbolEntry_st* symIterator = pSymTable->table[index];

    while (symIterator != NULL)
    {
        // Ensure symIterator->name is valid before comparison (avoid null pointer dereference)
        if (symIterator->name != NULL && strcmp(symIterator->name, name) == 0)
        {
            (*ppSymbol) = symIterator;
            return SYMBOL_FOUND;
        }
        symIterator = symIterator->next;
    }

    // Symbol not found in the current scope, check enclosing scope (if it exists)
    if (pSymTable->enclosingScope != NULL && !onlyCurrentScope)
    {
        return fetchSymbol(pSymTable->enclosingScope, ppSymbol, name, onlyCurrentScope);
    }

    return SYMBOL_NOT_FOUND;                    // Symbol not found
}


/// @brief Function to insert a symbol into the symbol table
/// @param pSymTable
/// @param ppSymEntry
/// @param symName
/// @param symType
/// @return
int insertSymbol(SymbolTable_st* pSymTable, SymbolEntry_st** ppSymEntry, char *symName, SymbolType_et symType)
{
    if (!pSymTable || !ppSymEntry)
        return -EINVAL;

    int index = hash(symName);


    SymbolEntry_st* pEntryAux;

    // checks if the symbol already exists in the current scope and adds it if not
    if( fetchSymbol(pSymTable, &pEntryAux, symName, true) == SYMBOL_NOT_FOUND)
    {
        SymbolEntry_st* pNewSymbol;
        pNewSymbol = (SymbolEntry_st*) calloc(1, sizeof(SymbolEntry_st));

        if (!pNewSymbol)
        {
            LOG_DEBUG("Failed to allocate memory for new symbol!\n");
            return -ENOMEM;
        }

        pNewSymbol->name = symName;
        pNewSymbol->symbolType = symType;

        pEntryAux = pSymTable->table[index];
        pSymTable->table[index] = pNewSymbol;
        pNewSymbol->next = pEntryAux;

        *ppSymEntry = pNewSymbol;

        return SYMBOL_ADDED;
    }

    *ppSymEntry = pEntryAux;

    return SYMBOL_ERROR;
}


/// @brief Function to free the memory allocated for the whole Symbol Table
/// @param symTable
void freeSymbolTable()
{
    SymbolTable_st* curTable;
    SymbolEntry_st* curSymbol;
    SymbolEntry_st* tempSymbol;

    for(int j = 0; j < tablesNumber; j++)
    {
        curTable = allSymbolsTables[j];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            curSymbol = curTable->table[i];
            while (curSymbol != NULL)
            {
                tempSymbol = curSymbol;
                curSymbol = curSymbol->next;

                if (tempSymbol->symbolType == SYMBOL_FUNCTION)
                {
                    free(tempSymbol->symbolContent_u.SymbolFunction_s.parameters);
                }
                free(tempSymbol->name);
                free(tempSymbol);
            }
            free(curSymbol);
        }
        free(curTable);
    }

    endCompiling();
}


/// @brief Prints a symbol
/// @param symbolType
/// @param name
/// @param varType
/// @param varSign
/// @param varMod
/// @param varVis
/// @param memoryLocation
/// @param arraySize
/// @param isImplemented
/// @param parameterNumber
static void printSymbol(char* symbolType, const char *name, int varType, int varSign, int varMod,
                        int varVis, int memoryLocation, uint32_t arraySize, int isImplemented,
                        int parameterNumber, int scopeLocation, int isPassedByRegister)
{
    printf("| %10s | %20s | %11s | %10s | %10s | %10s |",
           symbolType,
           name,
           varType != NOT_APPLICABLE            ? VarTypeStrings[varType]       : "n/a",
           varSign != NOT_APPLICABLE            ? SignQualifierStrings[varSign] : "n/a",
           varMod  != NOT_APPLICABLE            ? ModQualifierStrings[varMod]   : "n/a",
           varVis  != NOT_APPLICABLE            ? VisQualifierStrings[varVis]   : "n/a"
    );

    if(memoryLocation != NOT_APPLICABLE)
        printf(" %10d |", memoryLocation);
    else
        printf(" %10s |", "n/a");

    if(arraySize != NOT_APPLICABLE)
        printf(" %10u |", arraySize);
    else
        printf(" %10s |", "n/a");

    printf(" %10s |", isImplemented == -1 ? "n/a" : isImplemented ? "True" : "False");

    if(parameterNumber != NOT_APPLICABLE)
        printf(" %10d |", parameterNumber);
    else
        printf(" %10s |", "n/a");

    if(scopeLocation != NOT_APPLICABLE)
        printf(" %15s |", ScopeLocationStrings[scopeLocation]);
    else
        printf(" %15s |", "n/a");

    if(isPassedByRegister != NOT_APPLICABLE)
        printf(" %15d |", isPassedByRegister);
    else
        printf(" %15s |", "n/a");

    printf("\n");   // Newline for next symbol

}


/// @brief prints all symbols tables
void printSymbolTables()
{
    static uint8_t counter = 0;
    SymbolEntry_st* temp;
    SymbolTable_st* CurrTable;

    for(int j = 0; j < tablesNumber; j++)
    {
        CurrTable = allSymbolsTables[j];

        printf("-------------------------------------------------------------------------------- SYMBOL TABLE %u ----------------------------------------------------------------------------------\n", counter++);

        printf("\033[38;2;255;197;173m");
        printf("| %10s | %20s | %11s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %15s | %15s|\n", "SYMBOL", "NAME",
               "TYPE", "SIGN", "MODIFIER", "VISIBILITY", "MEM_LOC", "ARRAY SIZE", "IS_IMPL", "PARAM_NUM", "SCOPE LOCATION", "IS_PASSED_BY_REG");
        printf("\033[1;0m");

        for(int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            temp = CurrTable->table[i];

            while(temp != NULL)
            {
                switch (temp->symbolType)
                {
                    //prints a symbol of avariable
                    case SYMBOL_VARIABLE:
                        printSymbol("VARIABLE",
                                    temp->name,
                                    temp->type,
                                    temp->signal,
                                    temp->modifier,
                                    temp->visibility,
                                    temp->symbolContent_u.memoryLocation,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    temp->scopeLocation,
                                    NOT_APPLICABLE
                        );
                        break;

                        // Prints a symbol of a function
                    case SYMBOL_FUNCTION:
                        printSymbol("FUNCTION",
                                    temp->name,
                                    temp->type,
                                    temp->signal,
                                    temp->modifier,
                                    temp->visibility,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    temp->symbolContent_u.SymbolFunction_s.isImplemented,
                                    temp->symbolContent_u.SymbolFunction_s.parameterNumber,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE
                        );

                        parameter_st* parameterAux;
                        int paramNum = temp->symbolContent_u.SymbolFunction_s.parameterNumber;
                        if(temp->symbolContent_u.SymbolFunction_s.parameterNumber != 0)
                        {
                            parameterAux = temp->symbolContent_u.SymbolFunction_s.parameters;
                            //prints all function parameters
                            printf("\tPARAMETERS: ");
                            for(int k=0; k<paramNum; k++)
                            {
                                if(k!=0)
                                    printf("\t            ");

                                printf("%15s | %11s | %10s | %10s | %10s\n",
                                        /* Name */     parameterAux[k].name,
                                        /* Type */     VarTypeStrings[parameterAux[k].varType],
                                        /* Sign */     SignQualifierStrings[parameterAux[k].varSign],
                                        /* Modifier */     ModQualifierStrings[parameterAux[k].varMod],
                                        /* Is Pointer */     parameterAux[k].isPointer? "Pointer: yes" : "Pointer: no"
                                );
                            }
                            printf("\n");
                        }
                        break;

                        // Prints all symbols of a label
                    case SYMBOL_LABEL:
                        printSymbol("LABEL",
                                    temp->name,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE
                        );
                        break;

                        // Prints a symbol of a pointer
                    case SYMBOL_POINTER:
                        printSymbol("POINTER",
                                    temp->name,
                                    temp->type,
                                    temp->signal,
                                    temp->modifier,
                                    temp->visibility,
                                    temp->symbolContent_u.memoryLocation,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE
                        );
                        break;

                        // Prints a symbol of an array
                    case SYMBOL_ARRAY:
                        printSymbol("ARRAY",
                                    temp->name,
                                    temp->type,
                                    temp->signal,
                                    temp->modifier,
                                    temp->visibility,
                                    temp->symbolContent_u.SymbolArray_s.memoryLocation,
                                    temp->symbolContent_u.SymbolArray_s.arraySize,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE,
                                    NOT_APPLICABLE
                        );
                        break;

                    default:
                        break;
                }

                temp = temp->next;
            }
        }
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
    }
}


/// @brief adds a new parameter to the function parameters list
/// @param pSymbol   -function symbol
/// @param pNewParam -parameter to add 
/// @return error handling
int addFunctionParams(SymbolEntry_st* pSymbol, struct parameter* pNewParam)
{
    if (!pSymbol)
        return -EINVAL;

    parameter_st* pParamList;

    //rellocates space for the new parameter
    pParamList = reallocarray(pSymbol->symbolContent_u.SymbolFunction_s.parameters, pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber + 1, sizeof(parameter_st));
    if (!pParamList)
    {
        LOG_DEBUG("Failed to allocate memory while trying to add a new parameter\n");
        return -ENOMEM;
    }

    //copies the parameter data to the allocated space
    memcpy(&pParamList[pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber++], pNewParam, sizeof(parameter_st));
    pSymbol->symbolContent_u.SymbolFunction_s.parameters = pParamList;

    return 0;
}