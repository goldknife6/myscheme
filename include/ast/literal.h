#ifndef _LITERAL_SCHEMER
#define _LITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"
#include "gc.h"
#include "lexer.h"

#include <string>



class Literal : public AstLeaf {
public:
	Literal(Lexer::Token &t)
	:AstLeaf(t) {
	}

	virtual Object* eval(std::shared_ptr<Environment> e)=0;	
};


class StringLiteral : public Literal {
public:
	StringLiteral(Lexer::Token &t)
	:Literal(t) {
	}

	std::string value() {
		return token().getText();
	}

	virtual Object* eval(std::shared_ptr<Environment> env) {
		return ObjectAlloctaor::allocString(value());
	}	
};

class NumberLiteral : public Literal {
public:
	NumberLiteral(Lexer::Token &t)
	:Literal(t) {
	}
	virtual Object* eval(std::shared_ptr<Environment> env) {
		
	}	
};

class BooleanLiteral : public Literal {
public:
	BooleanLiteral(Lexer::Token &t)
	:Literal(t) {
	}
	virtual Object* eval(std::shared_ptr<Environment> env) {
		
	}	
};

#endif/*_LITERAL_SCHEMER*/
