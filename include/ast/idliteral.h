#ifndef _IDLITERAL_SCHEMER
#define _IDLITERAL_SCHEMER

#include "astleaf.h"
#include "object.h"
#include "env.h"

#include <string>
#include <lexer.h>

class IdLiteral : public AstLeaf {
public:
	IdLiteral(Lexer::Token &t)
	:AstLeaf(t) {
	}

	std::string getName() {
		return token().getText();
	}

	virtual void check() override {


	}

	virtual Object *eval(Env *e) override {
		Object *obj;
		obj = e->get(getName());
		if(!obj) {
			std::cout<<getUnboundMsg(getName())<<std::endl;
		}
		return obj;
	}
};



#endif/*_IDLITERAL_SCHEMER*/
