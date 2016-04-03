#ifndef _DEFFORMALS_SCHEMER
#define _DEFFORMALS_SCHEMER

#include "astlist.h"
#include "variable.h"
#include "object.h"

class DefFormals : public AstList {
public:
	DefFormals(std::deque<std::shared_ptr<AstTree>> &deque)
	:AstList(deque){
	}

	virtual std::string toString() override {
		std::string s;
		s += "(";
		std::string sep("");
		std::shared_ptr<AstTree> p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += sep;
			s += p->toString();
			sep = " ";
		}
		s += ")";
		return s;
	}

	virtual Object* eval(EnvironmentObject *env) {
		throw *new SchemeError("DefFormals eval called");
	}

	std::shared_ptr<Variable> getVariable(int index) {
		return std::dynamic_pointer_cast<Variable>(child(index));
	}
	void eval(EnvironmentObject *env,int index,Object *obj) {
		std::shared_ptr<Variable> var = getVariable(index);		
		env->put(var->getName(),obj);
	}
	
};


#endif/*_DEFFORMALS_SCHEMER*/
