#ifndef _STRLITERAL_SCHEMER
#define _STRLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

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

	virtual void check() override {
		std::cout<<"StrLiteral check not impelmented"<<std::endl;
	}

	virtual Object *eval() override {
		std::cout<<"StrLiteral eval not impelmented"<<std::endl;
	}
};



#endif/*_STRLITERAL_SCHEMER*/
