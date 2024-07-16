#include "../Util/Logger.h"
#include "CodeGeneration.h"
#include "CodeGenerationTypes.h"
#include "../Util/Util.h"


FILE *pAsmFile;

static reg_et arrayIndexRegSave;
static reg_et dRegSave;
static reg_et lRegSave;
static reg_et rRegSave;

postinc_list_st* postIncList;
bool delayPostIncDec = 0;


static reg_state_st regStateList[] =
{
    {.regName = REG_R12, .isFree = true},
    {.regName = REG_R13, .isFree = true},
    {.regName = REG_R14, .isFree = true},
    {.regName = REG_R15, .isFree = true},
    {.regName = REG_R16, .isFree = true},
    {.regName = REG_R17, .isFree = true},
    {.regName = REG_R18, .isFree = true},
    {.regName = REG_R19, .isFree = true},
    {.regName = REG_R20, .isFree = true},
    {.regName = REG_R21, .isFree = true},
    {.regName = REG_R22, .isFree = true},
    {.regName = REG_R23, .isFree = true},
    {.regName = REG_R24, .isFree = true},
    {.regName = REG_R25, .isFree = true},
    {.regName = REG_R26, .isFree = true},
    {.regName = REG_R27, .isFree = true},
    {.regName = REG_R28, .isFree = true},
    {.regName = REG_R29, .isFree = true},
    {.regName = REG_R30, .isFree = true},
    {.regName = REG_R31, .isFree = true}
};

static operator_pair_st operatorLut[] =
{
    {.operatorType = OP_PLUS, .assignOpType = OP_PLUS_ASSIGN, .asmInstruction = INST_ADD},
    {.operatorType = OP_MINUS, .assignOpType = OP_MINUS_ASSIGN, .asmInstruction = INST_SUB},
    {.operatorType = OP_RIGHT_SHIFT, .assignOpType = OP_RIGHT_SHIFT_ASSIGN, .asmInstruction = INST_RR},
    {.operatorType = OP_LEFT_SHIFT, .assignOpType = OP_LEFT_SHIFT_ASSIGN, .asmInstruction = INST_RL},
    {.operatorType = OP_BITWISE_AND, .assignOpType = OP_BITWISE_AND_ASSIGN, .asmInstruction = INST_AND},
    {.operatorType = OP_BITWISE_NOT, .assignOpType = -1, .asmInstruction = INST_NOT},
    {.operatorType = OP_BITWISE_OR, .assignOpType = OP_BITWISE_OR_ASSIGN, .asmInstruction = INST_OR},
    {.operatorType = OP_BITWISE_XOR, .assignOpType = OP_BITWISE_XOR_ASSIGN, .asmInstruction = INST_XOR},

    {.operatorType = (OperatorType_et) OP_GREATER_THAN, .assignOpType = -1, .asmInstruction = INST_BGT},
    {.operatorType = (OperatorType_et) OP_LESS_THAN_OR_EQUAL, .assignOpType = -1, .asmInstruction = INST_BLE},
    {.operatorType = (OperatorType_et) OP_GREATER_THAN_OR_EQUAL, .assignOpType = -1, .asmInstruction = INST_BGE},
    {.operatorType = (OperatorType_et) OP_LESS_THAN, .assignOpType = -1, .asmInstruction = INST_BLT},
    {.operatorType = (OperatorType_et) OP_EQUAL, .assignOpType = -1, .asmInstruction = INST_BEQ},
    {.operatorType = (OperatorType_et) OP_NOT_EQUAL, .assignOpType = -1, .asmInstruction = INST_BNE},
    {.operatorType = (OperatorType_et) OP_LOGICAL_AND, .assignOpType = -1, .asmInstruction = INST_BEQ},
    {.operatorType = (OperatorType_et) OP_LOGICAL_OR, .assignOpType = -1, .asmInstruction = INST_BNE},
    {.operatorType = (OperatorType_et) OP_LOGICAL_NOT, .assignOpType = -1, .asmInstruction = INST_BEQ},
};

#define OPERATOR_LUT_SIZE (sizeof(operatorLut) / sizeof(operator_pair_st))
#define NOF_SCRATCH_REGISTER (sizeof(regStateList) / sizeof(reg_state_st))


static asm_instr_et mapInstructionFromOperator(OperatorType_et opType)
{
    size_t i;

    for (i = 0; i < OPERATOR_LUT_SIZE; ++i)
    {
        if (operatorLut[i].operatorType == opType)
            return operatorLut[i].asmInstruction;
    }

    return INST_NOP;
}

static asm_instr_et mapInstructionFromAssignOp(OperatorType_et opType)
{
    size_t i;

    for (i = 0; i < OPERATOR_LUT_SIZE; ++i)
    {
        if (operatorLut[i].assignOpType == opType)
            return operatorLut[i].asmInstruction;
    }

    return INST_NOP;
}


int executeCodeGeneration(TreeNode_st *pTreeRoot, FILE* pDestStream)
{
    if (!pTreeRoot || !pDestStream)
        return -EINVAL;

    pAsmFile = pDestStream;

    //Init list of post inc/dec statements
    PostIncListInit();

    //Emit Iinitialization  Code
    generateInitCode();
    
    //Function code used to execute multiplication
    generateMultiplication();

    //Function code used to execute division
    generateDivision();
    
    generateCode(pTreeRoot);

    return 0;
}

static int generateInitCode()
{
    int ret = 0;
    
    fprintf(pAsmFile, ".org 0x00\n");
    emitJumpInstruction(INST_JMP, REG_R0, REG_NONE, 64);
    // colocar interrupts

    fprintf(pAsmFile, "\n.org 0x4000\n");
    fprintf(pAsmFile, "\tHALT\n\n");
    
    fprintf(pAsmFile, ".org 0x40\n");
    // Initialize Stack and Frame pointers
    ret |= emitMemoryInstruction(INST_LDI, REG_R2, REG_NONE, STACK_START_ADDR, NULL);
    ret |= emitMemoryInstruction(INST_LDI, REG_R3, REG_NONE, STACK_START_ADDR, NULL);
    
    ret |= emitMemoryInstruction(INST_LDI, REG_R1, REG_NONE, 16384, NULL);
    push(REG_R1);
    ret |= emitMemoryInstruction(INST_LDI, REG_R1, REG_NONE, 0, "main");
    ret |= emitJumpInstruction(INST_JMP, REG_R1, REG_NONE, 0);

    return ret;
}

static int generateCode(TreeNode_st *pTreeNode)
{
    TreeNode_st *pSib;
    int ret = parseNode(pTreeNode, NODE_TYPE_NOT_DEFINED, OP_NOT_DEFINED, 0);
    if (ret < 0)
        return ret;

    pSib = pTreeNode->pSibling;
    while (pSib)
    {
        parseNode(pSib, NODE_TYPE_NOT_DEFINED, OP_NOT_DEFINED, 0);
        pSib = pSib->pSibling;
    }

    return 0;
}


static int generateDynamicMemoryInstruction(asm_instr_et instructionType, reg_et reg, TreeNode_st* pTreeNode)
{
    //FALTA LOADS IMEDIATOS

    if(instructionType == INST_LD)
    {
        if(pTreeNode->pSymbol->scopeLocation == FUNCTION_SCOPE)
        {
            emitMemoryInstruction(INST_LDX, reg, REG_R2, -pTreeNode->pSymbol->symbolContent_u.memoryLocation - 2, NULL);
        }
        else if(pTreeNode->pSymbol->scopeLocation == ARGUMENT_SCOPE)
        {
            emitMemoryInstruction(INST_LDX, reg, REG_R2, pTreeNode->pScope->parameterNumber - pTreeNode->pSymbol->paramPosition, NULL);
        }
        else
        {
            emitMemoryInstruction(INST_LD, reg, REG_NONE, pTreeNode->pSymbol->symbolContent_u.memoryLocation, NULL);
        }
    }
    else if(instructionType == INST_LDI)
    {
        if(pTreeNode->pSymbol->scopeLocation == FUNCTION_SCOPE)
        {
            emitMemoryInstruction(INST_LDI, reg, REG_NONE,  STACK_START_ADDR - pTreeNode->pSymbol->symbolContent_u.memoryLocation - 2, NULL);
            emitAluInstruction(INST_SUB, false, 0, reg, reg, REG_R2);
        }
        else if(pTreeNode->pSymbol->scopeLocation == ARGUMENT_SCOPE)
        {
            emitMemoryInstruction(INST_LDI, reg, REG_NONE,  STACK_START_ADDR - pTreeNode->pScope->parameterNumber - pTreeNode->pSymbol->paramPosition, NULL);
            emitAluInstruction(INST_SUB, false, 0, reg, reg, REG_R2);
        }
        else
        {
            emitMemoryInstruction(INST_LDI, reg, REG_NONE, pTreeNode->pSymbol->symbolContent_u.memoryLocation, NULL);
        }
    }
    else if(instructionType == INST_ST)
    {
        if(pTreeNode->pSymbol->scopeLocation == FUNCTION_SCOPE)
        {
            emitMemoryInstruction(INST_STX, reg, REG_R2, - pTreeNode->pSymbol->symbolContent_u.memoryLocation - 2, NULL);
        }
        else if(pTreeNode->pSymbol->scopeLocation == ARGUMENT_SCOPE)
        {
            emitMemoryInstruction(INST_STX, reg, REG_R2, pTreeNode->pScope->parameterNumber - pTreeNode->pSymbol->paramPosition, NULL);
        }
        else
        {
            emitMemoryInstruction(INST_ST, reg, REG_NONE, pTreeNode->pSymbol->symbolContent_u.memoryLocation, NULL);
        }
    }
    //else
        //LOG_ERROR("Un-implemented\n");
    
}


