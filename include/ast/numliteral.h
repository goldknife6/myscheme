#ifndef _NUMLITERAL_SCHEMER
#define _NUMLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

#include <lexer.h>

class NumLiteral : public AstLeaf {
public:
	NumLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	int value() {
		return token().getNumber();
	}

	virtual void check() override {
		std::cout<<"NumLiteral check not impelmented"<<std::endl;
	}

	virtual Object *eval() override {
		std::cout<<"NumLiteral eval not impelmented"<<std::endl;
	}

};



#endif/*_NUMLITERAL_SCHEMER*/
