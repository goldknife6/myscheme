#ifndef _NUMLITERAL_SCHEMER
#define _NUMLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

#include <lexer.h>

class NumLiteral : public AstLeaf {
	std::shared_ptr<Number> num;
public:
	NumLiteral(Lexer::Token &t)
	:AstLeaf(t),num(new Number(value())) {
	}

	int value() {
		return token().getNumber();
	}

	virtual void check() override {
		std::cout<<"NumLiteral check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) override {
		return num;		
	}

};



#endif/*_NUMLITERAL_SCHEMER*/
