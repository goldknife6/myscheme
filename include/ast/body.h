#ifndef _BODY_SCHEMER
#define _BODY_SCHEMER

#include "astlist.h"
#include "formals.h"
#include "object.h"
#include <env.h>

class Body : public AstList {
public:
	Body(std::deque<AstTree*> &def)
	:AstList(def) {
	}

	virtual std::string toString() override {
		std::string s;
		s += "(Body";
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
		std::cout<<"Body check not impelmented"<<std::endl;
	}
	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) override {
		std::shared_ptr<Object> res;
		int i = numChildren();
		for(int j = 0;j < i; j++)
			res = child(j)->eval(e);
		return res;
	}

};




#endif/*_BODY_SCHEMER*/