static uint32_t generateMemoryAddress(TreeNode_st* pTreeNode)
{
    uint32_t outMemory;

    if(!IS_TERMINAL_NODE(NODE_TYPE(pTreeNode)) ||  NODE_TYPE(pTreeNode) == NODE_INTEGER)
        return -EINVAL;

    if(pTreeNode->pSymbol->scopeLocation == FUNCTION_SCOPE)
    {

        outMemory = STACK_START_ADDR - pTreeNode->pScope->parameterNumber - pTreeNode->pSymbol->symbolContent_u.memoryLocation - 1;
    }
    else if(pTreeNode->pSymbol->scopeLocation == ARGUMENT_SCOPE)
    {
        outMemory = STACK_START_ADDR - pTreeNode->pSymbol->paramPosition - 1; 
    }
    else
        outMemory = pTreeNode->pSymbol->symbolContent_u.memoryLocation;


    return outMemory;

}


/// \brief This function allows to generate code for ALU instructions
/// \param instructionType Enum representing the ALU instruction to emit
/// \param isImed Boolean value that defines if the right hand operand should be an immediate or from memory
/// \param imedValue If isImed is set to true, this value is used as the right hand operand
/// \param resultReg Register to put the operation result into
/// \param leftOperand Left side operand
/// \param rightOperand Right side operand, only used if isImed is equal to false
/// \return -EINVAL if invalid arguments are passed, -EPERM if the combination of arguments is invalid, 0 on success
static int emitAluInstruction(asm_instr_et instructionType,
                              uint8_t isImed,
                              uint32_t imedValue,
                              reg_et resultReg,
                              reg_et leftOperand,
                              reg_et rightOperand)
{

    //NOT instruction can't use immediate as a parameter
    if ((instructionType == INST_NOT) && (isImed))
        return -EPERM;

    if ((isImed) && (rightOperand != REG_NONE))
        return -EPERM;

    if (isImed)
    {
        if (instructionType == INST_CMP)
        {
            fprintf(pAsmFile, "\t%s %s,#%d\n",
                    INSTRUCTION(instructionType),
                    REGISTER(leftOperand),
                    imedValue);
        }
        else
        {
            fprintf(pAsmFile, "\t%s %s,%s,#%d\n",
                    INSTRUCTION(instructionType),
                    REGISTER(resultReg),
                    REGISTER(leftOperand),
                    imedValue);
        }
    }
    else
    {
        if (instructionType == INST_CMP)
        {
            fprintf(pAsmFile, "\t%s %s,%s\n",
                    INSTRUCTION(instructionType),
                    REGISTER(leftOperand),
                    REGISTER(rightOperand));
        }
        else
        {
            if (rightOperand == REG_NONE)
            {
                fprintf(pAsmFile, "\t%s %s,%s\n",
                        INSTRUCTION(instructionType),
                        REGISTER(resultReg),
                        REGISTER(leftOperand));
            }
            else
            {
                fprintf(pAsmFile, "\t%s %s,%s,%s\n",
                        INSTRUCTION(instructionType),
                        REGISTER(resultReg),
                        REGISTER(leftOperand),
                        REGISTER(rightOperand));
            }
        }
    }

    return 0;
}

/// \brief This function emits to the destination assembly file a memory type instruction (LD, LDI, LDX, ST, STX)
/// \param instructionType Enum representing the instruction to generate assembly for
/// \param reg Register used for the memory operation
/// \param idx Index register used for LDX and STX operations
/// \param dVal Immediate value used for the memory operation
/// \return -EINVAL if invalid arguments are passed, -EPERM if the passed instruction is not a valid memory instruction
/// returns 0 on success.
static int emitMemoryInstruction(asm_instr_et instructionType, reg_et reg, reg_et idx, uint32_t dVal, char* Label)
{
    if (reg >= REG_NONE)
        return -EINVAL;

    switch (instructionType)
    {
        case INST_LD:

            if (VALID_LD_IMMED(dVal))
            {
                fprintf(pAsmFile, "\t%s %s,#%d\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        dVal & MAX_IMMED_LD);
            }
            else
            {
                //Emit LDI of dVal to a Register X
                //Emit LDX reg, register X, 0
                reg_et auxReg = getNextAvailableReg();
                emitMemoryInstruction(INST_LDI, auxReg, REG_NONE, dVal, NULL);
                emitMemoryInstruction(INST_LDX, reg, auxReg, 0, NULL);
                releaseReg(auxReg);
            }
            break;

        case INST_LDI:

            if(Label != NULL)
                fprintf(pAsmFile, "\t%s %s,:FUNCTION_%s\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        Label
                );
            else if (VALID_LDI_IMMED(dVal))
            {
                fprintf(pAsmFile, "\t%s %s,#%d\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        dVal & MAX_IMMED_LD);
            }        
            else
                loadImm32(dVal, reg);
            break;

        case INST_ST:

            if (VALID_ST_IMMED(dVal))
            {
                fprintf(pAsmFile, "\t%s %s,#%d\n",
                        INSTRUCTION(instructionType),
                        REGISTER(reg),
                        dVal & MAX_IMMED_ST);
            }
            else
            {
                //Emit LDI of dVal to a Register X
                //Emit LDX reg, register X, 0
                reg_et auxReg = getNextAvailableReg();
                emitMemoryInstruction(INST_LDI, auxReg, REG_NONE, dVal, NULL);
                emitMemoryInstruction(INST_STX, reg, auxReg, 0, NULL);
                releaseReg(auxReg);
            }
            break;

        case INST_LDX:
        case INST_STX:

            if (idx >= REG_NONE)
                return -EINVAL;

            fprintf(pAsmFile, "\t%s %s,%s,#%d\n",
                    INSTRUCTION(instructionType),
                    REGISTER(reg),
                    REGISTER(idx),
                    dVal);
            break;

        default:
            return -EPERM;
    }

    return 0;
}

static uint32_t labelCounters[LABEL_MAX] = {0};

static int emitLabelInstruction(label_et labelType, uint32_t count, char* nameLabel)
{
    if (labelType < WHILE_START || labelType >= LABEL_MAX)
        return -EINVAL;
    if(labelType != FUNCTION_NAME)
        fprintf(pAsmFile, "%s%u:\n",
                LABEL(labelType),
                count);
    else
        fprintf(pAsmFile, "\n\n\n%s%s:\n",
                LABEL(labelType),
                nameLabel);
    
    return 0;
}

static uint32_t getPostIncLabelCounter(label_et labeltype)
{
    if (labeltype < WHILE_START || labeltype >= LABEL_MAX)
        return -EINVAL;

    return labelCounters[labeltype]++;
}

static uint32_t getLabelCounter(label_et labelType)
{
    if (labelType < WHILE_START || labelType >= LABEL_MAX)
        return -EINVAL;

    return labelCounters[labelType];
}

/// \brief Function to emit branch labels
static int emitBranchInstruction(asm_instr_et instructionType, label_et labelType, uint32_t counter)
{
   //CheckLabel type
    if (labelType < WHILE_START || labelType >= LABEL_MAX)
        return -EINVAL;

    if (instructionType < INST_BGT || instructionType > INST_BMI)
        return -EINVAL;

    if(counter < 0)
        return -EINVAL;

    fprintf(pAsmFile, "\t%s %s%u\n",
            INSTRUCTION(instructionType),
            LABEL(labelType),
            counter);

    return 0;
}

static int emitJumpInstruction(asm_instr_et instructionType, reg_et dReg, reg_et lReg, uint32_t dVal)
{
    if (dReg >= REG_NONE) 
        return -EINVAL;
        
    if(instructionType == INST_JMP)
        fprintf(pAsmFile, "\t%s %s,#%u\n",
            INSTRUCTION(instructionType),
            REGISTER(dReg),
            dVal
            );

    else if (instructionType == INST_JMPL)
        fprintf(pAsmFile, "\t%s %s,%s,#%u\n",
            INSTRUCTION(instructionType),
            REGISTER(dReg),
            REGISTER(lReg),
            dVal
            );
    else
        return -EINVAL;

    return 0;
    
}

/// \brief Considering the LDI instruction only allows to load values up to 2^22 - 1, some arithmetic must be used in
/// order to use immediate values larger than this. This function generates boilerplate code to perform this operation
/// \param dVal Value of the immediate to load
/// \param destReg Register that the immediate should be loaded to
/// \return -ENOMEM if unable to acquire a register to perform arithmetic operations on, other negative errors if unable
/// to emit operations or release the working register, returns 0 on success
static int loadImm32(uint32_t dVal, reg_et destReg)
{
    int ret;
    reg_et workingReg;
    uint16_t lw16 = dVal & 0xFFFF;
    uint16_t hp16 = (dVal >> 16) & 0xFFFF;

    workingReg = getNextAvailableReg();
    if (workingReg == REG_NONE)
        return -ENOMEM;

    ret = emitMemoryInstruction(INST_LDI, workingReg, REG_NONE, hp16, NULL);
    ret |= emitAluInstruction(INST_RL, true, 16, workingReg, workingReg, REG_NONE);
    ret |= emitAluInstruction(INST_OR, true, lw16, destReg, workingReg, REG_NONE);
    ret |= releaseReg(workingReg);

    return ret;
}


/// \brief Goes through the postIncList and emits all the increments of the addresses that were added to it
/// \param reg_et auxReg to perform operations
/// \return -ENODATA if list is empty
static int handlePostIncDecOperations(reg_et auxReg)
{

    delayPostIncDec = 0;

    if(postIncList->size <= 0)
        return -ENODATA;
    
    while (postIncList->size > 0) 
    {        
        list_item_st* current_item = &postIncList->savedItem[postIncList->size - 1];
        generateDynamicMemoryInstruction(INST_LD, auxReg, current_item->treeNode);

        if(current_item->is_increment)
            emitAluInstruction(INST_ADD, true, 1, auxReg, auxReg, REG_NONE);
        else
            emitAluInstruction(INST_SUB, true, 1, auxReg, auxReg, REG_NONE);

        generateDynamicMemoryInstruction(INST_ST, auxReg, current_item->treeNode);

        PostIncListDelete(postIncList);
    }

    return 0;
}

static int handleMulDivNode(OperatorType_et opType, reg_et dReg, reg_et lReg, reg_et rReg)
{
    if(opType == OP_MULTIPLY)
    {
        //Pass arguments to execute MUL function
        emitAluInstruction(INST_MOV, false, 0, REG_R4, lReg, REG_NONE);
        emitAluInstruction(INST_MOV, false, 0, REG_R5, rReg, REG_NONE);
        reg_et labelReg = getNextAvailableReg();
        emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, "FUNCTION_MUL");
        emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
        emitAluInstruction(INST_MOV, false, 0, dReg, REG_R4, REG_NONE);
        releaseReg(labelReg);
    }
    else if(opType == OP_DIVIDE)
    {
        //Pass arguments to execute MUL function
        emitAluInstruction(INST_MOV, false, 0, REG_R4, lReg, REG_NONE);
        emitAluInstruction(INST_MOV, false, 0, REG_R5, rReg, REG_NONE);
        reg_et labelReg = getNextAvailableReg();
        emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, "FUNCTION_DIV");
        emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
        emitAluInstruction(INST_MOV, false, 0, dReg, REG_R4, REG_NONE);
        releaseReg(labelReg);

    }
    else if (opType == OP_REMAIN)
    {
        //Pass arguments to execute MUL function
        emitAluInstruction(INST_MOV, false, 0, REG_R4, lReg, REG_NONE);
        emitAluInstruction(INST_MOV, false, 0, REG_R5, rReg, REG_NONE);
        reg_et labelReg = getNextAvailableReg();
        emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, "FUNCTION_DIV");
        emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
        emitAluInstruction(INST_MOV, false, 0, dReg, REG_R5, REG_NONE);
        releaseReg(labelReg);
    }

    return 0;
}

