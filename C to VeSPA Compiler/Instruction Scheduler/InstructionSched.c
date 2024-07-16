#include "InstructionSched.h"

MnemonicMap mnemonicTable[] = {
    {"NOP", OP_NOP}, {"ADD", OP_ADD}, {"SUB", OP_SUB},   {"OR", OP_OR},
    {"AND", OP_AND}, {"NOT", OP_NOT}, {"XOR", OP_XOR},   {"CMP", OP_CMP},
    {"RR" , OP_RR},  {"RL" , OP_RL},  {"MOV", OP_MOV},  
    {"BRA", OP_BXX}, {"BCC", OP_BXX}, {"BVC", OP_BXX}, {"BEQ", OP_BXX}, 
    {"BGE", OP_BXX}, {"BGT", OP_BXX}, {"BNV", OP_BXX}, {"BCS", OP_BXX}, 
    {"BVS", OP_BXX}, {"BNE", OP_BXX}, {"BLT", OP_BXX}, {"BLE", OP_BXX}, 
    {"BMI", OP_BXX}, {"JMP", OP_JMP}, {"JML", OP_JMP},   {"LD", OP_LD},     
    {"LDI", OP_LDI}, {"LDX", OP_LDX}, {"ST", OP_ST},     {"STX", OP_STX},   
    {"RET", OP_RET}, {"HLT", OP_HLT}
};


const int MNEMONIC_COUNT = sizeof(mnemonicTable) / sizeof(mnemonicTable[0]);

/**
 * @brief Retrieves the value associated with a given mnemonic.
 *
 * This function searches for a mnemonic in the mnemonicTable array and returns its corresponding value.
 *
 * @param mnemonic The mnemonic to search for. It should be a null-terminated string.
 * @return The value associated with the mnemonic if found, otherwise NO_OPCODE.
 */
int getMnemonicValue(const char *mnemonic){
    char trimmedMnemonic[5] = {0};
    strncpy(trimmedMnemonic, mnemonic, 4); // Copy only the first three characters to ensure no trailing space issues
    trimmedMnemonic[4] = '\0'; // Null-terminate to be safe

    for (int i = 0; i < MNEMONIC_COUNT; i++) {
        if (strcmp(mnemonicTable[i].mnemonic, trimmedMnemonic) == 0) {
            return mnemonicTable[i].value;
        }
    }
    return NO_OPCODE;
}

/**
 * @brief Checks if the given opcode corresponds to an ALU operation.
 *
 * This function determines whether the opcode corresponds to an ALU (Arithmetic Logic Unit) operation.
 *
 * @param opcode The opcode value to check.
 * @return true if the opcode is an ALU operation, false otherwise.
 */
bool isAluOperation(int opcode) {
    return opcode >= OP_ADD && opcode <= OP_MOV;
}

/**
 * @brief Parse every element that will be needed to classify each instruction.
 *
 * This function parses the given line and extracts the mnemonic and operands of an instruction.
 * It determines the type of the instruction and assigns the corresponding values to the Instruction_st structure.
 *
 * @param line The line of code to parse.
 * @param inst Pointer to the Instruction_st structure to store the parsed information.
 */
