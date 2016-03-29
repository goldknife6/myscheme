#ifndef _DEFINITION_SCHEMER
#define _DEFINITION_SCHEMER

#include "astlist.h"
#include "defformals.h"
#include "env.h"

#include <deque>


class Definition : public AstList {
public:	
	Definition(std::deque<AstTree*> &var) 
	:AstList(var) {

	}

	virtual std::string toString() override {
		std::string s;
		s += "(define";
		int j = numChildren();
		for(int i = 0; i < j;i++) {
			s += " " + child(i)->toString();
		}
		s += ")";
		return s;
	}

	virtual IdLiteral *name() {
		return dynamic_cast<IdLiteral*>(child(0));
	}
		
	virtual void check() override {
		std::cout<<"Definition check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> env) =0;
};

class DefinitionNormal : public Definition {
public:	
	DefinitionNormal(std::deque<AstTree*> &var) 
	:Definition(var) {

	}

	Expression* expression() {
		return dynamic_cast<Expression*>(child(1));
	}


	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> env) {
		IdLiteral* var = name();

		if (!var) throw *new IllFormedException(this->toString());

		Expression *exp;

		if(numChildren() > 2)
			throw *new IllFormedException(this->toString());

		exp = expression();
		if(exp) {
			std::shared_ptr<Object> obj = exp->eval(env);
			env->put(var->getName(),obj);
		}

		return std::shared_ptr<Id>(new Id(var->getName()));
	}
};



class DefinitionVarlist : public Definition {
public:
	DefinitionVarlist(std::deque<AstTree*> &var) 
	:Definition(var) {

	}

	Body *body() {
		return dynamic_cast<Body*>(child(2));
	}
	
	DefFormals *para() {
		return dynamic_cast<DefFormals*>(child(1));
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> env) {

		IdLiteral* var = name();

		if (!var) throw *new IllFormedException(this->toString());

		DefFormals *def = para();
		
		Body *b = body();

		if(!b || !b->sequence()->numChildren()) 
			throw *new IllFormedException(this->toString());

		//std::cout<<b->sequence()->numChildren()<<std::endl;
	
		std::shared_ptr<NormalFunction> fun(new NormalFunction(def,b,env));

		env->put(var->getName(),fun);
		
		return std::shared_ptr<Id>(new Id(var->getName()));
	}
};


#endif/*_DEFINITION_SCHEMER*/
