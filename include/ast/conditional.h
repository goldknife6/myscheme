#ifndef _CONDITIONAL_SCHEMER
#define _CONDITIONAL_SCHEMER

#include "astlist.h"

class Conditional : public AstList {
public:
	Conditional(std::deque<AstTree*> &deque)
	:AstList(deque) {
	}
	AstTree *test() {
		return child(0);
	}
	AstTree *consequent() {
		return child(1);
	}
	AstTree *alternate() {
		if(numChildren() ==3)
			return child(2);
		return nullptr;
	}

	virtual std::string toString() override {
		std::string s;
		s += "(Conditional  ";
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




#endif/*_CONDITIONAL_SCHEMER*/