void parseInstruction(const char *line, Instruction_st *inst){
    char mnemonic[10];
    
    strncpy(inst->line, line, sizeof(inst->line) - 1);
    inst->line[sizeof(inst->line) - 1] = '\0';
    
    if(sscanf(line, "%3s R%d, #%d", mnemonic, &inst->operands[0], &inst->operands[1]) == 3){
        inst->type = TYPE_IMMEDIATE;
        inst->mnemonicValue = getMnemonicValue(mnemonic);
        inst->operands[1] = NO_OPERAND;
        inst->operands[2] = NO_OPERAND;
        if(inst->mnemonicValue == OP_JMP)
            inst->type = TYPE_END_BLOCK;
    }
    
    else if(sscanf(line, "%3s R%d, R%d, #%d", mnemonic, &inst->operands[0], &inst->operands[1], &inst->operands[2]) == 4){
        inst->type = TYPE_IMMEDIATE;
        inst->mnemonicValue = getMnemonicValue(mnemonic);
        inst->operands[2] = NO_OPERAND;
        if(inst->mnemonicValue == OP_JMP)
            inst->type = TYPE_END_BLOCK;
    }
    
    else if(sscanf(line, "%3s R%d, R%d, R%d", mnemonic, &inst->operands[0], &inst->operands[1], &inst->operands[2]) == 4){
        inst->type = TYPE_REGISTERS;
        inst->mnemonicValue = getMnemonicValue(mnemonic);
    }

    else if(sscanf(line, "%3s R%d, R%d", mnemonic, &inst->operands[0], &inst->operands[1]) == 3){
        if(getMnemonicValue(mnemonic) == OP_CMP){
            inst->type = TYPE_REGISTERS;
            inst->mnemonicValue = getMnemonicValue(mnemonic);
            inst->operands[2] = inst->operands[1];
            inst->operands[1] = inst->operands[0];
            inst->operands[0] = NO_OPERAND;
        }
        else{
            inst->type = TYPE_REGISTERS;
            inst->mnemonicValue = getMnemonicValue(mnemonic);
            inst->operands[2] = NO_OPERAND;
        }
    }
    
    else if(sscanf(line, "%3s #%d", mnemonic, &inst->operands[0]) == 2){
        inst->mnemonicValue = getMnemonicValue(mnemonic);
        inst->operands[1] = NO_OPERAND;
        inst->operands[2] = NO_OPERAND;

        if (inst->mnemonicValue == OP_BXX)
            inst->type = TYPE_LAST;
    }    
    else{
        sscanf(line, "%3s",mnemonic);
        inst->mnemonicValue = getMnemonicValue(mnemonic);
    
        if(inst->mnemonicValue == NO_OPCODE)
            inst->type = TYPE_DIRECTIVE;
        else if(inst->mnemonicValue == OP_HLT || inst->mnemonicValue == OP_RET || inst->mnemonicValue == OP_RETI)
            inst->type = TYPE_END_BLOCK;
        else
            inst->type = TYPE_SINGLE;    
    }
}

/**
 * @brief Parse the file and separate it into blocks of code.
 *
 * This function reads the source file and divides it into blocks of code based on certain criteria.
 * It dynamically allocates memory to store the code blocks and their instructions.
 *
 * @param filename The name of the source file to parse.
 * @param ppCodeBlock_st Pointer to the pointer of the code block structure to store the parsed code blocks.
 * @param totalBlocks Pointer to an integer to store the total number of code blocks.
 * @return 0 if successful, or a negative error code if an error occurred.
 */
int codeBlockDivision(const char *filename, codeBlock_st **ppCodeBlock_st, int *totalBlocks){
    
    FILE *file = fopen(filename, "r");
    
    if(!file){
        //LOG_ERROR("Failed to open source file!\n");
        printf("Failed to open source file!\n");
        return -ENOENT;
    }

    char line[1024];
    int lineCount = 0;
    *totalBlocks = 1;

    Instruction_st *pInstruction_st;

    *ppCodeBlock_st = malloc(sizeof(codeBlock_st));
    if(!*ppCodeBlock_st){
        //LOG_ERROR("Failed to allocate memory!\n");
        printf("Failed to allocate memory!\n");
        fclose(file);
        return -ENOMEM;
    }
    codeBlock_st* pCurrentBlock = *ppCodeBlock_st;

    pCurrentBlock->Instructions = NULL;
    pCurrentBlock->size = 0;

    while (fgets(line, sizeof(line), file)){
        
        pInstruction_st = realloc(pCurrentBlock->Instructions, (lineCount + 1) * sizeof(Instruction_st));
        if(!pInstruction_st){
            //LOG_ERROR("Failed to realloc memory");
            printf("Failed to realloc memory");
            fclose(file);
            return -ENOMEM;
        }
        pCurrentBlock->Instructions = pInstruction_st;

        parseInstruction(line, &pCurrentBlock->Instructions[lineCount]);

        if(pCurrentBlock->Instructions[lineCount].mnemonicValue == OP_BXX)
            pCurrentBlock->branchFound = true;
        else
            pCurrentBlock->branchFound = false;

        pCurrentBlock->Instructions[lineCount].lineNum = lineCount;        

        if(pCurrentBlock->Instructions[lineCount].type == TYPE_DIRECTIVE || pCurrentBlock->Instructions[lineCount].type == TYPE_END_BLOCK){
            (*totalBlocks)++;

            *ppCodeBlock_st = realloc(*ppCodeBlock_st, (*totalBlocks) * sizeof(codeBlock_st));            
            if(!*ppCodeBlock_st){
                //LOG_ERROR("Failed to realloc memory");
                printf("Failed to realloc memory");
                fclose(file);
                return -ENOMEM;
            }
            pCurrentBlock = &(*ppCodeBlock_st)[*totalBlocks-1];
            
            pCurrentBlock->Instructions = malloc(sizeof(Instruction_st)); 
            lineCount = 0;
            pCurrentBlock->Instructions[lineCount].lineNum = lineCount;
            parseInstruction(line, &pCurrentBlock->Instructions[lineCount]);  
            pCurrentBlock->size = 1;
            lineCount++;
        }
        else if(pCurrentBlock->Instructions[lineCount].type == TYPE_LAST){
            lineCount++;
            pCurrentBlock->size = lineCount;
            (*totalBlocks)++;
            *ppCodeBlock_st = realloc(*ppCodeBlock_st, (*totalBlocks) * sizeof(codeBlock_st));
            
            if(!*ppCodeBlock_st){
                //LOG_ERROR("Failed to realloc memory");
                printf("Failed to realloc memory");
                fclose(file);
                return -ENOMEM;
            }
            pCurrentBlock = &(*ppCodeBlock_st)[*totalBlocks-1];
            pCurrentBlock->Instructions = NULL;
            pCurrentBlock->size = 0;
            lineCount = 0;
        }
        else{        
            lineCount++;
            pCurrentBlock->size = lineCount;
        }
    }

    fclose(file);
    return 0;
}


