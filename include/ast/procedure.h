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
		s += ")";
		return s;
	}
};




#endif/*_PROCEDURE_SCHEMER*/
