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
		return value->toString();
	}

	virtual Object* eval(EnvironmentObject *env) override {
		if(value)
			return value->eval(env);
		return nullptr;
	}
};


#endif/*_EXPRESSION_SCHEMER*/
