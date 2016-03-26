#ifndef _BOOLLITERAL_SCHEMER
#define _BOOLLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"

#include <lexer.h>

class BoolLiteral : public AstLeaf {
public:
	BoolLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	bool value() {
		return token().getNumber();
	}

	virtual void check() override {
		std::cout<<"Conditional check not impelmented"<<std::endl;
	}

	virtual Object *eval() override {
		std::cout<<"Conditional eval not impelmented"<<std::endl;
	}

};



#endif/*_BOOLLITERAL_SCHEMER*/
