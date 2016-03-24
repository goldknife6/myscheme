#ifndef _BOOLLITERAL_SCHEMER
#define _BOOLLITERAL_SCHEMER

#include "astleaf.h"
#include <lexer.h>

class BoolLiteral : public AstLeaf {
public:
	BoolLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	bool value() {
		return token().getNumber();
	}

};



#endif/*_BOOLLITERAL_SCHEMER*/
