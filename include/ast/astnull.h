#ifndef _ASTNULL_SCHEMER
#define _ASTNULL_SCHEMER

#include "asttree.h"
#include "env.h"

class AstNull : public AstTree {
public:
	virtual int numChildren() override {
		return 0;
	}

	virtual std::shared_ptr<AstTree> child(int i) override {
		return nullptr;
	}

	virtual std::string toString() override {
		return "nulltree";
	}
	
};


#endif/*_ASTNULL_SCHEMER*/
