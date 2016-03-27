#ifndef _BOOLLITERAL_SCHEMER
#define _BOOLLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include <env.h>
#include <lexer.h>

class BoolLiteral : public AstLeaf {
	Bool * val;
public:
	BoolLiteral(Lexer::Token &t)
	:AstLeaf(t) {
		val = new Bool(value());
	}

	bool value() {
		return token().getNumber();
	}

	virtual void check() override {
		std::cout<<"Conditional check not impelmented"<<std::endl;
	}

	virtual Object *eval(Env *o) override {
		return val;
	}

};



#endif/*_BOOLLITERAL_SCHEMER*/
