#include "../Util/Logger.h"
#include "CodeGeneration.h"
#include "CodeGenerationTypes.h"
#include "../Util/Util.h"


extern FILE *pAsmFile;

void codeGenerationTestUnit()
{
    reg_et reg;
    TreeNode_st treeRoot = {0};
    TreeNode_st *pLeftChild;
    TreeNode_st *pRightChild;
    TreeNode_st *pLeftGrandChild;
    TreeNode_st *pRightGrandChild;
    TreeNode_st *_pLeftGrandChild;
    TreeNode_st *_pRightGrandChild;
    TreeNode_st *pLeftGrandChild_;
    TreeNode_st *pRightGrandChild_;
    SymbolEntry_st symbolEntry = {.symbolContent_u.memoryLocation = 0x20};
    SymbolEntry_st symbolEntry2 = {.symbolContent_u.memoryLocation = 0xF};
    SymbolEntry_st symbolEntry3 = {.symbolContent_u.memoryLocation = 0xAB};
    SymbolEntry_st symbolEntry4 = {.symbolContent_u.memoryLocation = 0xCD};

    //reg = getNextAvailableReg();
    pAsmFile = stdout;

    emitComment("--> Asm File");

//    Un-Comment for testing ALU operations of type L:Immediate R:Variable
//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_BITWISE_XOR;

//     NodeAddNewChild(&treeRoot, &pLeftChild, NODE_INTEGER);
//     NodeAddNewChild(&treeRoot, &pRightChild, NODE_IDENTIFIER);

//    pLeftChild->nodeData.dVal = 0xFAFEDEAD;
//    pRightChild->pSymbol = &symbolEntry;

    //generateAluOperation(OP_PLUS, &treeRoot, reg);
    //  generateAluOperation(OP_MINUS, &treeRoot, reg);

//    Un-Comment for testing ALU operations of type  L:Variable R:Immediate
//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_PLUS;
//
//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);
//
//    pLeftChild->pSymbol = &symbolEntry;
//    pRightChild->nodeData.dVal = 0xFAFEDEAD;
//
//    generateAluOperation(OP_PLUS, &treeRoot, reg);
//    generateAluOperation(OP_MINUS, &treeRoot, reg);
// generateAluOperation(treeRoot.nodeData.dVal, &treeRoot, reg);

    //ASSIGN TESTS
//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_MINUS_ASSIGN;
//
//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);
//
//    pRightChild->nodeData.dVal = 0x1;
//    //pRightChild->pSymbol = &symbolEntry2; //0xF
//    pLeftChild->pSymbol = &symbolEntry;   //0x20
//
//
//    generateAssignOperation(treeRoot.nodeData.dVal, &treeRoot, reg);


/* TEST SIMPLE Arithmetic
 * M (Mem)-> Means it is an identifier 
 *
 *              -
 *             / \
 *         1       *X:0xF
 *           
 *       
 */

//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_MINUS;

//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_POINTER_CONTENT);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);

//    pRightChild->nodeData.dVal = 1;
//    pLeftChild->pSymbol = &symbolEntry2;


/* TEST SIMPLE BOOLEAN
 * M (Mem)-> Means it is an identifier 
 *
 *             &&
 *             / \
 *          1      X:0xF
 *           
 *       
 */

    treeRoot.nodeType = NODE_OPERATOR;
    treeRoot.nodeData.dVal = OP_LOGICAL_AND;

    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_INTEGER);
    NodeAddNewChild(&treeRoot, &pRightChild, NODE_IDENTIFIER);

    pLeftChild->nodeData.dVal = 1;
    pRightChild->pSymbol = &symbolEntry2;



/* TEST 0 
 * M (Mem)-> Means it is an identifier 
 *
 *              +
 *             / \
 *            +   1
 *           / \
 *       M:32   #2
 */

//    treeRoot.nodeType = NODE_OPERATOR;
//    treeRoot.nodeData.dVal = OP_PLUS;

//    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
//    NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);

//    pLeftChild->nodeData.dVal = OP_PLUS;
//    pRightChild->nodeData.dVal = 1;

//    NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
//    NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

//    pLeftGrandChild->pSymbol = &symbolEntry;
//    pRightGrandChild->nodeData.dVal = 2;

