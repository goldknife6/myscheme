#ifndef _FORMALS_SCHEMER
#define _FORMALS_SCHEMER

#include "astlist.h"

class Formals : public AstList {
	bool var;
public:
	Formals(std::deque<AstTree*> &deque,
		bool v)
	:AstList(deque),var(v) {
	}

	virtual std::string toString() override {
		std::string s;
		s += "(formals";
		std::string sep("");
		AstTree *p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ")";
		return s;
	}

	virtual void check() override {
		std::cout<<"Formals check not impelmented"<<std::endl;
	}

	virtual Object *eval(Env *o) override {
		std::cout<<"Formals eval not impelmented"<<std::endl;
	}
};




#endif/*_FORMALS_SCHEMER*/
