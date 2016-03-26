#ifndef _ASTTREE_SCHEMER
#define _ASTTREE_SCHEMER
#include "object.h"

class AstTree {
public:
	virtual int numChildren() =0;
	virtual AstTree *child(int) =0;
	virtual std::string location() =0;
	virtual std::string toString() =0;
	virtual Object *eval() =0;
	virtual void check() =0;
};




#endif/*_ASTTREE_SCHEMER*/
