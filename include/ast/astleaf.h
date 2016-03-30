#ifndef _ASTLEAF_SCHEMER
#define _ASTLEAF_SCHEMER

#include "asttree.h"

#include <vector>
#include <string>

#include <lexer.h>

class AstLeaf : public AstTree {
public:
	AstLeaf(Lexer::Token &t):tokenData(t) {
				
	}

	virtual int numChildren() override {
		return 0;
	}

	virtual std::shared_ptr<AstTree> child(int i) override {
		throw *new SchemeError("AstLeaf child() called");
	};

	virtual std::string toString() override {
		return tokenData.getText();
	}

	Lexer::Token &token() {
		return tokenData; 
	}

private:
	Lexer::Token &tokenData;
};



#endif/*_ASTLEAF_SCHEMER*/
