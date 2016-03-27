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
		AstTree *fristChild = child(0);

		if (fristChild == nullptr)
			return nullptr;

		Object *p = fristChild->eval(o);

		if(!p) {
			return nullptr;
		}

		Function *f = dynamic_cast<Function *>(p);
		if(!f) {
			std::cout<<";The object is not applicable."<<std::endl;
		}
		return nullptr;
	}
};




#endif/*_PROCEDURE_SCHEMER*/
