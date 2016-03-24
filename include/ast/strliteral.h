#ifndef _STRLITERAL_SCHEMER
#define _STRLITERAL_SCHEMER

#include "astleaf.h"
#include <string>
#include <lexer.h>

class StrLiteral : public AstLeaf {
public:
	StrLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	std::string value() {
		return token().getText();
	}

};



#endif/*_STRLITERAL_SCHEMER*/
