#ifndef _PARSER_SCHEMER
#define _PARSER_SCHEMER

#include "lexer.h"
#include "ast.h"

class Parser {
public:
	Parser(Lexer& l):lexer(l) {};
	std::shared_ptr<AstTree> beginParse();


private:
	Lexer &lexer;
	Lexer::Token *token;

	Lexer::Token *getToken() {
		token = &lexer.read();
		return token;
	}
	Lexer::Token *peek(int i) {
		return 	&lexer.peek(i);
	}

	std::shared_ptr<AstTree> program();
	std::shared_ptr<AstTree> expression();
	std::shared_ptr<AstTree> definition();
	std::shared_ptr<AstTree> procedureCall();
	std::shared_ptr<AstTree> variable();
	std::shared_ptr<AstTree> literal();
	std::shared_ptr<AstTree> lambdaExpression();
	std::shared_ptr<AstTree> formals();
	std::shared_ptr<AstTree> body();
	std::shared_ptr<AstTree> sequence();
	std::shared_ptr<AstTree> conditional();
	std::shared_ptr<AstTree> defFormals();
	std::shared_ptr<AstTree> assignment();
};





#endif/*_PARSER_SCHEMER*/
