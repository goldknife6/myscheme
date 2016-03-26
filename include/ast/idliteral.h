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

	virtual Object *eval(Env *o) override {
		
	}
};



#endif/*_IDLITERAL_SCHEMER*/