/*  TEST 1
 *                 +
 *              /     \
 *             /       \
 *            /         \
 *           +           -    
 *          / \        /   \
 *   Mem:0x20 #2  Mem:0xF  #10
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_INTEGER);

    // _pLeftGrandChild->pSymbol = &symbolEntry2;
    // _pRightGrandChild->nodeData.dVal = 10;


/* TEST 2
 *                  +
 *                /   \ 
 *               /     \ 
 *              /       \
 *             /         \    
 *            +           -
 *           / \        /   \ 
 *          /   #2    M:0xF  #10      
 *         +                
 *       /   \              
 *   M:0xAB M:0xCD    
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->nodeData.dVal = OP_PLUS;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_INTEGER);

    // _pLeftGrandChild->pSymbol = &symbolEntry2;
    // _pRightGrandChild->nodeData.dVal = 10;

    // NodeAddNewChild(pLeftGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;


/* TEST 3
 *                  +
 *                /   \ 
 *               /     \ 
 *              /       \
 *             /         \    
 *            +           -
 *           / \        /   \ 
 *          / M:0x20  #10  M:0xF
 *         +                
 *       /   \              
 *   M:0xAB M:0xCD    
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_IDENTIFIER);

    // pLeftGrandChild->nodeData.dVal = OP_PLUS;
    // pRightGrandChild->pSymbol = &symbolEntry;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_IDENTIFIER);

    // _pLeftGrandChild->nodeData.dVal = 10;
    // _pRightGrandChild->pSymbol = &symbolEntry2;


    // NodeAddNewChild(pLeftGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;


/* TEST 4
 *                  -
 *                /   \  
 *               /     \ 
 *              /       \
 *             /         \
 *            -           -
 *           / \         / \  
 *     M:0x20   \   Mem:0xF #10 
 *               -         
 *              / \          
 *         M:0xAB M:0xCD      
 *                 
 */


    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_MINUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_INTEGER);

    // _pLeftGrandChild->pSymbol = &symbolEntry2;
    // _pRightGrandChild->nodeData.dVal = 10;

    // NodeAddNewChild(pRightGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(pRightGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;


/* TEST 5
 *              +
 *             / \
 *            +   \
 *           / \   \
 *   Mem:0x20  #2   \
 *                   -
 *                  / \
 *                 +   Mem:0xF
 *                / \
 *         Mem:0XAB Mem:0xCD        
 */


    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_OPERATOR);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_IDENTIFIER);

    // _pLeftGrandChild->nodeData.dVal = OP_PLUS;
    // _pRightGrandChild->pSymbol = &symbolEntry2;

    // NodeAddNewChild(_pLeftGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(_pLeftGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;




/* TEST 6
 *              +
 *             / \
 *            +   \
 *           / \   \
 *      M:0x20 #2   \
 *                   -
 *                  / \
 *               #20   \ 
 *                      +
 *                    /   \
 *                  0XAB  0xCD        
 */


    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    // pLeftChild->nodeData.dVal = OP_PLUS;
    // pRightChild->nodeData.dVal = OP_MINUS;

    // NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_IDENTIFIER);
    // NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_INTEGER);

    // pLeftGrandChild->pSymbol = &symbolEntry;
    // pRightGrandChild->nodeData.dVal = 2;

    // NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
    // NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

    // _pLeftGrandChild->nodeData.dVal = 20;
    // _pRightGrandChild->nodeData.dVal = OP_PLUS;

    // NodeAddNewChild(_pRightGrandChild, &pLeftGrandChild_, NODE_IDENTIFIER);
    // NodeAddNewChild(_pRightGrandChild, &pRightGrandChild_, NODE_IDENTIFIER);

    // pLeftGrandChild_->pSymbol = &symbolEntry3;
    // pRightGrandChild_->pSymbol = &symbolEntry4;



/* TEST 7
                     -
                    / \
                  /     \
                /         \
              /             \
            +                 -
          /  \               /  \
        /      \            /    \
      -         +         #255     -
     / \       / \                / \
    /   \     /   \              /   \
 M:0xF #32  M:0xAB M:0xCD      #42  M:0x20         
      
 */


// TreeNode_st* pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;    

//     treeRoot.nodeType = NODE_OPERATOR;
//     treeRoot.nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
//     NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

//     pLeftChild->nodeData.dVal = OP_PLUS;
//     pRightChild->nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
//     NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

//     pLeftGrandChild->nodeData.dVal = OP_MINUS;   //1º OP da ultima linha
//     pRightGrandChild->nodeData.dVal = OP_PLUS;   //2º OP da ultima linha

//     NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
//     NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

