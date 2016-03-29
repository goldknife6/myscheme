#ifndef _CONDITIONAL_SCHEMER
#define _CONDITIONAL_SCHEMER

#include "astlist.h"
#include "object.h"
#include "env.h"

class Conditional : public AstList {
public:
	Conditional(std::deque<AstTree*> &deque)
	:AstList(deque) {
	}

	virtual std::string toString() override {
		std::string s;
		s += "(if";
		std::string sep("");
		AstTree *p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = " ";
		}
		s += ")";
		return s;
	}

	virtual void check() override {
		std::cout<<"Conditional check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		if (!test() || !consequent()) {
			std::cout<<";Ill-formed special form:";
			std::cout<<toString()<<std::endl;
		} else {
			std::cout<<"Conditional eval not impelmented"<<std::endl;
		}
	}
private:
	AstTree *test() {
		return child(0);
	}
	AstTree *consequent() {
		return child(1);
	}
	AstTree *alternate() {
		return child(2);
	}

};




#endif/*_CONDITIONAL_SCHEMER*/
