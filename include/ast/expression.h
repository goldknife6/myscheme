#ifndef _EXPRESSION_SCHEMER
#define _EXPRESSION_SCHEMER

#include "astlist.h"
#include "object.h"
#include "env.h"

class Expression : public AstList {
public:
	virtual void check() override {
		std::cout<<"Expression check not impelmented"<<std::endl;
	}

	virtual Object *eval(Env *o) override {
		std::cout<<"Expression eval not impelmented"<<std::endl;
	}
};


#endif/*_EXPRESSION_SCHEMER*/
