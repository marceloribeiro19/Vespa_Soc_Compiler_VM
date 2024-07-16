#ifndef _UTIL_H_
#define _UTIL_H_

#include "Globals.h"
#include "TreeNode.h"

static const const char *nodeTypeStrings[] = {
    "NODE_SIGN",
    "NODE_MISC",
    "NODE_VISIBILITY",
    "NODE_MODIFIER",
    "NODE_TYPE",
    "NODE_OPERATOR",
    "NODE_TERNARY",
    "NODE_IDENTIFIER",
    "NODE_STRING",
    "NODE_INTEGER",
    "NODE_FLOAT",
    "NODE_STRUCT",
    "NODE_IF",
    "NODE_WHILE",
    "NODE_DO_WHILE",
    "NODE_RETURN",
    "NODE_CONTINUE",
    "NODE_BREAK",
    "NODE_GOTO",
    "NODE_LABEL",
    "NODE_SWITCH",
    "NODE_CASE",
    "NODE_DEFAULT",
    "NODE_REFERENCE",
    "NODE_POINTER",
    "NODE_POINTER_CONTENT",
    "NODE_TYPE_CAST",
    "NODE_POST_DEC",
    "NODE_PRE_DEC",
    "NODE_POST_INC",
    "NODE_PRE_INC",
    "NODE_VAR_DECLARATION",
    "NODE_ARRAY_DECLARATION",
    "NODE_ARRAY_INDEX",
    "NODE_FUNCTION",
    "NODE_FUNCTION_CALL",
    "NODE_PARAMETER",
    "NODE_NULL",
    "NODE_END_SCOPE",
    "NODE_START_SCOPE"
};


static const char *OperatorStrings[] = {
    "+ ",      // 0
    "- ",      // 1
    ">> ",     // 2
    "<< ",     // 3
    "* ",      // 4
    "/ ",      // 5
    "%% ",     // 6
    "> ",      // 7
    "<= ",     // 8
    ">= ",     // 9
    "< ",      // 10
    "== ",     // 11
    "!= ",     // 12
    "&& ",     // 13
    "|| ",     // 14
    "! ",      // 15
    "& ",      // 16
    "~ ",      // 17
    "| ",      // 18
    "^ ",      // 19
    "= ",      // 20
    "+= ",     // 21
    "-= ",     // 22
    "%%= ",    // 23
    "<<= ",    // 24
    ">>= ",    // 25
    "&= ",     // 26
    "|= ",     // 27
    "^= ",     // 28
    "*= ",     // 29
    "/= ",     // 30
    "sizeof",   // 31
    "negative",
    "not_defined"
};

static const char *VarTypeStrings[] = {
    "char ",
    "short ",
    "int ",
    "long ",
    "float ",
    "double ",
    "long double ",
    "void "
};

static const char *SignQualifierStrings[] = {
    "signed ",
    "unsigned "
};

static const char *ModQualifierStrings[] = {
    "",
    "const ",
    "volatile "
};

static const char *VisQualifierStrings[] = {
    "",
    "static ",
    "extern "
};

static const char *MiscDataStrings[] = {
    "",
    "register "
};

static const char *MiscTokensStrings[] = {
    ")",
    "(",
    "]",
    "["
};

static const char *ScopeLocationStrings[] = {
    "Global",
    "Argument",
    "Function"
};


int NodeCreate(TreeNode_st** ppNewNode, NodeType_et nodeType);

int NodeAddChild(TreeNode_st* pParent, TreeNode_st* pChild);
int NodeAddChildCopy(TreeNode_st* pParent, TreeNode_st *pChild);
int NodeAddNewChild(TreeNode_st* pParent, TreeNode_st** ppNewChild, NodeType_et nodeType);

int StringCreateAndCopy(char** ppDest, char* pSrc, size_t strLen);

static void Indentation(void);

void PrintNode(TreeNode_st* pNode);



//Code generation utils

typedef struct 
{
  bool is_increment;
  TreeNode_st* treeNode;
}list_item_st;

typedef struct 
{
  uint8_t size;
  list_item_st* savedItem;
} postinc_list_st;


int PostIncListInit();

int PostIncListInsert(postinc_list_st* address_list, bool is_increment, TreeNode_st* TreeNode);

int PostIncListDelete(postinc_list_st* address_list);

void PostIncListDestroy(postinc_list_st* address_list);




















































































































































































































void endCompiling(void);


#endif