/// \brief Places the memory location of the array[exp] in the register passed in the parameters
/// \param reg_et ArrayLocationReg to place the memory location of the array[exp] 
/// \param TreeNode_st pointer to the Array Node
/// \return -EINVAL if any argument is invalid
static int handleArrayIndexedExpressions(TreeNode_st *pTreeNode, reg_et ArrayLocationReg)
{
    reg_et IndexValReg;

    if (ArrayLocationReg >= REG_NONE)
        return -EINVAL;
    
    if(pTreeNode == NULL || (NODE_TYPE(pTreeNode) != NODE_ARRAY_INDEX))
        return -EINVAL;
    

    //If the node is not a terminal node, parse the left child node
    if(!IS_TERMINAL_NODE(L_CHILD_TYPE(pTreeNode)))
    {
        parseNode(&L_CHILD(pTreeNode), NODE_ARRAY_INDEX, OP_NOT_DEFINED, true);
        //Get the reg alocated as dreg in the parseNode func
        IndexValReg = arrayIndexRegSave;
        generateDynamicMemoryInstruction(INST_LD, ArrayLocationReg, pTreeNode);

        if(pTreeNode->pSymbol->scopeLocation == GLOBAL_SCOPE)
            emitAluInstruction(INST_ADD, false, 0, ArrayLocationReg, IndexValReg, ArrayLocationReg);
        else
            emitAluInstruction(INST_SUB, false, 0, ArrayLocationReg, IndexValReg, ArrayLocationReg);

        return 0;
    }
    else
    {
        if(L_CHILD_TYPE(pTreeNode) == NODE_INTEGER)
        {
            generateDynamicMemoryInstruction(INST_LD, ArrayLocationReg, pTreeNode);
            if(pTreeNode->pSymbol->scopeLocation == GLOBAL_SCOPE)
                emitAluInstruction(INST_ADD, true, L_CHILD_DVAL(pTreeNode), ArrayLocationReg, ArrayLocationReg, REG_NONE);
            else
                emitAluInstruction(INST_SUB, true, L_CHILD_DVAL(pTreeNode), ArrayLocationReg, ArrayLocationReg, REG_NONE);
        }
        else
        if(L_CHILD_TYPE(pTreeNode) == NODE_IDENTIFIER)
        {
            reg_et tempReg = getNextAvailableReg();
            generateDynamicMemoryInstruction(INST_LD, ArrayLocationReg, pTreeNode);
            generateDynamicMemoryInstruction(INST_LD, ArrayLocationReg, &L_CHILD(pTreeNode));
            releaseReg(tempReg);
        }
    }

    return 0;
}

static int generateImmediateAluOperation(TreeNode_st *pTreeNode, asm_instr_et asmInstruction, reg_et destReg, reg_et tempReg)
{
    // i = 1 if the integer is the left child
    uint8_t i = ((L_CHILD_TYPE(pTreeNode)) == NODE_INTEGER) ? 1 : 0;

    //Gen Code for the Terminal Node that is not an INTEGER
    //Nodes with 2 constants will never exist 
    switch (pTreeNode->pChilds[i].nodeType)
    {
        case NODE_IDENTIFIER:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &pTreeNode->pChilds[i]);
            break;
        case NODE_POINTER_CONTENT:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &pTreeNode->pChilds[i]);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0, NULL);
            break;
        case NODE_REFERENCE:
            generateDynamicMemoryInstruction(INST_LDI, tempReg, &pTreeNode->pChilds[i]);
            break;
        case NODE_POST_INC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &pTreeNode->pChilds[i]);
            //If an assign was detected earlier, add this addr to the list so that it can be incremented later on
            if(delayPostIncDec)
                PostIncListInsert(postIncList, true, &pTreeNode->pChilds[i]); 
            break;
        case NODE_PRE_INC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &pTreeNode->pChilds[i]);
            emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
           generateDynamicMemoryInstruction(INST_ST, tempReg, &pTreeNode->pChilds[i]);
            break;
        case NODE_POST_DEC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &pTreeNode->pChilds[i]);
            //If an assign was detected earlier, add this addr to the list so that it can be decremented later on
            if(delayPostIncDec)
                PostIncListInsert(postIncList, false, &pTreeNode->pChilds[i]);           
            break;
        case NODE_PRE_DEC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &pTreeNode->pChilds[i]);
            emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, tempReg, &pTreeNode->pChilds[i]);       
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&pTreeNode->pChilds[i], tempReg);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0, NULL);
            break;
        case NODE_FUNCTION_CALL:
            generateCode(&pTreeNode->pChilds[i]);
            emitAluInstruction(INST_MOV, false, 0, tempReg, REG_R4, REG_NONE);
            break;
        default:
           // LOG_ERROR("Un-Implemented condition!\n");
            break;
    }

    //now switch the i var to the INTEGER POSITION
    i = !i;
    
    //Since ALU always performs Immed - RLeft, for performing subtractions with immediate, instead of a SUB
    //an ADD with the immediate negated is performed and then we negate the result using R0_REG
    //Enters this if when the operation is a SUB and the integer is at the left
    if ((asmInstruction == INST_SUB) && (!i))
    {
        if (VALID_ALU_IMMED(L_CHILD_DVAL(pTreeNode)))
        {
            emitAluInstruction(INST_ADD, true, -L_CHILD_DVAL(pTreeNode), destReg, tempReg, REG_NONE);
            emitAluInstruction(INST_SUB, false, 0, destReg, REG_R0, destReg);

        }
        else //In case Immediate value is bigger then 16 bits
        {
            emitMemoryInstruction(INST_LDI, destReg, REG_NONE, -L_CHILD_DVAL(pTreeNode), NULL);
            emitAluInstruction(INST_ADD, false, 0, destReg, destReg, tempReg);
        }
    }
    else
    {
        if (pTreeNode->pChilds[i].nodeData.dVal <= MAX_IMMED_ALU)
        {
            emitAluInstruction(asmInstruction, true, pTreeNode->pChilds[i].nodeData.dVal, destReg, tempReg, REG_NONE);
        }
        else //In case Immediate value is bigger then 16 bits
        {
            emitMemoryInstruction(INST_LDI, destReg, REG_NONE, pTreeNode->pChilds[i].nodeData.dVal, NULL);
            emitAluInstruction(asmInstruction, false, 0, destReg, destReg, tempReg);
        }
    }


    //Post Inc/Dec here if no assign was found during traverse
    if(!delayPostIncDec && (pTreeNode->pChilds[!i].nodeData.dVal == NODE_POST_INC))
    {
        emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
        generateDynamicMemoryInstruction(INST_ST, tempReg, &pTreeNode->pChilds[i]);
    }

    if(!delayPostIncDec && (pTreeNode->pChilds[!i].nodeData.dVal == NODE_POST_DEC))
    {
        emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
        generateDynamicMemoryInstruction(INST_ST, tempReg, &pTreeNode->pChilds[!i]);
        delayPostIncDec = 0;
    }

    return 0;
}


