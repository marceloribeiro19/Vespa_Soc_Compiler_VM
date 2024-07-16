#include <math.h> 
#include <stdio.h> 
#include <string.h> 

typedef struct lineParameters
{
    unsigned int addr;
    unsigned int value;
}sLineParams;

void init_statements_list(sLineParams** lineParams, int *strSize);
void add_statement(sLineParams** lineParams, unsigned int addr, unsigned int value, int *index, int *strSize);
void releaseStructure(sLineParams ** lineParams);
void bubbleSort(sLineParams **arr, int n);
FILE* openFile(const char* fileName, const char* openType);
void print_bin_number(FILE* fp, int value);
void print_code_binary(FILE *fp, const sLineParams* lineParams, int index);
unsigned int hexToDec(char *hexNum);

void init_statements_list(sLineParams** lineParams, int *strSize){
    *lineParams = (sLineParams*)malloc(sizeof(sLineParams) * 32);
    if(*lineParams == NULL){
        printf("Error allocating memory\n");
        exit(1);
    }

    *strSize = 32;
}

void add_statement(sLineParams** lineParams, unsigned int addr, unsigned int value, int *index, int *strSize){
    
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
    (*lineParams)[*index].value = value;

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

void print_bin_number(FILE* fp, int value){

    for(int j = 32; j > 0; j--){
        fprintf(fp, "%d", (value >> (j - 1)) & 1); 
    }    
}

void print_code_binary(FILE *fp, const sLineParams* lineParams, int index){

    fprintf(fp, "memory_initialization_radix=2;\nmemory_initialization_vector=\n");
    
    __uint8_t first = 1;
    
    for (int i = 0; i < index; i++) {
        
        if (!first){
            fprintf(fp, ",\n");
        }
        else {
            first = 0;
            if (lineParams[0].addr != 0){

            int auxAddr = 0;
            printf("estou aqui\n");
            while(auxAddr < lineParams[0].addr){
                
                auxAddr += 4;
                print_bin_number(fp, 0);
                fprintf(fp, ",\n");
            }
        }
        }

       

        if( (i > 0) && (lineParams[i].addr != lineParams[i-1].addr + 4)){

            __uint8_t it = 1;

            while ((lineParams[i].addr != lineParams[i-1].addr + (4 * it)))
            {
                print_bin_number(fp, 0);
                fprintf(fp, ",\n");
                it++;
            }
            print_bin_number(fp, lineParams[i].value);
        }
        else {
            print_bin_number(fp, lineParams[i].value);
        }
    }
    fprintf(fp, ";");
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

int main(int argc, char *argv[]) {
    
    char line[19];
    char addr[5];
    char hexValue[16];
    int strSize = 0;
    int index = 0;

    if (argc != 2) {
        printf("File name missing!\n Use: %s <hex_file>\n", argv[0]);
        return 1;
    }

    const char *hex_file = argv[1];

    FILE* file_hex = openFile(hex_file, "r");
    FILE* file_bin = openFile("Output/code.coe", "w");

    sLineParams *lineParams;
    init_statements_list(&lineParams, &strSize);

    while (fgets(line, sizeof(line), file_hex)) {

        sscanf(line, "@%4s %2s %2s %2s %2s", addr, &hexValue[0], &hexValue[2], &hexValue[4], &hexValue[6]);

        add_statement(&lineParams, hexToDec(addr), hexToDec(hexValue), &index, &strSize);
    }
    fclose(file_hex);

    bubbleSort(&lineParams, index);

    printf("Printing all statements:\n");
    for (int i = 0; i < index; i++) {
        printf("Addr: %4d,    Value: %12d\n", lineParams[i].addr, lineParams[i].value);
    }

    print_code_binary(file_bin, lineParams, index);

    releaseStructure(&lineParams);
    fclose(file_bin);

    return 0; 
}