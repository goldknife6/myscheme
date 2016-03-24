#ifndef _ASTTREE_SCHEMER
#define _ASTTREE_SCHEMER

class AstTree {
public:
	virtual int numChildren() =0;
	virtual AstTree *child(int) =0;
	virtual std::string location() =0;
	virtual std::string toString() =0;
};




#endif/*_ASTTREE_SCHEMER*/