static int generateAluOperation(TreeNode_st *pTreeNode, reg_et destReg)
{
    uint32_t memAddr;
    uint32_t leftAddr;
    uint32_t rightAddr;
    reg_et lReg = getNextAvailableReg();
    reg_et rReg = getNextAvailableReg();
    OperatorType_et opType = (OperatorType_et) pTreeNode->nodeData.dVal;
    asm_instr_et asmInstruction = mapInstructionFromOperator(opType);
    bool post_inc_left = 0;
    bool post_inc_right = 0;

    int childPos = 0;
    bool is_postdec= 0;
    bool is_postinc= 0;

   
    if ((L_CHILD_TYPE(pTreeNode) == NODE_INTEGER) || (R_CHILD_TYPE(pTreeNode)) == NODE_INTEGER)
    {
        if(opType != OP_MULTIPLY && opType != OP_DIVIDE && opType != OP_REMAIN)
        {
            generateImmediateAluOperation(pTreeNode, asmInstruction, destReg, lReg);
            releaseReg(lReg);
            releaseReg(rReg);
            return 0;
        }
    }

 
    switch (L_CHILD_TYPE(pTreeNode))
    {
        case NODE_INTEGER:
            emitMemoryInstruction(INST_LDI, lReg, REG_NONE, L_CHILD_DVAL(pTreeNode), NULL);
            break;
        case NODE_IDENTIFIER:
            generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            break;
        case NODE_POINTER_CONTENT:
             generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            emitMemoryInstruction(INST_LDX, lReg, lReg, 0, NULL);
            break;
        case NODE_REFERENCE:
            generateDynamicMemoryInstruction(INST_LDI, lReg, &L_CHILD(pTreeNode));
            break;
        case NODE_POST_INC:
            generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            if(delayPostIncDec)
                PostIncListInsert(postIncList, true, &L_CHILD(pTreeNode));
            childPos = 0;
            is_postinc = 1;
            break;
        case NODE_PRE_INC:
            generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            emitAluInstruction(INST_ADD, true, 1, lReg, lReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, lReg, &L_CHILD(pTreeNode));
            break;
        case NODE_POST_DEC:
            generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            if(delayPostIncDec)
                PostIncListInsert(postIncList, false, &L_CHILD(pTreeNode));
            childPos = 0;
            is_postdec = 1;
            break;
        case NODE_PRE_DEC:
            generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            emitAluInstruction(INST_SUB, true, 1, lReg, lReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, lReg, &L_CHILD(pTreeNode));
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&L_CHILD(pTreeNode), lReg);
            emitMemoryInstruction(INST_LDX, lReg, lReg, 0, NULL);
            break;
        case NODE_FUNCTION_CALL:
            generateCode(&L_CHILD(pTreeNode));
            emitAluInstruction(INST_MOV, false, 0, lReg, REG_R4, REG_NONE);
            break;
        default:
            //LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    switch (R_CHILD_TYPE(pTreeNode))
    {
        case NODE_INTEGER:
            emitMemoryInstruction(INST_LDI, rReg, REG_NONE, R_CHILD_DVAL(pTreeNode), NULL);
            break;
        case NODE_IDENTIFIER:
            generateDynamicMemoryInstruction(INST_LD, rReg, &R_CHILD(pTreeNode));
            break;
        case NODE_POINTER_CONTENT:
            generateDynamicMemoryInstruction(INST_LD, rReg, &R_CHILD(pTreeNode));
            emitMemoryInstruction(INST_LDX, rReg, rReg, 0, NULL);
            break;
        case NODE_REFERENCE:
            generateDynamicMemoryInstruction(INST_LDI, rReg, &R_CHILD(pTreeNode));
            break;
        case NODE_POST_INC:
            generateDynamicMemoryInstruction(INST_LD, rReg, &R_CHILD(pTreeNode));
            if(delayPostIncDec)
                PostIncListInsert(postIncList, true, &R_CHILD(pTreeNode));
            childPos = 1;
            is_postinc = 1;
            break;
        case NODE_PRE_INC:
            generateDynamicMemoryInstruction(INST_LD, rReg, &R_CHILD(pTreeNode));
            emitAluInstruction(INST_ADD, true, 1, rReg, rReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, rReg, &R_CHILD(pTreeNode));
            break;
        case NODE_POST_DEC:
            generateDynamicMemoryInstruction(INST_LD, rReg, &R_CHILD(pTreeNode));
            if(delayPostIncDec)
                PostIncListInsert(postIncList, false, &R_CHILD(pTreeNode));
            childPos = 1;
            is_postdec = 1;
            break;
        case NODE_PRE_DEC:
            generateDynamicMemoryInstruction(INST_LD, rReg, &R_CHILD(pTreeNode));
            emitAluInstruction(INST_SUB, true, 1, rReg, rReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, rReg, &R_CHILD(pTreeNode));
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&R_CHILD(pTreeNode), rReg);
            emitMemoryInstruction(INST_LDX, rReg, rReg, 0, NULL);
            break;
        case NODE_FUNCTION_CALL:
            generateCode(&R_CHILD(pTreeNode));
            emitAluInstruction(INST_MOV, false, 0, rReg, REG_R4, REG_NONE);
            break;
        default:
            //LOG_ERROR("Un-Implemented condition!\n");
            break;
    }

    if(opType == OP_MULTIPLY)
    {
        //Pass arguments to execute MUL function
        emitAluInstruction(INST_MOV, false, 0, REG_R4, lReg, REG_NONE);
        emitAluInstruction(INST_MOV, false, 0, REG_R5, rReg, REG_NONE);
        reg_et labelReg = getNextAvailableReg();
        emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, "FUNCTION_MUL");
        emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
        emitAluInstruction(INST_MOV, false, 0, destReg, REG_R4, REG_NONE);
        releaseReg(labelReg);
    }
    else if(opType == OP_DIVIDE)
    {
        //Pass arguments to execute MUL function
        emitAluInstruction(INST_MOV, false, 0, REG_R4, lReg, REG_NONE);
        emitAluInstruction(INST_MOV, false, 0, REG_R5, rReg, REG_NONE);
        reg_et labelReg = getNextAvailableReg();
        emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, "FUNCTION_DIV");
        emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
        emitAluInstruction(INST_MOV, false, 0, destReg, REG_R4, REG_NONE);
        releaseReg(labelReg);

    }
    else if (opType == OP_REMAIN)
    {
        //Pass arguments to execute MUL function
        emitAluInstruction(INST_MOV, false, 0, REG_R4, lReg, REG_NONE);
        emitAluInstruction(INST_MOV, false, 0, REG_R5, rReg, REG_NONE);
        reg_et labelReg = getNextAvailableReg();
        emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, "FUNCTION_DIV");
        emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
        emitAluInstruction(INST_MOV, false, 0, destReg, REG_R5, REG_NONE);
        releaseReg(labelReg);

    }
    else 
        emitAluInstruction(asmInstruction, false, 0, destReg, lReg, rReg);

    //Post Inc/Dec here if no assign was found during traverse
    if(!delayPostIncDec && is_postinc)
    {
        //rReg already has the value contained in the address of the right child
        //lreg already has the value contained in the address of the left child
        if(childPos == 1)
        {
            emitAluInstruction(INST_ADD, true, 1, rReg, rReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, rReg, &R_CHILD(pTreeNode));
        }
        else
        {
            emitAluInstruction(INST_ADD, true, 1, lReg, lReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, lReg, &L_CHILD(pTreeNode));
        }
        
    }

    if(!delayPostIncDec && is_postdec)
    {
        //rReg already has the value contained in the address of the right child
        //lreg already has the value contained in the address of the left child
        if(childPos == 1)
        {
            emitAluInstruction(INST_SUB, true, 1, rReg, rReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, rReg, &R_CHILD(pTreeNode));
        }
        else
        {
            emitAluInstruction(INST_SUB, true, 1, lReg, lReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, lReg, &L_CHILD(pTreeNode));
        }
        
    }

    releaseReg(lReg);
    releaseReg(rReg);

    return 0;
}



static int generateBooleanOperation(OperatorType_et operatorType, TreeNode_st *pTreeNode, reg_et destReg, reg_et lReg, reg_et rReg, bool is_root)
{
    bool allocTemp1 = (lReg == REG_NONE) ? 1 : 0;
    bool allocTemp2 = (rReg == REG_NONE) ? 1 : 0;

    reg_et tempReg1 = allocTemp1 ? getNextAvailableReg() : lReg;
    reg_et tempReg2 = allocTemp2 ? getNextAvailableReg() : rReg;

    if(!is_root)
    {
        switch (L_CHILD_TYPE(pTreeNode))
        {
            case NODE_INTEGER:
                emitMemoryInstruction(INST_LDI, tempReg1, REG_NONE, L_CHILD_DVAL(pTreeNode), NULL);
                break;
            case NODE_IDENTIFIER:
                generateDynamicMemoryInstruction(INST_LD, tempReg1, &L_CHILD(pTreeNode));
                break;
            case NODE_POINTER:
                generateDynamicMemoryInstruction(INST_LD, tempReg1, &L_CHILD(pTreeNode));
                emitMemoryInstruction(INST_LDX, tempReg1, tempReg1, 0, NULL);
                break;
            case NODE_ARRAY_INDEX:
                handleArrayIndexedExpressions(&L_CHILD(pTreeNode), tempReg1);
                emitMemoryInstruction(INST_LDX, tempReg1, tempReg1, 0, NULL);
                break;
            case NODE_FUNCTION_CALL:
                generateCode(&L_CHILD(pTreeNode));
                emitAluInstruction(INST_MOV, false, 0, tempReg1, REG_R4, REG_NONE);
            break;
            
            default:
                //LOG_ERROR("Un-Implemented condition!\n");
                break;
        }


        switch (R_CHILD_TYPE(pTreeNode))
        {
            case NODE_INTEGER:
                emitMemoryInstruction(INST_LDI, tempReg2, REG_NONE, R_CHILD_DVAL(pTreeNode), NULL);
                break;
            case NODE_IDENTIFIER:
                generateDynamicMemoryInstruction(INST_LD, tempReg2, &R_CHILD(pTreeNode));
                break;
            case NODE_POINTER:
                generateDynamicMemoryInstruction(INST_LD, tempReg2, &R_CHILD(pTreeNode));
                emitMemoryInstruction(INST_LDX, tempReg2, tempReg2, 0,NULL);
                break;
            case NODE_ARRAY_INDEX:
                handleArrayIndexedExpressions(&R_CHILD(pTreeNode), tempReg2);
                emitMemoryInstruction(INST_LDX, tempReg2, tempReg2, 0, NULL);
                break;
            case NODE_FUNCTION_CALL:
                generateCode(&R_CHILD(pTreeNode));
                emitAluInstruction(INST_MOV, false, 0, tempReg2, REG_R4, REG_NONE);
            break;
            
            default:
                //LOG_ERROR("Un-Implemented condition!\n");
                break;
        }
    }
    

    //Pre-load the value 1 to indicate that the condition is true if it doesnt change
    emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 1, NULL);

    
    if(operatorType == OP_LOGICAL_AND)
    {
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg1, REG_NONE);
        emitBranchInstruction(INST_BEQ, FALSE, getLabelCounter(FALSE));
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg2, REG_NONE);
        emitBranchInstruction(INST_BEQ, FALSE, getLabelCounter(FALSE));
        emitBranchInstruction(INST_BRA, TRUE, getLabelCounter(TRUE));
        emitLabelInstruction(FALSE, getPostIncLabelCounter(FALSE), NULL);
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0, NULL);
        emitLabelInstruction(TRUE, getPostIncLabelCounter(TRUE), NULL);


    }
    else if(operatorType == OP_LOGICAL_OR)
    {
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg1, REG_NONE);
        emitBranchInstruction(INST_BNE, TRUE, getLabelCounter(TRUE));
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg2, REG_NONE);
        emitBranchInstruction(INST_BNE, TRUE, getLabelCounter(TRUE));
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0, NULL);
        emitLabelInstruction(TRUE, getPostIncLabelCounter(TRUE), NULL);

    }
    else if (operatorType == OP_LOGICAL_NOT)
    {
        emitAluInstruction(INST_CMP, true, 0, REG_NONE, tempReg1, REG_NONE);
        emitBranchInstruction(INST_BNE, TRUE, getLabelCounter(TRUE));
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0, NULL);
        emitLabelInstruction(TRUE, getPostIncLabelCounter(TRUE), NULL);
    }
    else
    { //Cases: !=, ==, >=, <=, etc
        emitAluInstruction(INST_CMP, false, 0, REG_NONE, tempReg1, tempReg2);
        emitBranchInstruction(mapInstructionFromOperator(operatorType), SKIP, getLabelCounter(SKIP));
        emitMemoryInstruction(INST_LDI, destReg, REG_NONE, 0, NULL);
        emitLabelInstruction(SKIP, getLabelCounter(SKIP), NULL);      
    }
    
    if(allocTemp1) 
        releaseReg(tempReg1);
    if(allocTemp2) 
        releaseReg(tempReg2);
    return 0;
}


 static int handleRootBooleanNode(OperatorType_et rootNodeOpType, reg_et dreg, reg_et lReg, reg_et rReg)
 {
    generateBooleanOperation(rootNodeOpType, NULL, dreg, lReg, rReg, true);
 }