/**
 * @brief Find the positions for the lines with stalls
 * @param pCodeBlock_st Pointer to the code block structure.
 * @return 0 on success, -ENOMEM if memory reallocation fails.
 */
int checkForStalls(codeBlock_st *pCodeBlock_st){
    pCodeBlock_st->stallPositionsNum = 0;
    pCodeBlock_st->stallPositions = malloc(sizeof(int));  

    if (pCodeBlock_st->stallPositions == NULL) {
        //LOG_ERROR("Failed to allocate memory for stall positions");
        printf("Failed to allocate memory for stall positions");
        return -ENOENT;
    }

    for(int i = 0; i < pCodeBlock_st->size - 1; i++){
        if (i + 1 < pCodeBlock_st->size && (pCodeBlock_st->Instructions[i].mnemonicValue == OP_LD || 
         pCodeBlock_st->Instructions[i].mnemonicValue == OP_LDX) && ( (isAluOperation(pCodeBlock_st->Instructions[i + 1].mnemonicValue) &&
            (pCodeBlock_st->Instructions[i].operands[0] == pCodeBlock_st->Instructions[i + 1].operands[1] ||
             pCodeBlock_st->Instructions[i].operands[0] == pCodeBlock_st->Instructions[i + 1].operands[2])) || ((pCodeBlock_st->Instructions[i+1].mnemonicValue == OP_ST || 
             pCodeBlock_st->Instructions[i+1].mnemonicValue == OP_STX) &&
             pCodeBlock_st->Instructions[i].operands[0] == pCodeBlock_st->Instructions[i + 1].operands[0]) ) ){

                int *pAux = realloc(pCodeBlock_st->stallPositions, (pCodeBlock_st->stallPositionsNum + 1) * sizeof(int));
                    if(pAux == NULL){
                        printf("Failed to reallocate memory for stall positions");
                        // LOG_ERROR("Failed to reallocate memory for stall positions");
                        return -ENOMEM;
                    }

                pCodeBlock_st->stallPositions = pAux;

                // Store the position of the stall
                pCodeBlock_st->stallPositions[pCodeBlock_st->stallPositionsNum] = pCodeBlock_st->Instructions[i].lineNum;
                pCodeBlock_st->stallPositionsNum++;
        }
    }
}

/**
 * @brief Find the positions for the lines that can be changed
 * to avoid the stall
 * @param pCodeBlock_st Pointer to the code block structure.
 * @return 0 on success, -ENOMEM if memory reallocation fails.
 */
