#ifndef _BODY_SCHEMER
#define _BODY_SCHEMER

#include "astlist.h"
#include "formals.h"
#include "object.h"

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
	virtual Object *eval() override {
		std::cout<<"Body eval not impelmented"<<std::endl;
	}

};




#endif/*_BODY_SCHEMER*/