/// @brief function for emiting assign operations 
/// @param operatorType -> Type of assign(=, +=, <<=, &=,*x = &y, etc.)
/// @param pTreeNode -> current node being processed
/// @param destReg -> destiny register used for code emition
/// @return 
static int generateAssignOperation(OperatorType_et operatorType, TreeNode_st *pTreeNode, reg_et destReg)
{
    uint32_t leftAddr;
    uint32_t rightAddr;

    reg_et tempReg = getNextAvailableReg();
    reg_et lReg = getNextAvailableReg();

    bool is_postdec= 0;
    bool is_postinc= 0;


    //Templates for the Right childs of an assignement
    switch (R_CHILD_TYPE(pTreeNode))
    {
        case NODE_INTEGER:
            emitMemoryInstruction(INST_LDI, tempReg, REG_NONE, R_CHILD_DVAL(pTreeNode), NULL);
            break;
        case NODE_IDENTIFIER:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &R_CHILD(pTreeNode));
            break;
        case NODE_POINTER_CONTENT:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &R_CHILD(pTreeNode));
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0, NULL);
            break;
        case NODE_REFERENCE:
            generateDynamicMemoryInstruction(INST_LDI, tempReg, &R_CHILD(pTreeNode));
            break;
        case NODE_POST_INC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &R_CHILD(pTreeNode));
            is_postinc = 1;
            break;
        case NODE_PRE_INC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &R_CHILD(pTreeNode));
            emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, tempReg, &R_CHILD(pTreeNode));
            break;
        case NODE_POST_DEC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &R_CHILD(pTreeNode));
            is_postdec = 1;
            break;
        case NODE_PRE_DEC:
            generateDynamicMemoryInstruction(INST_LD, tempReg, &R_CHILD(pTreeNode));
            emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
            generateDynamicMemoryInstruction(INST_ST, tempReg, &R_CHILD(pTreeNode));
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&R_CHILD(pTreeNode), tempReg);
            emitMemoryInstruction(INST_LDX, tempReg, tempReg, 0, NULL);
            break;
        case NODE_FUNCTION_CALL:
            generateCode(&R_CHILD(pTreeNode));
            emitAluInstruction(INST_MOV, false, 0, tempReg, REG_R4, REG_NONE);
            break;
        default:
            //LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    //Templates for the left child of an assignement
    switch (L_CHILD_TYPE(pTreeNode))
    {
        case NODE_IDENTIFIER:
            if (operatorType != OP_ASSIGN)
            {
                generateDynamicMemoryInstruction(INST_LD, lReg, &L_CHILD(pTreeNode));
            }
            break;
        case NODE_POINTER_CONTENT:
            generateDynamicMemoryInstruction(INST_LD, destReg, &L_CHILD(pTreeNode));
            break;
        case NODE_ARRAY_INDEX:
            handleArrayIndexedExpressions(&L_CHILD(pTreeNode), destReg);
            break;
        default:
            //LOG_ERROR("Un-Implemented condition!\n");
            break;
    }


    //If its an assign with an Alu operation (+=, -=,..), generate the operation before the Store
    //Will need to halndle here the multiply, div and remaind diferently
    if (operatorType != OP_ASSIGN)
    {
        emitAluInstruction(mapInstructionFromAssignOp(operatorType), false, 0, lReg, lReg, tempReg);
    }

    //Templates for the left child of an assignement
    switch (L_CHILD_TYPE(pTreeNode))
    {
        case NODE_IDENTIFIER:
            if(operatorType != OP_ASSIGN)
                generateDynamicMemoryInstruction(INST_ST, lReg, &L_CHILD(pTreeNode));
            else
                generateDynamicMemoryInstruction(INST_ST, tempReg, &L_CHILD(pTreeNode));
            break;
        case NODE_POINTER_CONTENT:
            if(operatorType != OP_ASSIGN)
                emitMemoryInstruction(INST_STX, lReg, destReg, 0, NULL);
            else
                emitMemoryInstruction(INST_STX, tempReg, destReg, 0, NULL);
            break;
        case NODE_ARRAY_INDEX:
            if(operatorType != OP_ASSIGN)
                emitMemoryInstruction(INST_STX, lReg, destReg, 0, NULL);
            else
                emitMemoryInstruction(INST_STX, tempReg, destReg, 0, NULL);
            break;
        default:
            //LOG_ERROR("Un-Implemented condition!\n");
            break;
    }

    //Post Inc/Dec here if no assign was found during traverse
    if(!delayPostIncDec && is_postinc)
    {       
        emitAluInstruction(INST_ADD, true, 1, tempReg, tempReg, REG_NONE);
        generateDynamicMemoryInstruction(INST_ST, tempReg, &R_CHILD(pTreeNode)); 
    }
    if(!delayPostIncDec && is_postdec)
    {     
        emitAluInstruction(INST_SUB, true, 1, tempReg, tempReg, REG_NONE);
        generateDynamicMemoryInstruction(INST_ST, tempReg, &R_CHILD(pTreeNode)); 
    }

    releaseReg(tempReg);
    releaseReg(lReg);

    return 0;
}

static int parseOperatorNode(TreeNode_st *pTreeNode, reg_et dReg)
{
    OperatorType_et opType = (OperatorType_et) pTreeNode->nodeData.dVal;

    switch (opType)
    {
        case OP_PLUS:
        case OP_MINUS:
        case OP_RIGHT_SHIFT:
        case OP_LEFT_SHIFT:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_REMAIN:
        case OP_BITWISE_AND:
        case OP_BITWISE_NOT:
        case OP_BITWISE_OR:
        case OP_BITWISE_XOR:
            generateAluOperation(pTreeNode, dReg);
            break;
        case OP_GREATER_THAN:
        case OP_LESS_THAN_OR_EQUAL:
        case OP_GREATER_THAN_OR_EQUAL:
        case OP_LESS_THAN:
        case OP_EQUAL:
        case OP_NOT_EQUAL:
        case OP_LOGICAL_AND:
        case OP_LOGICAL_OR:
        case OP_LOGICAL_NOT:
            generateBooleanOperation(opType, pTreeNode, dReg, REG_NONE, REG_NONE, false);
            break;
        case OP_ASSIGN:
        case OP_PLUS_ASSIGN:
        case OP_MINUS_ASSIGN:
        case OP_MODULUS_ASSIGN:
        case OP_LEFT_SHIFT_ASSIGN:
        case OP_RIGHT_SHIFT_ASSIGN:
        case OP_BITWISE_AND_ASSIGN:
        case OP_BITWISE_OR_ASSIGN:
        case OP_BITWISE_XOR_ASSIGN:
        case OP_MULTIPLY_ASSIGN:
        case OP_DIVIDE_ASSIGN:
            generateAssignOperation(opType, pTreeNode, dReg);
            releaseReg(dReg);
            break;
        case OP_SIZEOF:
            break;
        case OP_NEGATIVE:
            break;
    }

    return 0;
}


