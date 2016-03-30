#ifndef _VARIABLE_SCHEMER
#define _VARIABLE_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

#include <string>
#include <lexer.h>

class Variable : public AstLeaf {
public:	
	Variable(Lexer::Token &t) 
	:AstLeaf(t) {
	}

	std::string getName() {
		return token().getText();
	}

	virtual Object* eval(std::shared_ptr<Environment> env) {
		Object* obj = env->get(getName());
		if(!obj) 
			throw *new UnboundException(getName());
		return obj;
	}
};



#endif/*_VARIABLE_SCHEMER*/