//     _pLeftGrandChild->nodeData.dVal = 255;
//     _pRightGrandChild->nodeData.dVal = OP_MINUS;   //3º OP da ultima linha

//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_1, NODE_IDENTIFIER);
//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_2, NODE_INTEGER);

//     pThirdLevelChild_1->pSymbol = &symbolEntry2;
//     pThirdLevelChild_2->nodeData.dVal = 32;

//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_3, NODE_IDENTIFIER);
//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_4, NODE_IDENTIFIER);

//     pThirdLevelChild_3->pSymbol = &symbolEntry3;
//     pThirdLevelChild_4->pSymbol = &symbolEntry4;

//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_5, NODE_INTEGER);
//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_6, NODE_IDENTIFIER);

//     pThirdLevelChild_5->nodeData.dVal = 42;
//     pThirdLevelChild_6->pSymbol = &symbolEntry;



/* TEST 8
                                -
                               / \
                             /     \
                           /         \
                         /             \
                        +                 -
                      /  \               /  \
                    /      \            /    \
                  -         +         #255     -
                 / \       / \                / \
                /   \     /   \              /   \
            M:0xF  #32 M:0xAB  -          M:0x20  + 
                              / \                / \
                            /     \             /   \        
                          #20      +           -     M:0xAB
                                  / \         / \  
                                 /   \       /   \
                           M:0xAB  M:0xCD   #1  M:0xF      
*/
// TreeNode_st *pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;
// TreeNode_st *pFourthLevelChild_1, *pFourthLevelChild_2, *pFourthLevelChild_3, *pFourthLevelChild_4;
// TreeNode_st *pFifthLevelChild_1, *pFifthLevelChild_2, *pFifthLevelChild_3, *pFifthLevelChild_4;     

//     treeRoot.nodeType = NODE_OPERATOR;
//     treeRoot.nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
//     NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

//     pLeftChild->nodeData.dVal = OP_PLUS;
//     pRightChild->nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
//     NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

//     pLeftGrandChild->nodeData.dVal = OP_MINUS;  
//     pRightGrandChild->nodeData.dVal = OP_PLUS;   

//     NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
//     NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

//     _pLeftGrandChild->nodeData.dVal = 255;
//     _pRightGrandChild->nodeData.dVal = OP_MINUS;  

//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_1, NODE_IDENTIFIER);
//     NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_2, NODE_INTEGER);

//     pThirdLevelChild_1->pSymbol = &symbolEntry2;
//     pThirdLevelChild_2->nodeData.dVal = 32;

//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_3, NODE_IDENTIFIER);
//     NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_4, NODE_OPERATOR);

//     pThirdLevelChild_3->pSymbol = &symbolEntry3;
//     pThirdLevelChild_4->nodeData.dVal = OP_MINUS;

//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_5, NODE_IDENTIFIER);
//     NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_6, NODE_OPERATOR);

//     pThirdLevelChild_5->pSymbol = &symbolEntry;
//     pThirdLevelChild_6->nodeData.dVal = OP_PLUS;

//     NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_3, NODE_OPERATOR);
//     NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_4, NODE_IDENTIFIER);

//     pFourthLevelChild_3->nodeData.dVal = OP_MINUS;
//     pFourthLevelChild_4->pSymbol = &symbolEntry3;

//     NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_3, NODE_INTEGER);
//     NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_4, NODE_IDENTIFIER);

//     pFifthLevelChild_3->nodeData.dVal = 1;
//     pFifthLevelChild_4->pSymbol = &symbolEntry2;

//     NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_1, NODE_INTEGER);
//     NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_2, NODE_OPERATOR);

//     pFourthLevelChild_1->nodeData.dVal = 20;
//     pFourthLevelChild_2->nodeData.dVal = OP_PLUS;

//     NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_1, NODE_IDENTIFIER);
//     NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_2, NODE_IDENTIFIER);

//     pFifthLevelChild_1->pSymbol = &symbolEntry3;
//     pFifthLevelChild_2->pSymbol = &symbolEntry4;

