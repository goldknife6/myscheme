#ifndef _BOOLLITERAL_SCHEMER
#define _BOOLLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include <env.h>
#include <lexer.h>

class BoolLiteral : public AstLeaf {
	bool val;
public:
	BoolLiteral(Lexer::Token &t)
	:AstLeaf(t),val(value()) {
	}

	bool value() {
		return token().getNumber();
	}

	virtual void check() override {
		std::cout<<"Conditional check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		return std::shared_ptr<Object>(new Bool(val));
	}

};



#endif/*_BOOLLITERAL_SCHEMER*/
