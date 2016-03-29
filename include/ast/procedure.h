#ifndef _PROCEDURE_SCHEMER
#define _PROCEDURE_SCHEMER

#include "astlist.h"
#include "env.h"

class Procedure : public AstList {
public:
	Procedure(std::deque<AstTree*> &deque)
	:AstList(deque) {
		
	}

	virtual std::string toString() override {
		std::string s;
		s += "(proc  ";
		std::string sep("");
		AstTree *p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ") ";
		return s;
	}

	virtual void check() override {
		std::cout<<"Procedure check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> env) {
		Expression *fristChild = dynamic_cast<Expression*>(child(0));

		if (!fristChild) 
			return nullptr;

		try {
			std::shared_ptr<Object> p = fristChild->eval(env);

			std::shared_ptr<Function> func = std::dynamic_pointer_cast<Function>(p);

			if(!func) throw *new NotAppException(fristChild->toString());

			std::shared_ptr<Environment> newEnv = func->makeEnv();
			DefFormals* def = func->parameters();

			if(def->numChildren() != numChildren() - 1)
				throw *new ArugNotMutchException(this->toString());

			for(int i = 0; i < numChildren() - 1;i++) {
				def->eval(newEnv,i,child(i+1)->eval(env));
			}

			return func->body()->eval(newEnv);		
	
		} catch (UnboundException &e) {
			if(fristChild->toString() == "+")
				e.printMsg();
		}

		return nullptr;
	}
};




#endif/*_PROCEDURE_SCHEMER*/
