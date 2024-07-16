#ifndef TRAVERSE_H
#define TRAVERSE_H

#include "../Util/Globals.h"
#include "../Util/TreeNode.h"

#include "../SemanticAnalyzer/SymbolTable.h"


#define SEMANTIC_OK     0
#define SEMANTIC_ERROR  -1

int executeSemanticAnalisys(TreeNode_st* pTreeRoot, SymbolTable_st** ppGlobalTable);

#endif

void traverse (TreeNode_st* pNode, void (*preOrder) (TreeNode_st* ), void (*postOrder) (TreeNode_st* ));
void nullProc(TreeNode_st * st);

/*
1ª travessia - preorder
    - ADICIONAR SÍMBOLOS ÀS TABELAS
        - NODE_VAR_DECLARATION: colocar na tabela de simbolos do scope
        - NODE_ARRAY_DECLARATION
        - Verificar se essa variável já existe no scope 
        - função e var nomes diferentes

        - NODE_FUNCTION:
            - Colocar o nome da função no scope onde está
            - Criar um novo scope
            - Ir aos filhos para ir buscar a arg_list


    - VERIFICAR SE UMA VARIÁVEL FOI DEFINIDA
        - NODE_IDENTIFIER
        - NODE_ARRAY_INDEX
        - NODE_POINTER_CONTENT
        - NODE_REFERENCE
        - NODE_GOTO
        - NODE_FUNCTION_CALL
        - Se NODE_FUNCTION não ir aos filhos pq os filhos tb têm NODE_ID,
        mas pertence às vairá Colocar o nome da função no scope onde estáveis a verificar


2ª travessia - postorder
    - Type check 
        - Operações 
        - Const não pode ser alterado
        - Verificar parametros da chamada de funções
            - tipos de parametros
            - numero de parametros
            - tipo de retorno
        - indice de um array
        - if não pode ter strings
*/