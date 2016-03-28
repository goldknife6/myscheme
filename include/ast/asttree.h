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
	virtual AstTree *child(int) =0;
	virtual std::string location() =0;
	virtual std::string toString() =0;
	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment>) =0;
	virtual void check() =0;

	virtual std::string getValueMsg(std::shared_ptr<Object> ptr) {
		return "";
	}

	virtual std::string getUnboundMsg(std::string s) {
		return "";
	}
};




#endif/*_ASTTREE_SCHEMER*/
