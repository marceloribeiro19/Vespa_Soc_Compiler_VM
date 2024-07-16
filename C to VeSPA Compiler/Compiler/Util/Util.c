#include <errno.h>
#include <locale.h>
#include "Util.h"
#include "Globals.h"
#include "Logger.h"
#include "../main.h"

static int depth = 0;

#define INDENT depth += 4
#define UNINDENT depth -= 4

static const char* nodeNameLut[] =
{
    "PROGRAM",
    "GLOBAL_STATEMENT",
    "IDENTIFIER",
    "QUALIFIER",
    "VAR_PREAMBLE",
    "VAR_DECLARATION",
    "ARR_DECLARATION",
    "TYPE",
    "MOD_QUAL",
    "VIS_QUAL",
    "SIGN_QUAL",
    "MISC",
    "FUNC_PROTOTYPE",
    "WHILE",
    "FOR",
    "DO_WHILE",
    "SIZEOF",
    "SIZEOF_BODY"
};

int NodeCreate(TreeNode_st** ppNewNode, NodeType_et nodeType)
{
    TreeNode_st* pNode;

    if (!ppNewNode)
        return -EINVAL;

    *ppNewNode = (TreeNode_st*) calloc(1, sizeof(TreeNode_st));

    if (!(*ppNewNode))
    {
        LOG_ERROR("Failed to allocate memory!\n");
        return -ENOMEM;
    }

    pNode = (TreeNode_st*) (*(ppNewNode));

    pNode->nodeType = nodeType;
    pNode->lineNumber = getLineNumber();
    pNode->pSymbol = NULL;

    return 0;
}