/* TEST 9
                                -
                               / \
                             /     \
                           /         \
                         /             \
                        +                 -
                      /  \               /  \
                    /      \            /    \
                  -         +         #255     -
                 / \       / \                / \
                /   \     /   \              /   \
            M:0xF  #32 M:0xAB  -          M:0x20  +
                              / \                / \
                            /     \             /   \        
                          #20      +           -     ++M:0xAB
                                  / \         / \  
                                 /   \       /   \
                           M:0xAB *M:0xCD   #1  ++M:0xF      
*/
    /* TreeNode_st *pThirdLevelChild_1, *pThirdLevelChild_2, *pThirdLevelChild_3, *pThirdLevelChild_4, *pThirdLevelChild_5, *pThirdLevelChild_6;
    TreeNode_st *pFourthLevelChild_1, *pFourthLevelChild_2, *pFourthLevelChild_3, *pFourthLevelChild_4;
    TreeNode_st *pFifthLevelChild_1, *pFifthLevelChild_2, *pFifthLevelChild_3, *pFifthLevelChild_4;

    treeRoot.nodeType = NODE_OPERATOR;
    treeRoot.nodeData.dVal = OP_MINUS;

    NodeAddNewChild(&treeRoot, &pLeftChild, NODE_OPERATOR);
    NodeAddNewChild(&treeRoot, &pRightChild, NODE_OPERATOR);

    pLeftChild->nodeData.dVal = OP_PLUS;
    pRightChild->nodeData.dVal = OP_MINUS;

    NodeAddNewChild(pLeftChild, &pLeftGrandChild, NODE_OPERATOR);
    NodeAddNewChild(pLeftChild, &pRightGrandChild, NODE_OPERATOR);

    pLeftGrandChild->nodeData.dVal = OP_MINUS;
    pRightGrandChild->nodeData.dVal = OP_PLUS;

    NodeAddNewChild(pRightChild, &_pLeftGrandChild, NODE_INTEGER);
    NodeAddNewChild(pRightChild, &_pRightGrandChild, NODE_OPERATOR);

    _pLeftGrandChild->nodeData.dVal = 255;
    _pRightGrandChild->nodeData.dVal = OP_MINUS;

    NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_1, NODE_IDENTIFIER);
    NodeAddNewChild(pLeftGrandChild, &pThirdLevelChild_2, NODE_INTEGER);

    pThirdLevelChild_1->pSymbol = &symbolEntry2;
    pThirdLevelChild_2->nodeData.dVal = 32;

    NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_3, NODE_IDENTIFIER);
    NodeAddNewChild(pRightGrandChild, &pThirdLevelChild_4, NODE_OPERATOR);

    pThirdLevelChild_3->pSymbol = &symbolEntry3;
    pThirdLevelChild_4->nodeData.dVal = OP_MINUS;

    NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_5, NODE_IDENTIFIER);
    NodeAddNewChild(_pRightGrandChild, &pThirdLevelChild_6, NODE_OPERATOR);

    pThirdLevelChild_5->pSymbol = &symbolEntry;
    pThirdLevelChild_6->nodeData.dVal = OP_PLUS;

    NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_3, NODE_OPERATOR);
    NodeAddNewChild(pThirdLevelChild_6, &pFourthLevelChild_4, NODE_PRE_INC);

    pFourthLevelChild_3->nodeData.dVal = OP_MINUS;
    pFourthLevelChild_4->pSymbol = &symbolEntry3;

    NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_3, NODE_INTEGER);
    NodeAddNewChild(pFourthLevelChild_3, &pFifthLevelChild_4, NODE_PRE_INC);

    pFifthLevelChild_3->nodeData.dVal = 1;
    pFifthLevelChild_4->pSymbol = &symbolEntry2;

    NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_1, NODE_INTEGER);
    NodeAddNewChild(pThirdLevelChild_4, &pFourthLevelChild_2, NODE_OPERATOR);

    pFourthLevelChild_1->nodeData.dVal = 20;
    pFourthLevelChild_2->nodeData.dVal = OP_PLUS;

    NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_1, NODE_IDENTIFIER);
    NodeAddNewChild(pFourthLevelChild_2, &pFifthLevelChild_2, NODE_POINTER_CONTENT);

    pFifthLevelChild_1->pSymbol = &symbolEntry3;
    pFifthLevelChild_2->pSymbol = &symbolEntry4; */


