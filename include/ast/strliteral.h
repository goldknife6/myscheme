#ifndef _STRLITERAL_SCHEMER
#define _STRLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

#include <string>
#include <lexer.h>

class StrLiteral : public AstLeaf {
	std::string str;
public:
	StrLiteral(Lexer::Token &t)
	:AstLeaf(t),str(value()) {
	}

	std::string value() {
		return token().getText();
	}

	virtual void check() override {
		std::cout<<"StrLiteral check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		return std::shared_ptr<Object>(new String(str));		
	}
};



#endif/*_STRLITERAL_SCHEMER*/
