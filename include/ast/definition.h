#ifndef _DEFINITION_SCHEMER
#define _DEFINITION_SCHEMER

#include "astlist.h"

#include <deque>
class Definition : public AstList {
	AstTree* exp;

public:
	Definition(std::deque<AstTree*> &var,AstTree* e/*exp or body*/) 
	:AstList(var),exp(e) {

	}

	virtual std::string toString() override {
		std::string s;
		s += "(define  ";
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


#endif/*_DEFINITION_SCHEMER*/
