#ifndef _CONDITIONAL_SCHEMER
#define _CONDITIONAL_SCHEMER

#include "astlist.h"
#include "object.h"

class Conditional : public AstList {
public:
	Conditional(std::deque<std::shared_ptr<AstTree>> &deque)
	:AstList(deque) {
	}

	virtual std::string toString() override {
		std::string s;
		s += "(if";
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

	virtual Object *eval(EnvironmentObject *env) {
		if(numChildren() > 3 || numChildren() < 2)
			throw *new IllFormedException(toString());

		if(typeid(*test()) != typeid(Expression) ||
			typeid(*consequent()) != typeid(Expression))
			throw *new IllFormedException(toString());

		BooleanObject *obj = dynamic_cast<BooleanObject*>(test()->eval(env));
		if(!obj) {
			throw *new IllFormedException(toString());
		}
		if(obj->getValue()) {
			return consequent()->eval(env);
		} else if (numChildren() == 3) {
			return alternate()->eval(env);	
		} else
			return nullptr;
	}
private:
	std::shared_ptr<AstTree> test() {
		return child(0);
	}
	std::shared_ptr<AstTree> consequent() {
		return child(1);
	}
	std::shared_ptr<AstTree> alternate() {
		return child(2);
	}
};




#endif/*_CONDITIONAL_SCHEMER*/
