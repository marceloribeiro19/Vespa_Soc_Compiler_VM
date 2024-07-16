#ifndef _PARSER_H_
#define _PARSER_H_

#include "../Util/Globals.h"
#include "../Util/TreeNode.h"

int yyerror(char* pStr);
int executeParser(TreeNode_st** ppTreeRoot);

#endif