/// \brief Different ParsesNode because it allows to parse the terminal nodes (INTEGER, IDENTIFIER, POINTER_CONTENT,..) in their own "case" of the big switch
/// Although, it has to receive additional params  
/// \param pCurrentNode Pointer to the current Node to be parsed
/// \param parentNodeType The type of the parent of the currentNode
/// \param isLeftInherited 1 if the currentNode is at the left of its parent, 0 if its at the right of the parent
/// \return 0 if success; -EINVAL in pCurrentNode is NULL
static int parseNode(TreeNode_st *pCurrentNode, NodeType_et parentNodeType, OperatorType_et parentOperatorType, bool isLeftInherited)
{
    reg_et lReg;
    reg_et rReg;
    reg_et dReg;

    OperatorType_et CurrentNodeOpType = (OperatorType_et) pCurrentNode->nodeData.dVal;

    if (!IS_TERMINAL_NODE(pCurrentNode->nodeType) && NODE_TYPE(pCurrentNode) == NODE_OPERATOR && NODE_OP_TYPE(pCurrentNode) != OP_ASSIGN)
    {
        //If we enter a non terminal node we allocate a new dReg for that operation
        dReg = getNextAvailableReg();
        lReg = REG_NONE;
        rReg = REG_NONE;
    }
    
    if(IS_TERMINAL_NODE(pCurrentNode->nodeType) && IS_CONDITIONAL_NODE(parentNodeType))
        dReg = getNextAvailableReg();

    if(parentNodeType == NODE_ARRAY_INDEX)
        arrayIndexRegSave = dReg;

    if (!pCurrentNode)
        return -EINVAL;


    switch (pCurrentNode->nodeType)
    {
        case NODE_OPERATOR:

            if(IS_ASSIGN_OPERATION(CurrentNodeOpType))
                delayPostIncDec = 1;

            if (!IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode)))
            {
                //Gen Code for Left Child If its not a terminal node
                generateCode(&pCurrentNode->pChilds[0]);
                lReg = dRegSave;
            }
            //There are nodes with only 1 left child so before we genCode for the right one we need to verify if it exists in order to not get SegFault Error
            if (!IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode)))
            {
                //Gen Code for Right Child If its not terminal node
                generateCode(&pCurrentNode->pChilds[1]);
                rReg = dRegSave;
            }

            //TERMINAL NODE CASES
            //Should only enter these cases when we find Terminal nodes and when we start going upwards in the AST
            if (IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode)) && IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode)))
            {
                //If both childs are terminals, parse the node to generate the ALU operation
                parseOperatorNode(pCurrentNode, dReg);
                dRegSave = dReg;
            }
            else if ((IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode))) && (!IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode))))
            {
                //If Left child is a terminal node and Right child is not
                //Save lReg and dReg because we will enter a new calling stack
                rRegSave = rReg;  
                dRegSave = dReg;
                parseNode(&pCurrentNode->pChilds[0], NODE_OPERATOR, CurrentNodeOpType, true);
                releaseReg(rReg); 
            }
            else if ((IS_TERMINAL_NODE(R_CHILD_TYPE(pCurrentNode))) && (!IS_TERMINAL_NODE(L_CHILD_TYPE(pCurrentNode))))
            {
                //If Right child is a terminal node and Left child is not
                //Save lReg and dReg because we will enter a new calling stack
                lRegSave = lReg;
                dRegSave = dReg;
                parseNode(&pCurrentNode->pChilds[1], NODE_OPERATOR, CurrentNodeOpType, false);
                releaseReg(lReg);
            }
            else
            {
                //If both childs are Non-Terminals
                if(IS_ALU_OPERATION(CurrentNodeOpType))
                    emitAluInstruction(mapInstructionFromOperator(CurrentNodeOpType), false, 0, dReg, lReg, rReg);

                else if(IS_BOOLEAN_OPERATION(CurrentNodeOpType))
                    handleRootBooleanNode(CurrentNodeOpType, dReg, lReg, rReg);

                dRegSave = dReg;
                releaseReg(lReg);
                releaseReg(rReg);
            }

            //If there are Post Increments or Decrements to emit, handle it here
            if(IS_ASSIGN_OPERATION(CurrentNodeOpType))
            {
                reg_et auxReg = getNextAvailableReg();
                handlePostIncDecOperations(auxReg);
                releaseReg(auxReg);
            }

            break;
        case NODE_IDENTIFIER:
        
            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode); 

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, lReg);
                    else
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Will always be left inherited so the value to assign is always at rReg
                rReg = rRegSave;


                //If its an assign with an operation (+=, -=), GenCode for the operation
                if (parentOperatorType != OP_ASSIGN)
                {
                    reg_et auxReg = getNextAvailableReg();
                    generateDynamicMemoryInstruction(INST_LD, auxReg, pCurrentNode); 
                    emitAluInstruction(mapInstructionFromAssignOp(parentOperatorType), false, 0, rReg, auxReg, rReg);
                    releaseReg(auxReg);
                }

                generateDynamicMemoryInstruction(INST_ST, rReg, pCurrentNode); 
                
                releaseReg(dReg);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LD, tempreg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            else //Used for Simple Conditions if(x), while(x)...
            {
                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);
                dRegSave = dReg;
            }

            break;
        case NODE_INTEGER:

            //Load saved registers
            //rReg is not used in imm operation so in case it is left inherited we reload the rRegSave to the lReg  
            lReg = isLeftInherited ? rRegSave : lRegSave;

            //If the integer is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Foi necessário colocar aqui a mesma verificação que está na func generateALUOperation (se for operaçao menos trocar para ADD e negar o imediato)
                if ((parentOperatorType == OP_MINUS) && isLeftInherited)
                {
                    uint32_t immVal = pCurrentNode->nodeData.dVal;
                    emitAluInstruction(INST_ADD, true, -immVal, dReg, lReg, REG_NONE);
                    emitAluInstruction(INST_SUB, false, 0, dReg, REG_R0, dReg);
                }
                else
                {
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                    {
                        uint32_t immVal = pCurrentNode->nodeData.dVal;
                        reg_et auxMulReg = getNextAvailableReg();
                        if(isLeftInherited)
                        {
                            rReg = rRegSave;
                            emitMemoryInstruction(INST_LDI, auxMulReg, REG_NONE, immVal, NULL);
                            handleMulDivNode(parentOperatorType, dReg, auxMulReg, lReg);
                        }
                        else
                        {
                            lReg = lRegSave;
                            emitMemoryInstruction(INST_LDI, auxMulReg, REG_NONE, immVal, NULL);
                            handleMulDivNode(parentOperatorType, dReg, lReg, auxMulReg);
                        }
                        releaseReg(auxMulReg);          
                    }
                    else
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), true, pCurrentNode->nodeData.dVal, dReg, lReg, REG_NONE);
                }

            }
            else if(parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LDI, tempreg, REG_NONE, pCurrentNode->nodeData.dVal, NULL);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                     
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            else //Used for Simple Conditions if(1), while(1)...
            {
                emitMemoryInstruction(INST_LDI, dReg, REG_NONE, pCurrentNode->nodeData.dVal, NULL);
                dRegSave = dReg;
                dRegSave = dReg;
                dRegSave = dReg;
            }

            break;
        case NODE_IF:
            
            parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode),(OperatorType_et) L_CHILD_DVAL(pCurrentNode), true);
            
            emitAluInstruction(INST_CMP, true, 0, REG_NONE, dRegSave, REG_NONE);

            //If there is no "else", jump to the exit
            if (pCurrentNode->childNumber > 2)
                emitBranchInstruction(INST_BEQ, IF_FALSE, getLabelCounter(IF_FALSE));
            else
                emitBranchInstruction(INST_BEQ, IF_EXIT, getLabelCounter(IF_EXIT));

            if (pCurrentNode->childNumber > 1)
                generateCode(&pCurrentNode->pChilds[1]);

            //If statement with else
            if (pCurrentNode->childNumber > 2)
            {
                emitBranchInstruction(INST_BRA, IF_EXIT, getLabelCounter(IF_EXIT));
                emitLabelInstruction(IF_FALSE, getPostIncLabelCounter(IF_FALSE), NULL);
                generateCode(&pCurrentNode->pChilds[2]);
            }

            emitLabelInstruction(IF_EXIT, getPostIncLabelCounter(IF_EXIT), NULL);

            break;
        case NODE_WHILE:
            emitLabelInstruction(WHILE_START, getLabelCounter(WHILE_START), NULL);
            parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode),(OperatorType_et) L_CHILD_DVAL(pCurrentNode), true);
            emitAluInstruction(INST_CMP, true, 0, REG_NONE, dRegSave, REG_NONE);
            emitBranchInstruction(INST_BEQ, WHILE_EXIT, getLabelCounter(WHILE_EXIT));

            //While can be empty
            if (pCurrentNode->childNumber > 1)
                generateCode(&R_CHILD(pCurrentNode));

            emitBranchInstruction(INST_BRA, WHILE_START, getPostIncLabelCounter(WHILE_START));
            emitLabelInstruction(WHILE_EXIT, getPostIncLabelCounter(WHILE_EXIT), NULL);

            break;
        case NODE_DO_WHILE:
            emitLabelInstruction(WHILE_START, getLabelCounter(WHILE_START), NULL);
            
            //Do can be empty
            //Gen code inside do
            if (pCurrentNode->childNumber > 1)
                generateCode(&R_CHILD(pCurrentNode));

            //Generate while condition
            parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode),(OperatorType_et) L_CHILD_DVAL(pCurrentNode), true);
            emitAluInstruction(INST_CMP, true, 0, REG_NONE, dRegSave, REG_NONE);
            emitBranchInstruction(INST_BNE, WHILE_START, getPostIncLabelCounter(WHILE_START));

            break;
        case NODE_BREAK:
        
            if(parentNodeType != NODE_DEFAULT)
                emitBranchInstruction(INST_BRA, CASE_EXIT, getLabelCounter(CASE_EXIT));
        
            break;
        case NODE_SWITCH:

            //Generate code for expression inside switch     
             parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode),(OperatorType_et) L_CHILD_DVAL(pCurrentNode), true);

            TreeNode_st *pCases, pDefault;
            pCases = &pCurrentNode->pChilds[1];

            int keepCounter = labelCounters[CASE];

            while(pCases->pSibling != NULL )
            {
                reg_et tempreg = getNextAvailableReg(); 
                emitMemoryInstruction(INST_LDI, tempreg, REG_NONE, pCases->nodeData.dVal, NULL);
            
                emitAluInstruction(INST_CMP, false, 0, REG_NONE, dRegSave, tempreg);
                emitBranchInstruction(INST_BEQ, CASE, getPostIncLabelCounter(CASE));
                
                releaseReg(tempreg);                

                if(pCases->pSibling->nodeType == NODE_DEFAULT)
                {
                    emitBranchInstruction(INST_BRA, DEFAULT, getLabelCounter(DEFAULT));  
                }
                else if(pCases->pSibling == NULL)
                    emitBranchInstruction(INST_BRA, CASE_EXIT, getLabelCounter(CASE_EXIT));  

                pCases = pCases->pSibling;
            }
            releaseReg(dRegSave);

            labelCounters[CASE]= keepCounter;
            
            generateCode(&R_CHILD(pCurrentNode));
            
            emitLabelInstruction(CASE_EXIT, getPostIncLabelCounter(CASE_EXIT), NULL);

            break;
        case NODE_CASE:

            //Emit Label for Case
            emitLabelInstruction(CASE, getPostIncLabelCounter(CASE), NULL);
            //Gen the case Code
            //Code inside case can be empty
            if(&L_CHILD(pCurrentNode) != NULL)
                generateCode(&L_CHILD(pCurrentNode));
                  
            break;
        case NODE_DEFAULT:

            emitLabelInstruction(DEFAULT, getPostIncLabelCounter(DEFAULT), NULL);
            generateCode(&L_CHILD(pCurrentNode));
            break;
        case NODE_REFERENCE:
            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                generateDynamicMemoryInstruction(INST_LDI, dReg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LDI, tempreg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }

            break;
        case NODE_POINTER_CONTENT:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0, NULL);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
                //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Will always be left inherited so the value to assign is always at rReg
                rReg = rRegSave;

                //If its an assign with an operation (+=, -=), GenCode for the operation
                if (parentOperatorType != OP_ASSIGN)
                {
                    //LOG_ERROR("Not implemented because its not suported by the parser");
                }
                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);
                emitMemoryInstruction(INST_STX, rReg, dReg, 0,NULL);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LD, tempreg, pCurrentNode);
                emitMemoryInstruction(INST_LDX, tempreg, tempreg, 0, NULL);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                releaseReg(tempreg);
            }
            else //Used for Simple Conditions if(*x), while(*x)...
            {
                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0, NULL);
                dRegSave = dReg;
            }

            break;
        case NODE_POST_DEC:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }

                //If an assign wasnt found before, do the post inc here
                if(!delayPostIncDec)
                {
                    emitAluInstruction(INST_SUB, true, 1, dReg, dReg, REG_NONE);
                    generateDynamicMemoryInstruction(INST_ST, dReg, pCurrentNode);
                }
                else
                    PostIncListInsert(postIncList, true, pCurrentNode);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LD, tempreg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }

                emitAluInstruction(INST_SUB, true, 1, tempreg, tempreg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tempreg, pCurrentNode);
                releaseReg(tempreg);
            }
                //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //its a dec statement (eg i--;)
            {
                reg_et tReg = getNextAvailableReg();

                generateDynamicMemoryInstruction(INST_LD, tReg, pCurrentNode);
                emitAluInstruction(INST_SUB, true, 1, tReg, tReg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tReg, pCurrentNode);
                releaseReg(tReg);
            }
            break;
        case NODE_PRE_DEC:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);
                emitAluInstruction(INST_SUB, true, 1, dReg, dReg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, dReg, pCurrentNode);


                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LD, tempreg, pCurrentNode);
                emitAluInstruction(INST_SUB, true, 1, tempreg, tempreg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tempreg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }

                releaseReg(tempreg);
            }
            //If the identifier is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //its a dec statement (eg --i;)
            {
                reg_et tReg = getNextAvailableReg();

                generateDynamicMemoryInstruction(INST_LD, tReg, pCurrentNode);
                emitAluInstruction(INST_SUB, true, 1, tReg, tReg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tReg, pCurrentNode);
                releaseReg(tReg);
            }
            break;
        case NODE_POST_INC:

            //If the Identifier is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                    
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
                //If an assign wasnt found before, do the post inc here
                if(!delayPostIncDec)
                {
                    emitAluInstruction(INST_ADD, true, 1, dReg, dReg, REG_NONE);
                    generateDynamicMemoryInstruction(INST_ST, dReg, pCurrentNode);
                }
                else
                    PostIncListInsert(postIncList, true, pCurrentNode);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LD, tempreg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }

                emitAluInstruction(INST_ADD, true, 1, tempreg, tempreg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tempreg, pCurrentNode);
                releaseReg(tempreg);
            }
            //If is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //Is just an increment statement (ex i++;)
            {
                reg_et tReg = getNextAvailableReg();

                generateDynamicMemoryInstruction(INST_LD, tReg, pCurrentNode);
                emitAluInstruction(INST_ADD, true, 1, tReg, tReg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tReg, pCurrentNode);
                releaseReg(tReg);
            }

            break;
        case NODE_PRE_INC:

            //If is a child of an ALU_OPERATION (+, -, *, /, %, <<, >>)
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;

                generateDynamicMemoryInstruction(INST_LD, dReg, pCurrentNode);
                emitAluInstruction(INST_ADD, true, 1, dReg, dReg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, dReg, pCurrentNode);


                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                generateDynamicMemoryInstruction(INST_LD, tempreg, pCurrentNode);
                emitAluInstruction(INST_ADD, true, 1, tempreg, tempreg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, dReg, pCurrentNode);

                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                
                releaseReg(tempreg);
            }
            //If is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                //Should never enter here
            }
            else //its an inc statement (eg ++i)
            {
                reg_et tReg = getNextAvailableReg();

                generateDynamicMemoryInstruction(INST_LD, tReg, pCurrentNode);
                emitAluInstruction(INST_ADD, true, 1, tReg, tReg, REG_NONE);
                generateDynamicMemoryInstruction(INST_ST, tReg, pCurrentNode);
                releaseReg(tReg);
            }

            break;
        case NODE_ARRAY_INDEX:
            
            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;             
                handleArrayIndexedExpressions(pCurrentNode, dReg);
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0, NULL);

                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, dReg, rReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, dReg, rReg);
                }
                else
                {
                    lReg = lRegSave;
                    if(parentOperatorType == OP_MULTIPLY || parentOperatorType == OP_DIVIDE || parentOperatorType == OP_REMAIN)
                        handleMulDivNode(parentOperatorType, dReg, lReg, dReg);
                    else 
                        emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dReg, lReg, dReg);
                }
            }
            //If the array is a child of an ASSIGN_OPERATION (=, +=, -=, *=, /=, %=, |=, <<=, >>=, &=, ^=,)
            else if (parentNodeType == NODE_OPERATOR && IS_ASSIGN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                //Dreg will have the value of the memory location of array[exp]
                handleArrayIndexedExpressions(pCurrentNode, dReg);

                //Will always be left inherited, if it was left inherited then the left child would also be a terminal one and that case is handled in ParseAssignOperation()
                if (isLeftInherited)
                {
                    rReg = rRegSave;
                    //If array child is at the left we need to store to it
                    emitMemoryInstruction(INST_STX, rReg, dReg, 0, NULL);
                }

            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {
                dReg = dRegSave;
                reg_et tempreg = getNextAvailableReg(); 
                handleArrayIndexedExpressions(pCurrentNode, tempreg);
                emitMemoryInstruction(INST_LDX, tempreg, tempreg, 0,NULL);
                
                if (isLeftInherited)
                {
                    rReg = rRegSave;                  
                    handleRootBooleanNode(parentOperatorType, dReg, tempreg, rReg);
                }
                else
                {
                    lReg = lRegSave;       
                    handleRootBooleanNode(parentOperatorType, dReg, lReg, tempreg);
                }
                
                releaseReg(tempreg);
            }
            else //used for while(array[x]), if (array[x])
            {
                handleArrayIndexedExpressions(pCurrentNode, dReg);
                emitMemoryInstruction(INST_LDX, dReg, dReg, 0,NULL);
                dRegSave = dReg;
            }

            break;
        case NODE_VAR_DECLARATION:
            // Reserve stack space for temporary variables
            if(pCurrentNode->pSymbol->scopeLocation == FUNCTION_SCOPE)
            {
                emitAluInstruction(INST_SUB, true, 1, REG_R3, REG_R3, REG_NONE);
            } 
            break;
        case NODE_FUNCTION:
            
            // Function node with no body
            if(pCurrentNode->childNumber != 3)
                break; 
            
            // Emit function Label
            emitLabelInstruction(FUNCTION_NAME, -1, pCurrentNode->nodeData.sVal);

            // Generate Body
            generateCode(pCurrentNode->pChilds + 2);
          
            // Emit Instruction to return for void functions as those won't have return statements
            if(pCurrentNode->pChilds[0].nodeVarType != TYPE_VOID)                     
                 break;  
                               
            //Copy FP to SP
            emitAluInstruction(INST_MOV, false, 0, REG_R3, REG_R2, REG_NONE);

            // Restore R1
            emitAluInstruction(INST_SUB, true, 1, REG_R3, REG_R3, REG_NONE);       
            pop(REG_R1);

            // Restore Frame Pointer
            pop(REG_R2);

            // Jump to addr in R1 
            emitJumpInstruction(INST_JMP, REG_R1, REG_NONE, 0);

            break;
        case NODE_FUNCTION_CALL:

            //In case this is an arithmetic calculation using a function call (eg: x = foo + 1)
            //We will now calculate the function parameters and will lose the register to where we need to Place the arithmetic result
            //So we save it here
            reg_et SaveOperationDestReg = dRegSave;
            reg_et SaveOperationRightReg = rRegSave;
            reg_et SaveOperationleftReg = lRegSave;
          
            TreeNode_st *pParameter = &pCurrentNode->pChilds[0];
            
            
            //Calculate arguments and push them to the stack
            for (size_t i = 0; i < pCurrentNode->pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber; i++)
            {
                if(pParameter)
                {
                    parseNode(pParameter, NODE_FUNCTION_CALL, OP_NOT_DEFINED, true);
                    push(dRegSave);
                    pParameter = pParameter->pSibling;
                }
            }
             
            // Push Register R2 - Frame Pointer/Control Link
            push(REG_R2);

            //Copy SP to FP
            emitAluInstruction(INST_MOV, false, 0, REG_R2, REG_R3, REG_NONE);

            // Push Register R1 - return address
            push(REG_R1);
            
            //Emit the jump to the function      
            reg_et labelReg = getNextAvailableReg();
            emitMemoryInstruction(INST_LDI, labelReg, REG_NONE, 0, pCurrentNode->nodeData.sVal);
            emitJumpInstruction(INST_JMPL, REG_R1, labelReg, 0);
            releaseReg(labelReg);
            

            //Pop all arguments
            emitAluInstruction(INST_ADD, true, pCurrentNode->pSymbol->symbolContent_u.SymbolFunction_s.parameterNumber, REG_R3, REG_R3, REG_NONE);

            

            dRegSave = SaveOperationDestReg;
            rRegSave = SaveOperationRightReg;
            lRegSave = SaveOperationleftReg;

            if (parentNodeType == NODE_OPERATOR && IS_ALU_OPERATION(parentOperatorType))
            {
                if (isLeftInherited)
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dRegSave, REG_R4, rRegSave);
                else
                    emitAluInstruction(mapInstructionFromOperator(parentOperatorType), false, 0, dRegSave, lRegSave, REG_R4);
            }
            else if (parentNodeType == NODE_OPERATOR && IS_BOOLEAN_OPERATION(parentOperatorType))
            {

                if (isLeftInherited)          
                    handleRootBooleanNode(parentOperatorType, dRegSave, REG_R4, rRegSave);       
                else   
                    handleRootBooleanNode(parentOperatorType, dRegSave, lRegSave, REG_R4);
            }
            else if(IS_CONDITIONAL_NODE(parentNodeType))
            {
                emitAluInstruction(INST_MOV, false, 0, dRegSave, REG_R4, REG_NONE);
            }

            break;

        case NODE_RETURN:           
            //Return of type void will have no child
            if(&L_CHILD(pCurrentNode) != NULL)
            {
                parseNode(&L_CHILD(pCurrentNode), NODE_TYPE(pCurrentNode), OP_NOT_DEFINED, true);
                // Place return values in R4
                emitAluInstruction(INST_MOV, false, 0, REG_R4, dRegSave, REG_NONE);
            }

            //Copy FP to SP
            emitAluInstruction(INST_MOV, false, 0, REG_R3, REG_R2, REG_NONE);

            // Restore R1
            emitAluInstruction(INST_SUB, true, 1, REG_R3, REG_R3, REG_NONE);       
            pop(REG_R1);

            // Restore Frame Pointer
            pop(REG_R2);            

            // Instruction to return to program flow before call
            emitJumpInstruction(INST_JMP, REG_R1, REG_NONE, 0);
            break;

        case NODE_PARAMETER:
            break;
        case NODE_NULL:
            break;
        case NODE_END_SCOPE:
            break;
        case NODE_START_SCOPE:
            break;
        case NODE_TYPE:
            break;
        case NODE_SIGN:
            break;
        case NODE_MISC:
            break;
        case NODE_VISIBILITY:
            break;
        case NODE_CONTINUE:
            break;
        case NODE_MODIFIER:
            break;
        case NODE_ARRAY_DECLARATION:
            // Reserve stack space for temporary array variables
            if(pCurrentNode->pSymbol->scopeLocation == FUNCTION_SCOPE)
            {
                emitAluInstruction(INST_SUB, true, R_CHILD_DVAL(pCurrentNode), REG_R3, REG_R3, REG_NONE);
            } 
            break;
        case NODE_TYPE_CAST:
            break;
        case NODE_POINTER:
            break;
        case NODE_GOTO:
            break;
        case NODE_LABEL:
            break;
        case NODE_TERNARY:
            break;
        case NODE_STRING:
            break;
        case NODE_FLOAT:
            break;
        case NODE_CHAR:
            break;
        case NODE_STRUCT:
            break;
    }

    if(IS_CONDITIONAL_NODE(parentNodeType))
    {
        releaseReg(dReg);
    }
    return 0;
}


