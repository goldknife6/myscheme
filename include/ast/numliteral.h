#ifndef _NUMLITERAL_SCHEMER
#define _NUMLITERAL_SCHEMER

#include "astleaf.h"

#include <lexer.h>

class NumLiteral : public AstLeaf {
public:
	NumLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	int value() {
		return token().getNumber();
	}

};



#endif/*_NUMLITERAL_SCHEMER*/
