#ifndef _EXPRESSION_SCHEMER
#define _EXPRESSION_SCHEMER

#include "astlist.h"
#include "object.h"
#include "env.h"

class Expression : public AstTree {
	AstTree *value;
public:
	Expression(AstTree *v):value(v) {
	}

	virtual int numChildren() {
		return 1;
	}

	virtual AstTree *child(int i) {
		return value;
	}

	virtual std::string location() {
		return 	value->location();
	}

	virtual std::string toString() {
		return 	value->toString();
	}

	virtual void check() override {
		std::cout<<"Expression check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		return value->eval(e);
	}
};


#endif/*_EXPRESSION_SCHEMER*/
