#ifndef _ASTTREE_SCHEMER
#define _ASTTREE_SCHEMER
#include <string>
#include <excpetion.h>
#include <memory>

class Object;
class Environment;

class AstTree {
public:
	virtual int numChildren() =0;
	virtual std::shared_ptr<AstTree> child(int) =0;
	virtual std::string toString() =0;
	virtual Object* eval(std::shared_ptr<Environment>) =0;
};




#endif/*_ASTTREE_SCHEMER*/
