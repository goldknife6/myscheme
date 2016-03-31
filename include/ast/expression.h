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

	virtual std::shared_ptr<AstTree> child(int) override {

	}

	virtual std::string toString() override {

	}

	virtual Object* eval(Environment *env) override {
	
	}
};


#endif/*_EXPRESSION_SCHEMER*/
