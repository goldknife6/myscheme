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

	virtual void check() override {
		std::cout<<"Expression check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) override {
		std::cout<<"Expression eval not impelmented"<<std::endl;
	}
};


#endif/*_EXPRESSION_SCHEMER*/