/// \brief This function gets the first available register of the working register list
/// \return Register number or REG_NONE if no register is available
static reg_et getNextAvailableReg()
{
    for (size_t i = 0; i < NOF_SCRATCH_REGISTER; ++i)
    {
        if (regStateList[i].isFree)
        {
            regStateList[i].isFree = false;
            return regStateList[i].regName;
        }
    }

    //LOG_ERROR("No register available!\n");
    return REG_NONE;
}

/// \brief This function tries to release a previously allocated register
/// \param reg Enum representing the register that should be released
/// \return -EPERM if the passed register is already free, -ENODATA if the passed register was not found on the register
/// list, returns 0 on success
static int releaseReg(reg_et reg)
{
    for (size_t i = 0; i < NOF_SCRATCH_REGISTER; ++i)
    {
        if (regStateList[i].regName == reg)
        {
            if (regStateList[i].isFree)
            {
                //LOG_ERROR("Trying to release already freed register!\n");
                return -EPERM;
            }

            regStateList[i].isFree = true;
            return 0;
        }
    }

    return -ENODATA;
}

/// @brief Function to push registers to stack. Updates Stack Pointer
/// @warning It assumes stack was correctly built and stack management is conducted properly,
/// as such, has no safeguards
/// @param reg register to save to stack
static void push(reg_et reg)
{
    emitAluInstruction(INST_SUB, true, 1, REG_R3, REG_R3, REG_NONE);
    emitMemoryInstruction(INST_STX, reg, REG_R3, 0, NULL);
}