int checkForReplacePositions(codeBlock_st *pCodeBlock_st){
    bool firstLine = true;
    bool stallAtended = false;

    bool dst_registers[REG_NUMBER];
    bool ope_registers[REG_NUMBER];

    pCodeBlock_st->replacePositionsNum = 0;

    memset(dst_registers, false, sizeof(dst_registers));
    memset(ope_registers, false, sizeof(ope_registers));
    int nextlimit = 0;

    pCodeBlock_st->replacePositions = malloc(sizeof(int));
    if(pCodeBlock_st->replacePositions == NULL){
        //LOG_ERROR("Failed to allocate memory for stall positions");
        printf("Failed to allocate memory for stall positions");
        return -ENOMEM;
    }

        for(int j = 0; j < pCodeBlock_st->stallPositionsNum; j++){
            
            //Variable Reset
            firstLine = true;
            memset(dst_registers, false, sizeof(dst_registers));
            memset(ope_registers, false, sizeof(ope_registers));

            int nextlimit = pCodeBlock_st->size;
            //Assignment of the next limit

                if(pCodeBlock_st->stallPositionsNum > j + 1)
                    nextlimit = pCodeBlock_st->stallPositions[j + 1];
                else
                    nextlimit = pCodeBlock_st->size;



            for (int i = pCodeBlock_st->stallPositions[j] + 1; i <= nextlimit; i++){
                if(pCodeBlock_st->Instructions[i].lineNum > pCodeBlock_st->stallPositions[j]){
                    
                    //Necessary fir update the operand and destiny registers of the first line
                    if(firstLine){

                        dst_registers[pCodeBlock_st->Instructions[i].operands[0]] = true;
                        ope_registers[pCodeBlock_st->Instructions[i].operands[1]] = true;
                        ope_registers[pCodeBlock_st->Instructions[i].operands[2]] = true;
                        firstLine = false;
                        stallAtended = false;
                        
                    }else if(!stallAtended){

                        switch (pCodeBlock_st->Instructions[i].mnemonicValue){              
                            case OP_NOP:
                                pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                stallAtended = true;
                            break;
                            
                            case OP_ADD:         
                            case OP_SUB:         
                            case OP_OR:         
                            case OP_XOR:
                            case OP_AND:                 
                            case OP_RR:           
                            case OP_RL:

                            if(pCodeBlock_st->Instructions[i].type == TYPE_REGISTERS){
                                if(dst_registers[pCodeBlock_st->Instructions[i].operands[0]] || dst_registers[pCodeBlock_st->Instructions[i].operands[1]] || dst_registers[pCodeBlock_st->Instructions[i].operands[2]] 
                                || ope_registers[pCodeBlock_st->Instructions[i].operands[0]] || ope_registers[pCodeBlock_st->Instructions[i].operands[1]] || ope_registers[pCodeBlock_st->Instructions[i].operands[2]]
                                || pCodeBlock_st->branchFound){

                                    dst_registers[pCodeBlock_st->Instructions[i].operands[0]] = true;
                                    ope_registers[pCodeBlock_st->Instructions[i].operands[1]] = true;
                                    ope_registers[pCodeBlock_st->Instructions[i].operands[2]] = true;

                                }
                                else{
                                    pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                    stallAtended = true;
                                }
                            }
                            else if(pCodeBlock_st->Instructions[i].type == TYPE_IMMEDIATE){
                                 if(dst_registers[pCodeBlock_st->Instructions[i].operands[0]] || dst_registers[pCodeBlock_st->Instructions[i].operands[1]]  
                                 || ope_registers[pCodeBlock_st->Instructions[i].operands[0]] || ope_registers[pCodeBlock_st->Instructions[i].operands[1]]
                                 || pCodeBlock_st->branchFound){
                                
                                    dst_registers[pCodeBlock_st->Instructions[i].operands[0]] = true;
                                    ope_registers[pCodeBlock_st->Instructions[i].operands[1]] = true;
                                }
                                else{
                                    //printf("Line for changing: %d (%d %d %d)\n",pCodeBlock_st->Instructions[i].lineNum, pCodeBlock_st->Instructions[i].operands[0],pCodeBlock_st->Instructions[i].operands[1],pCodeBlock_st->Instructions[i].operands[2]);
                                    pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                    stallAtended = true;
                                }
                            }

                            break;  
                                
                            case OP_CMP:
                                if(ope_registers[pCodeBlock_st->Instructions[i].operands[1]] || ope_registers[pCodeBlock_st->Instructions[i].operands[2]]){

                                    ope_registers[pCodeBlock_st->Instructions[i].operands[1]] = true;
                                    ope_registers[pCodeBlock_st->Instructions[i].operands[2]] = true; 

                                }else{
                    
                                    pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                    stallAtended = true;
                                }
                            break;

                            case OP_NOT:
                            case OP_MOV:
                                if(dst_registers[pCodeBlock_st->Instructions[i].operands[0]] || dst_registers[pCodeBlock_st->Instructions[i].operands[1]] ||
                                   ope_registers[pCodeBlock_st->Instructions[i].operands[0]] || ope_registers[pCodeBlock_st->Instructions[i].operands[1]]){

                                    dst_registers[pCodeBlock_st->Instructions[i].operands[0]] = true;
                                    ope_registers[pCodeBlock_st->Instructions[i].operands[1]] = true;

                                }else{
                                   
                                    pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                    stallAtended = true;
                                }
                            break;

                            case OP_LD:
                            case OP_LDI:
                            case OP_LDX:
                                if(dst_registers[pCodeBlock_st->Instructions[i].operands[0]] || ope_registers[pCodeBlock_st->Instructions[i].operands[0]]){

                                        dst_registers[pCodeBlock_st->Instructions[i].operands[0]] = true;
                                        
                                }else{
                                        
                                        pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                        stallAtended = true;
                                }
                            break;
            
                            case OP_ST:
                            case OP_STX:
                                if(dst_registers[pCodeBlock_st->Instructions[i].operands[0]] || pCodeBlock_st->Instructions[i].operands[0] == pCodeBlock_st->Instructions[pCodeBlock_st->stallPositions[j]].operands[0]){

                                    dst_registers[pCodeBlock_st->Instructions[i].operands[0]] = true;

                                }else{
                                   
                                    pCodeBlock_st->replacePositions[pCodeBlock_st->replacePositionsNum++] = pCodeBlock_st->Instructions[i].lineNum;
                                    stallAtended = true;
                                }
                            break;

                            case OP_BXX:
                            case OP_JMP:
                            case OP_RETI:         
                            case OP_RET:          
                            case OP_HLT:
                            break;

                            default:
                            break;          
                        }
                    }
                }
            }
        }
    }

