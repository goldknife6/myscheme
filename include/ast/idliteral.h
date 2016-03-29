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

	virtual std::shared_ptr<Object> eval(std::shared_ptr<Environment> e) {
		std::shared_ptr<Object> obj;
		obj = e->get(getName());

		if(!obj) throw *new UnboundException(getName());

		return obj;
	}
};



#endif/*_IDLITERAL_SCHEMER*/
