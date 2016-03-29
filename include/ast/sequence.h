#ifndef _SEQUENCE_SCHEMER
#define _SEQUENCE_SCHEMER

#include "astlist.h"
#include "formals.h"
#include "expression.h"
#include "env.h"

class Sequence : public AstList {
public:
	Sequence(std::deque<AstTree*> &deque)
	:AstList(deque) {
		
	}

	virtual std::string toString() override {
		std::string s;
		s += "(Sequence";
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

	virtual void check() override {
		std::cout<<"Sequence check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		std::shared_ptr<Object> res;
		int i = numChildren();
		for(int j = 0;j < i; j++)
			res = child(j)->eval(e);
		return res;
	}
};




#endif/*_SEQUENCE_SCHEMER*/
