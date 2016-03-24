#ifndef _IDLITERAL_SCHEMER
#define _IDLITERAL_SCHEMER

#include "astleaf.h"

#include <string>

#include <lexer.h>

class IdLiteral : public AstLeaf {
public:
	IdLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	std::string getName() {
		return token().getText();
	}
};



#endif/*_IDLITERAL_SCHEMER*/
