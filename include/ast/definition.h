#ifndef _DEFINITION_SCHEMER
#define _DEFINITION_SCHEMER

#include "astlist.h"
#include <deque>

class Definition : public AstList {
	/*用于确定define表达式的参数是否带括号*/
	bool isDef;
public:
	Definition(std::deque<AstTree*> &var,bool b = false) 
	:AstList(var),isDef(false) {

	}

	AstTree *body() {
		if(!isDef)
			return child(1);
		return child(2);
	}

	AstTree *name() {
		return child(0);
	}

	AstTree *para() {
		if(!isDef)
			return nullptr;
		else {
			return child(1);
		}
	}

	virtual std::string toString() override {
		std::string s;
		s += "(define";
		
		if(name())
			s+= " "+name()->toString();
		if(para())
			s+= " "+para()->toString();
		if(body())
			s+= " "+body()->toString();

		s += ")";
		return s;
	}

	virtual void check() override {
		std::cout<<"Definition check not impelmented"<<std::endl;
	}

	virtual Object *eval(Env *e) override {
		Object *obj;

		if (!name()) {
			std::cout<<this->toString();
			return nullptr;
		}

		if (!isDef) {
			AstTree *exp = body();
			if(exp) {
				IdLiteral* var = dynamic_cast<IdLiteral*>(name());
				obj = exp->eval(e);
				e->put(var->getName(),obj);
			}
		} else {

			
		}

		return obj;
	}
};


#endif/*_DEFINITION_SCHEMER*/
