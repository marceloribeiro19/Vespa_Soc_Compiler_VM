#ifndef _SCANNER_H_
#define _SCANNER_H_
#include "../Util/Globals.h"
#include "../Util/Types.h"

int yyparse();
int initLexer();
TokenType_et getToken(void);

#endif