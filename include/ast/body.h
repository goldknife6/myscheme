#ifndef _BODY_SCHEMER
#define _BODY_SCHEMER

#include "astlist.h"
#include "formals.h"
#include "object.h"
#include "sequence.h"


class Body : public AstTree {
	std::deque<std::shared_ptr<AstTree>> def;
	std::shared_ptr<AstTree> seq;
public:
	Body(std::deque<std::shared_ptr<AstTree>> &def,std::shared_ptr<AstTree> seq)
	:seq(seq),def(def) {}

	virtual int numChildren() {
		return 0;
	}
	virtual std::shared_ptr<AstTree> child(int i) {
		return nullptr;
	}

	std::shared_ptr<Sequence> sequence() {
		return std::dynamic_pointer_cast<Sequence>(seq);
	}

	virtual std::string toString() override {
		std::string s;
		s += "(body";
		std::string sep("");
		std::shared_ptr<AstTree> p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ")";
		return s;
	}

	virtual Object *eval(EnvironmentObject *env) {
		Object *res;
		int i = def.size();
		for(int j = 0;j < i; j++) {
			def[j]->eval(env);
		}
		return sequence()->eval(env);
	}
	

};




#endif/*_BODY_SCHEMER*/
