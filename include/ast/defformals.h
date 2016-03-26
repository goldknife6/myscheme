#ifndef _DEFFORMALS_SCHEMER
#define _DEFFORMALS_SCHEMER

#include "astlist.h"

class DefFormals : public AstList {
	bool var;
public:
	DefFormals(std::deque<AstTree*> &deque,
			bool v)
	:AstList(deque),var(v) {
	}

	virtual std::string toString() override {
		std::string s;
		s += "(DefFormals";
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

	virtual void check() override {
		std::cout<<"DefFormals check not impelmented"<<std::endl;
	}

	virtual Object *eval() override {
		std::cout<<"DefFormals eval not impelmented"<<std::endl;
	}
};


#endif/*_DEFFORMALS_SCHEMER*/
