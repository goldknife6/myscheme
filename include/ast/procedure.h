#ifndef _PROCEDURE_SCHEMER
#define _PROCEDURE_SCHEMER

#include "astlist.h"
#include "body.h"
#include "defformals.h"

class Procedure : public AstList {
public:
	Procedure(std::deque<std::shared_ptr<AstTree>> &deque)
	:AstList(deque) {
	}

	virtual std::string toString() override {
		std::string s;
		s += "(proc";
		std::string sep(" ");
		std::shared_ptr<AstTree> p;
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			//sep = " ";
		}
		s += ")";
		return s;
	}

	std::shared_ptr<Expression> getExp(int i) {
		return std::dynamic_pointer_cast<Expression>(child(i));
	}
	
	virtual Object *eval(EnvironmentObject *env) {
		std::shared_ptr<Expression> fristExp = getExp(0) ;
		if (!fristExp) 
			return nullptr;
		try {
			Object *p = fristExp->eval(env);

			FunctionObject  *func = dynamic_cast<FunctionObject*>(p);
			if(!func) throw *new NotAppException(p->toString());

			if(typeid(*func) == typeid(NativeFunctionObject)) {
				return static_cast<NativeFunctionObject*>(func)->invoke(this,env);
			}

			EnvironmentObject* newEnv = func->makeEnv();
			std::shared_ptr<DefFormals> def = func->getParameters();

			if(def->numChildren() != numChildren() - 1)
				throw *new ArugNotMutchException(this->toString());

			for(int i = 0; i < numChildren() - 1;i++) {
				def->eval(newEnv,i,getExp(i+1)->eval(env));
			}

			return func->getBody()->eval(newEnv);		
	
		} catch (UnboundException &e) {
			throw;
		}

		return nullptr;
	}
};




#endif/*_PROCEDURE_SCHEMER*/
