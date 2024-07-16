#ifndef _ASSEMBLER_MAIN_H_
#define _ASSEMBLER_MAIN_H_

#include <stdio.h>
#include <stdlib.h>

void get_source_file(FILE** file);
void get_output_file(FILE** ppFile);

size_t get_line_number();
size_t increment_line_number(size_t n);

#endif