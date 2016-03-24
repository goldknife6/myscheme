#ifndef _LAMBDA_SCHEMER
#define _LAMBDA_SCHEMER

#include "astlist.h"
#include "formals.h"

class Lambda : public AstList {
public:
	Lambda(std::deque<AstTree*> &deque)
	:AstList(deque) {
		
	}

	Formals &formals() {

	}

	virtual std::string toString() override {
		std::string s;
		s += "(lambda  ";
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
};




#endif/*_LAMBDA_SCHEMER*/