/// @brief Function to pop registers from stack. Updates Stack Pointer
/// @warning It assumes stack was correctly built and stack management is conducted properly,
/// as such, has no safeguards
/// @param reg register to get from stack
static void pop(reg_et reg)
{
    emitMemoryInstruction(INST_LDX, reg, REG_R3, 0, NULL);
    emitAluInstruction(INST_ADD, 1, true, REG_R3, REG_R3, REG_NONE);
}



static int generateDivision()
{
    int ret = 0;

    emitLabelInstruction(FUNCTION_NAME, -1, "DIV");

    reg_et regQuocient = getNextAvailableReg();
    reg_et regRemainder = getNextAvailableReg();
    reg_et regCondition = getNextAvailableReg();
    reg_et regTemp1 = getNextAvailableReg();
    reg_et regTemp2 = getNextAvailableReg();

    // Push dos registos acima
    
    push(regQuocient);
    push(regRemainder);
    push(regCondition);
    push(regTemp1);
    push(regTemp2);

    ret = emitMemoryInstruction(INST_LDI, regQuocient, REG_NONE, 0, NULL);
    ret |= emitMemoryInstruction(INST_LDI, regRemainder, REG_NONE, 0, NULL);

    for (size_t i = 0; i < 32; i++)
    {
        ret |= emitAluInstruction(INST_RR, 1, (31 - i), regTemp1, REG_R4, REG_NONE);
        ret |= emitAluInstruction(INST_AND, 1, 1, regTemp1, regTemp1, REG_NONE);
        ret |= emitAluInstruction(INST_RL, 1, 1, regTemp2, regRemainder, REG_NONE);
        ret |= emitAluInstruction(INST_OR, 0, 0, regRemainder, regTemp1, regTemp2);

        ret |= emitAluInstruction(INST_SUB, 0, 0, regCondition, regRemainder, REG_R5);
        emitBranchInstruction(INST_BGE, SKIP_DIV_BIT, getLabelCounter(SKIP_DIV_BIT));
        ret |= emitAluInstruction(INST_SUB, 0, 0, regRemainder, regRemainder, REG_R5);
        ret |= emitMemoryInstruction(INST_LDI, regTemp1, 0, 1, NULL);
        ret |= emitAluInstruction(INST_RL, 1, (31 - i), regTemp1, regTemp1, REG_NONE);
        ret |= emitAluInstruction(INST_OR, 0, 0, regQuocient, regQuocient, regTemp1);

        emitLabelInstruction(SKIP_DIV_BIT, getPostIncLabelCounter(SKIP_DIV_BIT), NULL);

    }

    // Load Quocient and Remainder to return registers
    ret |=  emitAluInstruction(INST_MOV, false, 0, REG_R4, regQuocient, REG_NONE);
    ret |=  emitAluInstruction(INST_MOV, false, 0, REG_R5, regRemainder, REG_NONE);

    releaseReg(regQuocient);
    releaseReg(regRemainder);
    releaseReg(regCondition);
    releaseReg(regTemp1);
    releaseReg(regTemp2);
    
    pop(regTemp2);
    pop(regTemp1);
    pop(regCondition);
    pop(regRemainder);
    pop(regQuocient);
    
    return ret;
}

static int generateMultiplication()
{
    int ret = 0;


    emitLabelInstruction(FUNCTION_NAME, -1, "MUL");
    
    reg_et regResult = getNextAvailableReg();
    reg_et regCondition = getNextAvailableReg();

    push(regResult);
    push(regCondition);
    
    ret = emitMemoryInstruction(INST_LDI, regResult, REG_NONE, 0, NULL);

    // Emit all 32 iterations
    for (size_t i = 0; i < 32; i++)
    {
        //Label = SKIP_MUL_ADD_BITi

        ret |= emitAluInstruction(INST_ADD, 1, 1, regCondition, REG_R5, REG_NONE);
        ret |= emitAluInstruction(INST_CMP, 1, 0, REG_NONE, regCondition, REG_NONE);
        
        emitBranchInstruction(INST_BNE, SKIP_MUL_ADD_BIT, getLabelCounter(SKIP_MUL_ADD_BIT));  
        ret |= emitAluInstruction(INST_ADD, 0, 0, regResult, regResult, REG_R4);

        emitLabelInstruction(SKIP_MUL_ADD_BIT, getPostIncLabelCounter(SKIP_MUL_ADD_BIT), NULL);

        ret |= emitAluInstruction(INST_RL, 1, 1, REG_R4, REG_R4, REG_NONE);
        ret |= emitAluInstruction(INST_RR, 1, 1, REG_R5, REG_R5, REG_NONE);
    }

    // Move result to return register
    ret |=  emitAluInstruction(INST_MOV, false, 0, REG_R4, regResult, REG_NONE);

    releaseReg(regResult);
    releaseReg(regCondition);

    pop(regCondition);
    pop(regResult);
     
    return ret;
}


