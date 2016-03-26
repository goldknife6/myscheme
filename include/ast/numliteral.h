#ifndef _NUMLITERAL_SCHEMER
#define _NUMLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

#include <lexer.h>

class NumLiteral : public AstLeaf {
	Number *num;
public:
	NumLiteral(Lexer::Token &t)
	:AstLeaf(t) {
		num = new Number(t.getNumber());
	}

	int value() {
		return token().getNumber();
	}

	virtual void check() override {
		std::cout<<"NumLiteral check not impelmented"<<std::endl;
	}

	virtual Object *eval(Env *o) override {
		std::cout<<getValueMsg(num)<<std::endl;
		return num;
	}

};



#endif/*_NUMLITERAL_SCHEMER*/
