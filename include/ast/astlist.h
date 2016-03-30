#ifndef _ASTLIST_SCHEMER
#define _ASTLIST_SCHEMER
#include "asttree.h"

#include <deque>
class AstList : public AstTree {
private:
	std::deque<std::shared_ptr<AstTree>> value;

public:
	AstList(std::deque<std::shared_ptr<AstTree>> &deque)
	:value(deque) {
		
	}

	virtual int numChildren() override {
		return value.size();
	}

	virtual std::shared_ptr<AstTree> child(int i) override {
		if(i >= value.size() || i<0) 
			throw *new OutOfRangeException();
		return value[i];
	}

	virtual std::string toString() override {
		std::string s;
		s += "(";
		std::string sep("");
		for(std::shared_ptr<AstTree> p : value) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ")";
		return s;
	}
};


#endif/*_ASTLIST_SCHEMER*/
