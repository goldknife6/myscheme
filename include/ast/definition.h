#ifndef _DEFINITION_SCHEMER
#define _DEFINITION_SCHEMER

#include "astlist.h"
#include "defformals.h"
#include "env.h"

#include <deque>

class Definition : public AstList {
	/*用于确定define表达式的参数是否带括号*/
	bool isDef;
public:
	Definition(std::deque<AstTree*> &var,bool b = false) 
	:AstList(var),isDef(b) {

	}

	Body *body() {
		if(isDef)
			return dynamic_cast<Body*>(child(2));
		return nullptr;
	}
	
	Expression* expression() {
		if(!isDef)
			return dynamic_cast<Expression*>(child(1));
		return nullptr;
	}

	IdLiteral *name() {
		return dynamic_cast<IdLiteral*>(child(0));
	}

	DefFormals *para() {
		if(!isDef)
			return nullptr;
		else 
			return dynamic_cast<DefFormals*>(child(1));
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

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> env) override {

		IdLiteral* var = name();

		if (!var) {
			//std::cout<<this->toString();
			return nullptr;
		}

		if (!isDef) {
			Expression *exp = expression();
			if(exp) {
				std::shared_ptr<Object> obj = exp->eval(env);
				env->put(var->getName(),obj);
			}
		} else {
			DefFormals *def = para();
			Body *b = body();
			if(!b || !b->numChildren()) *new IllFormedException(this->toString());
			std::cout<<b->numChildren();
			std::shared_ptr<NormalFunction> fun(new NormalFunction(def,b,env));
			env->put(var->getName(),fun);
		}
		
		return std::shared_ptr<Id>(new Id(var->getName()));
	}
};


#endif/*_DEFINITION_SCHEMER*/