/*  ASSIGN TEST 1
 *                 =
 *              /     \
 *           M:0xF     #1    
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_ASSIGN;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_INTEGER);

    // pLeftChild->pSymbol = &symbolEntry2;
    // pRightChild->nodeData.dVal = 1;


/*  ASSIGN TEST 2
 *                 =
 *              /     \
 *           M:0xF   M:0xAB       
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_ASSIGN;

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_IDENTIFIER);

    // pLeftChild->pSymbol = &symbolEntry2;
    // pRightChild->pSymbol = &symbolEntry3;


/*  ASSIGN TEST 3
 *                 =
 *              /     \
 *          *p:0xF  &a:0xAB       
 *                  
 */

    // treeRoot.nodeType = NODE_OPERATOR;
    // treeRoot.nodeData.dVal = OP_ASSIGN;

    // // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_POINTER_CONTENT);
    // // NodeAddNewChild(&treeRoot, &pRightChild, NODE_REFERENCE);

    // NodeAddNewChild(&treeRoot, &pLeftChild, NODE_POINTER_CONTENT);
    // NodeAddNewChild(&treeRoot, &pRightChild, NODE_REFERENCE);

    // pLeftChild->pSymbol = &symbolEntry2;
    // pRightChild->pSymbol = &symbolEntry3;

    generateCode(&treeRoot);

    //Release reg12 which is the one alloc'ed for the root
    releaseReg(REG_R12);

}

void functionGenerationTestUnit()
{
    pAsmFile = stdout;


    /* Test 1
     * Function Prototypes
     * Should not print
     * 
     *          Function
     *            /  \
     *           /    \
     *        Type    Parameter X
     * 
     */
    {
        TreeNode_st treeRoot = {0};
        TreeNode_st* pLeftChild, *pRightChild;
        
        treeRoot.nodeType = NODE_FUNCTION;
        
        NodeAddNewChild(&treeRoot, &pLeftChild, NODE_TYPE);
        NodeAddNewChild(&treeRoot, &pRightChild, NODE_PARAMETER);

        generateCode(&treeRoot);
    }
    

    /** Test 2 
     * Void Function with Implementation
     * Prints routine to save registers, generate body, restore registers and jump to before call
     *
     *                      Function
     *                        /|\
     *                       / | \
     *                      /  |  \
     *                   Type  |  Start_Scope
     *                         |
     *                     Parameter
     * 
     */
    {
        TreeNode_st treeRoot = {0};
        TreeNode_st* pLeftChild, *pMiddleChild, *pRightChild;
        
        treeRoot.nodeType = NODE_FUNCTION;
        treeRoot.nodeVarType = TYPE_VOID;
        treeRoot.nodeData.sVal = "Test2_Function";

        NodeAddNewChild(&treeRoot, &pLeftChild, NODE_TYPE);
        NodeAddNewChild(&treeRoot, &pMiddleChild, NODE_PARAMETER);
        NodeAddNewChild(&treeRoot, &pRightChild, NODE_START_SCOPE);



        generateCode(&treeRoot);
    }



    /** Test 3 
     * Function Call
     * Prints routine to save registers, generate body, restore registers and jump to before call
     *
     *                      Function Call
     *                        /
     *                       /
     *                      / 
     *                 Identifier a --- Identifier b
     * 
     */
    /* {
        TreeNode_st treeRoot = {0};
        TreeNode_st* pLeftChild; 
        TreeNode_st* pLeftSibling;
        
        SymbolEntry_st symbolEntry = {.symbolContent_u.SymbolFunction_s.parameterNumber = 1};
        SymbolEntry_st symbolEntry2 = {.symbolContent_u.memoryLocation = 0x20};
        // For some reason uncommenting one of the following statments results in a segmentation fault
        SymbolEntry_st symbolEntry3 = {.symbolContent_u.memoryLocation = 0xAB};

        treeRoot.nodeType = NODE_FUNCTION_CALL;
        treeRoot.pSymbol = &symbolEntry;
        pLeftChild->pSymbol = &symbolEntry2;
        //pLeftSibling.pSymbol = &symbolEntry2;

        //pLeftChild->pSibling = &pLeftSibling;

        NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);

        generateCode(&treeRoot);
    } */



    /** Test 4 
     * Returns with Identifier
     * Prints routine to restore registers and jump to before call
     *
     *                      Return
     *                        /
     *                       /
     *                      / 
     *                 Identifier a
     * 
     */
    {
        TreeNode_st treeRoot = {0};
        TreeNode_st* pLeftChild;
        
        SymbolEntry_st symbolEntry = {.symbolContent_u.memoryLocation = 0x20};

        treeRoot.nodeType = NODE_RETURN;

        NodeAddNewChild(&treeRoot, &pLeftChild, NODE_IDENTIFIER);
        pLeftChild->pSymbol = &symbolEntry;
        generateCode(&treeRoot);
    }


    printf("\n");
}

