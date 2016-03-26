#ifndef _PROCEDURE_SCHEMER
#define _PROCEDURE_SCHEMER

#include "astlist.h"

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

	virtual Object *eval() override {
		std::cout<<"Procedure eval not impelmented"<<std::endl;
	}
};




#endif/*_PROCEDURE_SCHEMER*/