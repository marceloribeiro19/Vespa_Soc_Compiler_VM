#include <math.h> 
#include <stdio.h> 
#include <string.h> 

#define CRED    "\x1b[31m"
#define CORANGE "\x1b[38;5;208m"
#define CYELLOW "\x1b[33m"
#define CGREEN  "\x1b[32m"
#define CRESET  "\x1b[0m"

typedef struct lineParameters
{
    unsigned int addr;
    char value[20];
}sLineParams;

void init_statements_list(sLineParams** lineParams, int *strSize);
void add_statement(sLineParams** lineParams, unsigned int addr, const char *value, int *index, int *strSize);
void releaseStructure(sLineParams ** lineParams);
void bubbleSort(sLineParams **arr, int n);
FILE* openFile(const char* fileName, const char* openType);
unsigned int hexToDec(char *hexNum);
int findDiffAddr(sLineParams *Hex, int hexSize, sLineParams *Golden, int goldenSize, const char * hex_file, const char * golden_file);
int findErrors(sLineParams *lineParamsGold, sLineParams *lineParamsHex, int maxIndex);

void init_statements_list(sLineParams** lineParams, int *strSize){
    *lineParams = (sLineParams*)malloc(sizeof(sLineParams) * 32);
    if(*lineParams == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }

    *strSize = 32;
}


void add_statement(sLineParams** lineParams, unsigned int addr, const char *value, int *index, int *strSize){
    
    if(*index >= *strSize){
        *strSize += 32;
        *lineParams = (sLineParams*) realloc(*lineParams, sizeof(sLineParams) * (*strSize));

        if(lineParams == NULL){
            printf("Error allocating memory\n");
            exit(1);
        }
    }

    if (addr % 4 != 0){
        printf("Address Invalid %4xh\n", addr);
        exit(1);
    }

    (*lineParams)[*index].addr  = addr;
    strcpy((*lineParams)[*index].value, value);

    (*index)++;
}

void releaseStructure(sLineParams ** lineParams){

    free(*lineParams);
}

void bubbleSort(sLineParams **arr, int n){
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((*arr)[j].addr > (*arr)[j+1].addr) {
                sLineParams temp = (*arr)[j];
                (*arr)[j] = (*arr)[j+1];
                (*arr)[j+1] = temp;
            }
        }
    }
}

FILE* openFile(const char* fileName, const char* openType){
    FILE *file = fopen(fileName, openType);
    if (file == NULL) {
        printf("Error Opening File\n");
        exit(1);
    }
    return file;
}

unsigned int hexToDec(char *hexNum){

    const char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', 
                                '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' }; 
    unsigned int decimalNumber = 0; 
    int power = 0; 

    for (int i = strlen(hexNum) - 1; i >= 0; i--) { 
    
        for (int j = 0; j < 16; j++) { 
            if (hexNum[i] == hexDigits[j]) { 
                decimalNumber += j * pow(16, power); 
            } 
        } 
        power++; 
    }
    return decimalNumber;
}

int findErrors(sLineParams *lineParamsGold, sLineParams *lineParamsHex, int maxIndex){

    int error = 0;

    for (int i = 0; i < maxIndex; i++) {

        int len = strlen(lineParamsHex[i].value);
        int pos[4] = {-1, -1, -1, -1};
        int index = 0;

        if(lineParamsHex[i].addr != lineParamsGold[i].addr){
            break;
        }

        for (int j = 0; j < len; j=j+3) {
            if (((lineParamsHex[i].value[j] != lineParamsGold[i].value[j]) || lineParamsHex[i].value[j+1] != lineParamsGold[i].value[j+1]) ) {
                pos[index] = j/3;
                index++;
                error = 1;
            }
        }
        
        int index2 = 0;
        int offset = 0;
        
        if ((pos[index2] != -1) || pos[index2+3] != -1 || pos[index2+1] != -1  || pos[index2+2] != -1) {
            printf(CRED "Error" CRESET" in address @%04x --> ", lineParamsGold[i].addr);
            printf("Hex: %s , Golden: %s\n", lineParamsHex[i].value, lineParamsGold[i].value);
            printf("                                ");
            
            for (int j = 0; j < index; j++) {
                
                for (int j = 0; j < (pos[index2]*3 - offset); j++) {
                    printf(" ");
                }
                printf(CYELLOW "^" CRESET);

                offset = (pos[index2]*3) + 1 ;
                index2++;
            }
            for (int j = 0; j < (22 - offset); j++) {
                    printf(" ");
            }

            index2 = 0;
            offset = 0;
            for (int j = 0; j < index; j++) {
                
                for (int j = 0; j < (pos[index2]*3 - offset); j++) {
                    printf(" ");
                }
                printf(CYELLOW "^" CRESET);

                offset = (pos[index2]*3) +1 ;
                index2++;
            }
            printf("\n");
        }
    } 

    return error;
}

int findDiffAddr(sLineParams *Hex, int hexSize, sLineParams *Golden, int goldenSize, const char * hex_file, const char * golden_file) {
    int found;
    int error = 0;

    for (int i = 0; i < hexSize; i++) {
        found = 0;
        for (int j = 0; j < goldenSize; j++) {
            if (Hex[i].addr == Golden[j].addr) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf(CORANGE "Error: " CRESET "@%04x address not found (%s)\n\n", Hex[i].addr, hex_file);
            error = 1;
        }
    }

    for (int i = 0; i < goldenSize; i++) {
        found = 0;
        for (int j = 0; j < hexSize; j++) {
            if (Golden[i].addr == Hex[j].addr) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf(CORANGE "Error: " CRESET "@%04x address not found (%s)\n\n", Golden[i].addr, golden_file);
            error = 1;
        }
    }
    return error;
}

int main(int argc, char *argv[]) {
    
    char line[19];
    char addr[5];
    char hexValue[20];
    int strSize = 0;
    int indexHex = 0;
    int indexGold = 0;
    int error = 0;

    if (argc != 3) {
        printf("File name missing!\n Use: %s <hex_file>\n", argv[0]);
        return 1;
    }

    const char *hex_file = argv[1];
    const char *golden_file = argv[2];

    FILE* file_hex = openFile(hex_file, "r");
    FILE* file_gold = openFile(golden_file, "r");

    sLineParams *lineParamsHex;
    init_statements_list(&lineParamsHex, &strSize);
    sLineParams *lineParamsGold;
    init_statements_list(&lineParamsGold, &strSize);

    while (fgets(line, sizeof(line), file_hex)) {

        sscanf(line, "@%4s %[^\n]", addr, hexValue);
        add_statement(&lineParamsHex, hexToDec(addr), hexValue, &indexHex, &strSize);
    }
    fclose(file_hex);

    while (fgets(line, sizeof(line), file_gold)) {
        
        sscanf(line, "@%4s %[^\n]", addr, hexValue);
        add_statement(&lineParamsGold, hexToDec(addr), hexValue, &indexGold, &strSize);
    }
    fclose(file_gold);

    bubbleSort(&lineParamsHex,  indexHex);
    bubbleSort(&lineParamsGold, indexGold);

    int maxIndex = (indexGold > indexHex) ? indexGold : indexHex;

    error = findErrors(lineParamsGold, lineParamsHex, maxIndex);

    error = findDiffAddr(lineParamsHex, indexHex, lineParamsGold, indexGold, hex_file, golden_file);

    if(!error){
        printf(CGREEN "\nSucess: " CRESET " %s matches %s\n\n", hex_file, golden_file);
    }

    releaseStructure(&lineParamsHex);
    releaseStructure(&lineParamsGold);
   
    return 0; 
}