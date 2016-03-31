#ifndef _LITERAL_SCHEMER
#define _LITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "gc.h"
#include "lexer.h"

#include <string>



class Literal : public AstLeaf {
public:
	Literal(Lexer::Token &t)
	:AstLeaf(t) {
	}

	virtual Object* eval(Environment *)=0;	
};


class StringLiteral : public Literal {
public:
	StringLiteral(Lexer::Token &t)
	:Literal(t) {
	}

	std::string value() {
		return token().getText();
	}

	virtual Object* eval(Environment *env) {
		return ObjectAlloctaor::allocString(value());
	}	
};

class NumberLiteral : public Literal {
public:
	NumberLiteral(Lexer::Token &t)
	:Literal(t) {
	}
	int value() {
		return token().getNumber();
	}
	virtual Object* eval(Environment *env) {
		return ObjectAlloctaor::allocNumber(value());
	}	
};

class BooleanLiteral : public Literal {
public:
	BooleanLiteral(Lexer::Token &t)
	:Literal(t) {
	}
	bool value() {
		return token().getNumber();
	}
	virtual Object* eval(Environment *env) {
		return ObjectAlloctaor::allocBoolean(value());
	}	
};

#endif/*_LITERAL_SCHEMER*/