/**
 * @brief Removes excess stalls from the code block.
 *
 * This function removes stalls from the code block based on the given replace positions.
 * It finds the closest preceding stall positions for each replace position and updates the stall positions array.
 *
 * @param pCodeBlock_st A pointer to the code block structure.
 */

void removeExcessStalls(codeBlock_st *pCodeBlock_st) {
    int newStallPositions[pCodeBlock_st->replacePositionsNum];
    int newStallCount = 0;

    // Iterate through replace positions to find closest preceding stall positions
    if (pCodeBlock_st->replacePositionsNum < pCodeBlock_st->stallPositionsNum) {
        for (int j = 0; j < pCodeBlock_st->replacePositionsNum; j++) {
            int closestStallIndex = -1;
            int closestDiff = -1;
            for (int i = 0; i < pCodeBlock_st->stallPositionsNum; i++) {
                int diff = pCodeBlock_st->replacePositions[j] - pCodeBlock_st->stallPositions[i];
                if (diff > 0 && (closestDiff == -1 || diff < closestDiff)) {
                    closestDiff = diff;
                    closestStallIndex = i;
                }
            }
            if (closestStallIndex != -1) {
                newStallPositions[newStallCount++] = pCodeBlock_st->stallPositions[closestStallIndex];
                // Mark the stall position as used by setting it to a large value
                pCodeBlock_st->stallPositions[closestStallIndex] = 250000;
            }
        }
        free(pCodeBlock_st->stallPositions);
        // Update the original stall positions array and its count
        memcpy(pCodeBlock_st->stallPositions, newStallPositions, newStallCount * sizeof(int));
        pCodeBlock_st->stallPositionsNum = newStallCount;

    }

}

/**
 * @brief Generates a file with modified code blocks.
 * 
 * This function generates a file with modified code blocks based on the provided code block structure.
 * It iterates through the instructions in the code block and adds them to the file in a specific order removing hazards
 * considering stall positions and replace positions.
 * 
 * @param destinationFilename The filename of the destination file.
 * @param pCodeBlock_st A pointer to the code block structure.
 * @return Returns 0 on success, or a negative error code on failure.
 */
