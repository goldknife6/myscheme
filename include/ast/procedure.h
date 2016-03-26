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

	virtual Object *eval(Env *o) override {
		IdLiteral *funName = dynamic_cast<IdLiteral *>(child(0));
		Object *fun = o->get(funName->getName());

		if(!fun) {
			std::cout<<getUnboundMsg(funName->getName());
			return nullptr;
		}

		std::cout<<funName;
	}
};




#endif/*_PROCEDURE_SCHEMER*/
