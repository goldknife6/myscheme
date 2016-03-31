#ifndef _EXPRESSION_SCHEMER
#define _EXPRESSION_SCHEMER

#include "astlist.h"
#include "object.h"

class Expression : public AstTree {
	std::shared_ptr<AstTree> value;
public:
	Expression(std::shared_ptr<AstTree> t)
	:value(t) {
	}

	virtual int numChildren() override {
		return 1;
	}

	virtual std::shared_ptr<AstTree> child(int i) override {
		if(i==0) return value;
		else throw *new OutOfRangeException("Expression");
	}

	virtual std::string toString() override {
		throw *new SchemeError("Expression toString");
	}

	virtual Object* eval(EnvironmentObject *env) override {
		return value->eval(env);
	}
};


#endif/*_EXPRESSION_SCHEMER*/
