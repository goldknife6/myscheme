#ifndef _DEFINITION_SCHEMER
#define _DEFINITION_SCHEMER

#include <ast/defformals.h>

#include <deque>


class Definition : public AstList {
public:	
	Definition(std::deque<std::shared_ptr<AstTree>> &var) 
	:AstList(var) {
	}
	virtual std::shared_ptr<Variable> getVariable()=0;
};

class DefinitionNormal : public Definition {
public:	
	DefinitionNormal(std::deque<std::shared_ptr<AstTree>> &var) 
	:Definition(var) {
	}

	std::shared_ptr<Expression> getExpression() {
		return std::dynamic_pointer_cast<Expression>(child(1));
	}

	virtual std::shared_ptr<Variable> getVariable() override {
		return std::dynamic_pointer_cast<Variable>(child(0));
	}

	virtual Object* eval(Environment* env) override {
		std::shared_ptr<Variable> var = getVariable();
		if (!var) 
			throw *new IllFormedException(this->toString());

		std::shared_ptr<Expression> exp;
		if (numChildren() > 2)
			throw *new IllFormedException(this->toString());
		exp = getExpression();
		if (exp) {
			Object* obj = exp->eval(env);
			env->put(var->getName(),obj);
		}

		return nullptr;
	}
};



class DefinitionVarlist : public Definition {
public:
	DefinitionVarlist(std::deque<std::shared_ptr<AstTree>> &var) 
	:Definition(var) {

	}

	virtual std::shared_ptr<Variable> getVariable() override {
		return std::dynamic_pointer_cast<Variable>(child(0));
	}

	std::shared_ptr<DefFormals> getDefFormals() {
		return std::dynamic_pointer_cast<DefFormals>(child(1));
	}

	std::shared_ptr<Body> getBody() {
		return std::dynamic_pointer_cast<Body>(child(2));
	}

	virtual Object* eval(Environment *env) override {
		std::shared_ptr<Variable> var = getVariable();
		if (!var) 
			throw *new IllFormedException(this->toString());
		std::shared_ptr<DefFormals> def = getDefFormals();
		std::shared_ptr<Body> b = getBody();
/*
		if(!b || !b->sequence()->numChildren()) 
			throw *new IllFormedException(this->toString());

		//std::cout<<b->sequence()->numChildren()<<std::endl;
	
		std::shared_ptr<NormalFunction> fun(new NormalFunction(def,b,env,var->getName()));

		env->put(var->getName(),fun);
*/		
		return nullptr;
	}
};


#endif/*_DEFINITION_SCHEMER*/
