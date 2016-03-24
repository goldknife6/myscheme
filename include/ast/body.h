#ifndef _BODY_SCHEMER
#define _BODY_SCHEMER

#include "astlist.h"
#include "formals.h"

class Body : public AstList {
public:
	Body(std::deque<AstTree*> &deque)
	:AstList(deque) {
		
	}


	virtual std::string toString() override {
		std::string s;
		s += "(Body  ";
		std::string sep("");
		AstTree *p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ")\n";
		return s;
	}
};




#endif/*_BODY_SCHEMER*/
