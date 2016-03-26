#ifndef _ASTTREE_SCHEMER
#define _ASTTREE_SCHEMER
#include "object.h"
#include "env.h"
#include <string>
class AstTree {
public:
	virtual int numChildren() =0;
	virtual AstTree *child(int) =0;
	virtual std::string location() =0;
	virtual std::string toString() =0;
	virtual Object *eval(Env *) =0;
	virtual void check() =0;

	virtual std::string getValueMsg(Object *o) {
		return "\n;Value: " + o->toString() + "\n";
	}

	virtual std::string getUnboundMsg(std::string s) {
		return "\n;Unbound variable: " + s + "\n";
	}
};




#endif/*_ASTTREE_SCHEMER*/
