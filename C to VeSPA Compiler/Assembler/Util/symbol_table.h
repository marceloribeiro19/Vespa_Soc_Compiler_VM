#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <stdint.h>

#define NULL_PTR            0
#define UNINITIALIZED_VALUE 0xFFFF
   

void init_symbol_table();
void delete_symbol_table();

uint32_t add_symbol(char *name);
uint32_t set_symbol_value(uint32_t index, int32_t value);
int32_t get_symbol_value(uint32_t index);
char* get_symbol_name(uint32_t index);


void print_table();

#endif