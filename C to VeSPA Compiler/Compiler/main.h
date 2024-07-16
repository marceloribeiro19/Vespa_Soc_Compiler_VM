#ifndef ROCKETC_MAIN_H
#define ROCKETC_MAIN_H

#include <stdlib.h>
#include <stdio.h>

size_t getLineNumber();
int getSourceFile(FILE** ppSourceFile);
size_t incrementLineNumber(size_t n);

#endif
