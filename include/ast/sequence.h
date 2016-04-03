#ifndef _SEQUENCE_SCHEMER
#define _SEQUENCE_SCHEMER

#include "astlist.h"
#include "formals.h"
#include "expression.h"

class Sequence : public AstList {
public:
	Sequence(std::deque<std::shared_ptr<AstTree>> &deque)
	:AstList(deque) {}

	virtual std::string toString() override {
		std::string s;
		std::shared_ptr<AstTree> p;
		
		for(int i = 0; (i < numChildren()) && (p = child(i)); i++) {
			s += " ";
			s += p->toString();
		}
		return s;
	}

	virtual Object *eval(EnvironmentObject *e) {
		Object *res;
		int i = numChildren();
		for(int j = 0;j < i; j++) {
			res = child(j)->eval(e);
		}

		if(res)
			return res->copyObject();
		else
			return nullptr;
	}
};




#endif/*_SEQUENCE_SCHEMER*/
