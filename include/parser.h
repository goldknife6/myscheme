#ifndef _PARSER_SCHEMER
#define _PARSER_SCHEMER

#include <lexer.h>
#include <ast.h>

class Parser {
public:
	Parser(Lexer& l):lexer(l) {};
	AstTree *beginParse();


private:
	Lexer &lexer;
	Lexer::Token *token;

	Lexer::Token * getToken() {
		token = &lexer.read();
		return token;
	}
	Lexer::Token *peek(int i) {
		return 	&lexer.peek(i);
	}

	AstTree *program();
	AstTree *expression();
	AstTree *definition();
	AstTree *procedureCall();
	AstTree *variable();
	AstTree *literal();
	AstTree *lambdaExpression();
	AstTree *formals();
	AstTree *body();
	AstTree *sequence();
	AstTree *conditional();
	AstTree *defFormals();
};





#endif/*_PARSER_SCHEMER*/