int fileGenerator(const char *destinationFilename, codeBlock_st *pCodeBlock_st){
    FILE *destinationFile;
    char auxBuffer[256] = {0};
    int index = 0;
    bool searchingLine = false;

    destinationFile = fopen(destinationFilename, "a");
    if(destinationFile == NULL){
        printf("Error opening destination file");
        return -EINVAL;
    }
    
    for(int i = 0; i < pCodeBlock_st->size; i++){
            if(pCodeBlock_st->Instructions[i].line != NULL){
            // Just place each instruction in order, in case there are no replace positions
                if(pCodeBlock_st->replacePositionsNum == 0){
                    fputs(pCodeBlock_st->Instructions[i].line, destinationFile);
                }
            
            // When the position of the stall instruction is found, add it to the file
                else if(i == pCodeBlock_st->stallPositions[index]){
                    fputs(pCodeBlock_st->Instructions[i].line, destinationFile);
                    searchingLine = true;
                }

            // As soon as a replace instruction is found, add it to the file, then add the content of the auxBuffer and clear it
                else if(i == pCodeBlock_st->replacePositions[index]){
                    searchingLine = false;
                    fputs(pCodeBlock_st->Instructions[i].line, destinationFile);
                    if(index < pCodeBlock_st->replacePositionsNum - 1)
                        index++;
                    fputs(auxBuffer,destinationFile);
                    memset(auxBuffer, '\0', sizeof(auxBuffer));
                }

            // While a replace instruction is not found, add the content to the auxBuffer
                else if(searchingLine){
                    strncat(auxBuffer, pCodeBlock_st->Instructions[i].line, sizeof(auxBuffer) - 1);
                }

            // If there are no more stalls to solver, the instructions are appended normally
                else{
                    fputs(pCodeBlock_st->Instructions[i].line, destinationFile);
                }

            }
    }
    fclose(destinationFile);
}

/**
 * @brief Prints each block of code along with relevant information.
 * 
 * This function prints each block of code along with the branch information, instructions, stall positions,
 * and replace positions.
 * 
 * @param pCodeBlock_st A pointer to the code block structure.
 * @param totalBlocks The total number of code blocks.
 */
void printCodeBlocks(codeBlock_st* pCodeBlock_st, int totalBlocks){
    for(int i = 0; i < totalBlocks; i++){
        printf("\n--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n");
        printf("    Code Block %d:\n\n", i);   
        
        if(pCodeBlock_st[i].branchFound)
            printf("Branch Found!\n");

        for(int j = 0; j < pCodeBlock_st[i].size; j++){
            Instruction_st* inst = &pCodeBlock_st[i].Instructions[j];
            printf("    Instruction %d: Mnemonic Value: %d, Operands: [", inst->lineNum, inst->mnemonicValue);
            for (int k = 0; k < 3; k++) {
                if (k > 0) printf(", ");
                printf("%d", inst->operands[k]);
            }
            printf("], Type: %d\n", inst->type);
        }

        printf("\n    Stall positions: ");
        for(int j = 0; j < pCodeBlock_st[i].stallPositionsNum; j++)
            printf("%d ", pCodeBlock_st[i].stallPositions[j]);
        
        printf("\n    Replace positions: ");
        for(int j = 0; j < pCodeBlock_st[i].replacePositionsNum; j++)
            printf("%d ", pCodeBlock_st[i].replacePositions[j]);   

        printf("\n--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---\n");
    }
}

/**
 * @brief Executes the stall optimizer in the Assembly file, finding
 *        the stall instructions and replacing them without changing
 *        the execution flow.
 * 
 * @param filename The path of the input Assembly file.
 * @param destinationFilename The path of the output file where the optimized code will be written.
 * 
 * @return Returns 0 on success, -1 if there was an error parsing the file.
 */
int executeStallOptimization(const char *filename, const char *destinationFilename) {
    int numBlocks = 0;
    codeBlock_st *pCodeBlock = NULL;

    if (codeBlockDivision(filename, &pCodeBlock, &numBlocks) == -1) {
        printf("Error parsing file.\n");
        return -1;
    }

    FILE *cleanFile = fopen(destinationFilename, "w");
    if(cleanFile != NULL) 
        fclose(cleanFile);

    for (int i = 0; i < numBlocks; i++){
        int numstalls = 0;  // Reset the number of stalls for each block
        if(checkForStalls(&pCodeBlock[i]) == -ENOMEM){
            printf("Memory allocation failed for stall positions.\n");
        }

        if(checkForReplacePositions(&pCodeBlock[i]) == -ENOMEM){
            printf("Memory allocation failed for replacing positions.\n");
        }

        removeExcessStalls(&pCodeBlock[i]);
    }

    printCodeBlocks(pCodeBlock,numBlocks);

    for(int i = 0; i < numBlocks; i++)
      fileGenerator(destinationFilename,&pCodeBlock[i]);

}

int main(){
    const char* inputFilename = "out.asm";        // File for otimization
    const char* outputFilename = "optimized.asm"; // File otimized
    executeStallOptimization(inputFilename,outputFilename);
}
