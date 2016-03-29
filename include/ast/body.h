#ifndef _BODY_SCHEMER
#define _BODY_SCHEMER

#include "astlist.h"
#include "formals.h"
#include "object.h"
#include "sequence.h"
#include <env.h>


class Body : public AstTree {
	std::deque<AstTree*> def;
	AstTree *seq;

public:
	Body(std::deque<AstTree*> &def,AstTree *seq)
	:seq(seq),def(def) {
	}

	virtual int numChildren() {
		return 0;
	}
	virtual AstTree *child(int i) {
		return nullptr;
	}

	Sequence *sequence() {
		return dynamic_cast<Sequence*>(seq);
	}

	virtual std::string location() {
		AstTree *p;
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			if(!p->location().empty())
				return p->location();
		}
		return "";
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
	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		std::shared_ptr<Object> res;
		int i = def.size();
		for(int j = 0;j < i; j++) {
			def[j]->eval(e);
		}
		return sequence()->eval(e);
	}

};




#endif/*_BODY_SCHEMER*/
