#ifndef _DEFFORMALS_SCHEMER
#define _DEFFORMALS_SCHEMER

#include "astlist.h"
#include "idliteral.h"
class DefFormals : public AstList {
public:
	DefFormals(std::deque<AstTree*> &deque)
	:AstList(deque){
	}

	virtual std::string toString() override {
		std::string s;
		s += "(";
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
		std::cout<<"DefFormals check not impelmented"<<std::endl;
	}

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> env) {
		throw *new SchemeError("DefFormals eval called");
	}

	void eval(std::shared_ptr<Environment> env,
				int index,std::shared_ptr<Object> obj) {
		IdLiteral *var = dynamic_cast<IdLiteral *> (child(index));		
		env->put(var->getName(),obj);
	}
};


#endif/*_DEFFORMALS_SCHEMER*/