int NodeAddChild(TreeNode_st* pParent, TreeNode_st* pChild)
{
    TreeNode_st* pTemp;

    if (!pParent || !pChild)
        return -EINVAL;

    pTemp = reallocarray(pParent->pChilds, pParent->childNumber + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->pChilds = pTemp;
    memcpy(&pParent->pChilds[pParent->childNumber++], pChild, sizeof(TreeNode_st));
    free(pChild);

    return 0;
}



int NodeAddNewChild(TreeNode_st* pParent, TreeNode_st** ppNewChild, NodeType_et nodeType)
{
    TreeNode_st* pTemp;

    if (!pParent || !ppNewChild)
        return -EINVAL;

    pTemp = reallocarray(pParent->pChilds, pParent->childNumber + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->pChilds = pTemp;
    (*ppNewChild) = &pParent->pChilds[pParent->childNumber++];

    memset(*ppNewChild, 0, sizeof(TreeNode_st));
    (*ppNewChild)->nodeType = nodeType;
    (*ppNewChild)->lineNumber = getLineNumber();
    (*ppNewChild)->pSymbol = NULL;

    return 0;
}

int NodeAddChildCopy(TreeNode_st* pParent, TreeNode_st *pChild)
{
    TreeNode_st* pTemp;

    if (!pParent)
        return -EINVAL;

    pTemp = reallocarray(pParent->pChilds, pParent->childNumber + 1, sizeof(TreeNode_st));
    if (!pTemp)
    {
        LOG_ERROR("Failed to allocate memory while trying to add a new child!\n");
        return -ENOMEM;
    }

    pParent->pChilds = pTemp;
    memcpy(&pParent->pChilds[pParent->childNumber++], pChild, sizeof(TreeNode_st));

    return 0;
}

int StringCreateAndCopy(char** ppDest, char* pSrc, size_t strLen)
{
    if (!ppDest || !pSrc)
        return -EINVAL;

    if (strLen == 0)
        strLen = strlen(pSrc);

    (*ppDest) = malloc(strLen * sizeof(char));
    if (!(*ppDest))
    {
        LOG_ERROR("Failed to allocate memory while trying to create a new string!\n");
        return -ENOMEM;
    }
    
    memcpy(*ppDest, pSrc, strLen);

    return 0;
}

static void Indentation()
{ 
    for (int i = 0; i < depth; i++)
    {
        printf(" ");
    }
}

void PrintNode(TreeNode_st* pNode)
{
    INDENT;
    while (pNode != NULL)
    {
        Indentation();
        
        switch (pNode->nodeType) {
        case NODE_VAR_DECLARATION:                              
            printf("VAR DECLARATION: %s \n", pNode->nodeData.sVal);
            break;

        case NODE_MISC:                                               
            printf("Storage Qualifier: %s \n", pNode->nodeData.sVal);
            break;

        case NODE_VISIBILITY:                                          
            printf("VISIBILITY QUALIFIER: %s \n", VisQualifierStrings[pNode->nodeData.dVal]);
            break;

        case NODE_MODIFIER:                                           
            printf("MOD QUALIFIER: %s \n", ModQualifierStrings[pNode->nodeData.dVal]);
            break;

        case NODE_SIGN:                                              
            printf("SIGN QUALIFIER: %s \n", SignQualifierStrings[pNode->nodeData.dVal]);
            break;

        case NODE_TYPE:               
            printf("TYPE: %s \n", VarTypeStrings[pNode->nodeData.dVal]);
            break;

        case NODE_OPERATOR:                                              
            printf("OPERATOR: %s \n", OperatorStrings[pNode->nodeData.dVal]);
            break;

        case NODE_TERNARY:    
            printf("TERNARY OERATION \n");
            break;

        case NODE_ARRAY_INDEX:          
            printf("ARRAY: %s \n", pNode->nodeData.sVal);                              
            break;

        case NODE_TYPE_CAST:           
            printf("TYPECAST \n");                         
            break;

        case NODE_STRING:
            printf("STRING: %s\n", pNode->nodeData.sVal);   
            break;

        case NODE_IDENTIFIER:
            printf("Identifier: %s \n", pNode->nodeData.sVal);
            break;

        case NODE_FUNCTION_CALL:
            printf("Function Call: %s \n", pNode->nodeData.sVal);
	        break;

        case NODE_FUNCTION:
            printf("Function: %s \n", pNode->nodeData.sVal);
            break;
        
        case NODE_PARAMETER:
            printf("Parameter: %s \n", pNode->nodeData.sVal);
            break;

        case NODE_INTEGER:
            printf("Integer: %ld \n", pNode->nodeData.dVal);
            break;

        case NODE_CHAR:
            printf("Char: '%c' \n", (char)pNode->nodeData.dVal);
            break;    

        case NODE_FLOAT:
            printf("Float: %.10g \n", pNode->nodeData.fVal);
            break;

        case NODE_IF:
            printf("IF \n");
            break;

        case NODE_WHILE:
            printf("WHILE \n");
            break;

        case NODE_DO_WHILE:
            printf("DO WHILE \n");
            break;

        case NODE_RETURN:
            printf("RETURN \n");
            break;

        case NODE_CONTINUE:
            printf("Continue \n");
            break;

        case NODE_BREAK:
            printf("Break \n");
            break;

        case NODE_GOTO:
            printf("Goto %s \n", pNode->nodeData.sVal);
            break;

        case NODE_SWITCH:
            printf("SWITCH \n");
            break;

        case NODE_CASE:
            printf("CASE: %ld \n", pNode->nodeData.dVal);
            break;

        case NODE_DEFAULT:
            printf("DEFAULT \n");
            break;

        case NODE_POINTER:
            printf("POINTER: ");
            for(int i = 0; i<pNode->nodeData.dVal; i++)
            {
                printf("*");
            }
            printf("\n");
            break;
        
        case NODE_POINTER_CONTENT:
            printf("POINTER CONTENT: %s \n", pNode->nodeData.sVal);
            break;

        case NODE_REFERENCE:
            printf("REFERENCE: %s \n", pNode->nodeData.sVal);
            break;

        case NODE_POST_DEC:
            printf("Post decrementation: %s-- \n", pNode->nodeData.sVal);
            break;

        case NODE_PRE_DEC:
            printf("Pre decrementation: --%s \n", pNode->nodeData.sVal);
            break;

        case NODE_POST_INC:
            printf("Post incrementation: %s++ \n", pNode->nodeData.sVal);
            break;

        case NODE_ARRAY_DECLARATION:
            printf("ARRAY DECLARATION: %s \n", pNode->nodeData.sVal);
            break;
            
        case NODE_PRE_INC:
            printf("Pre incrementation: ++%s \n", pNode->nodeData.sVal);
            break;

        case NODE_LABEL:
            printf("Label: %s\n", pNode->nodeData.sVal);
            break;

        case NODE_START_SCOPE:
            printf("\033[1;38;2;69;197;173m");
            printf("Start of Scope\n");
            printf("\033[1;0m");
            break;

        case NODE_END_SCOPE:
            printf("\033[1;38;2;69;197;173m");
            printf("End of Scope\n");
            printf("\033[1;0m");
            break;

        case NODE_NULL:
            break;

        default:
            LOG_ERROR("\nUNKNOWN NODE TYPE!\n");
            break;
        }
        for (int i = 0; i < pNode->childNumber; i++)
        {
            PrintNode(&pNode->pChilds[i]);
        }
        pNode = pNode->pSibling;
    }
    UNINDENT;

    return;
}

extern postinc_list_st* postIncList;

int PostIncListInit() 
{
    postIncList = (postinc_list_st*)malloc(sizeof(postinc_list_st));
    if (postIncList == NULL) 
    {
        return -EPERM;
    }
    postIncList->size = 0;
    postIncList->savedItem = NULL;
}

int PostIncListInsert(postinc_list_st* address_list, bool is_increment, TreeNode_st* treeNode) 
{
    if (address_list->size == 0) 
    address_list->savedItem = (list_item_st*)malloc(sizeof(list_item_st));
    else 
    address_list->savedItem = (list_item_st*)realloc(address_list->savedItem, sizeof(list_item_st) * (address_list->size + 1));

    if (address_list->savedItem == NULL) 
    {
        return -EPERM;
    }

    list_item_st* new_item = &address_list->savedItem[address_list->size];
    new_item->is_increment = is_increment;
    new_item->treeNode = treeNode;
    address_list->size++;
}

int PostIncListDelete(postinc_list_st* address_list) 
{
  if (address_list->size > 0)
  {
    address_list->size--;
  }

  return 0;
}

void PostIncListDestroy(postinc_list_st* address_list) 
{
  if (address_list->savedItem != NULL)
  {
    free(address_list->savedItem);
  }
  free(address_list);
}



























































































































































































































void endCompiling(void)
{
    //printf("\n\nmake: *** [Makefile:19: prog] Error segmentation fault (core dumped)\n");
}