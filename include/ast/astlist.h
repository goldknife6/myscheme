#ifndef _ASTLIST_SCHEMER
#define _ASTLIST_SCHEMER
#include "asttree.h"

#include <deque>
class AstList : public AstTree {
private:
	std::deque<AstTree*> childData;

public:
	AstList(std::deque<AstTree*> &deque)
	:childData(deque) {
		
	}

	virtual int numChildren() override {
		return childData.size();
	}

	virtual AstTree *child(int i) override {
		return childData[i];
	}

	virtual std::string location() override {
		for(AstTree *p : childData) {
			if(!p->location().empty())
				return p->location();

			return "";
		}
	}

	virtual std::string toString() override {
		std::string s;
		s += "(";
		std::string sep("");
		for(AstTree *p : childData) {
			s += sep;
			s += p->toString();
			sep = "  ";
		}
		s += ")";
		return s;
	}
};


#endif/*_ASTLIST_SCHEMER*/
