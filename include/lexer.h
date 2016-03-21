#ifndef _LEXER_SCHEMER
#define _LEXER_SCHEMER
#include <iostream>

class Lexer {
public:
	typedef enum {
		IDENTIFIER,BOOLEAN,NUMBER,STRING,
		/*keyword*/
		LAMBDA,IF,SET,BEGIN,COND,AND,OR,CASE,LET,DELAY,
		/* special symbols */
		LEFTPAREN,RIGHTPAREN,APOST/*'*/,DOT
		
	} TokenType;

	typedef enum {
		START,DONE,ERROR,
		INID,INNUM,INBOOL,INSTRING,INCOMMENT
	} StateType;

	static const int MAXTOKEN = 48;

	Lexer(std::istream &is):istr(is) {}
	
	TokenType getToken(void);

	static void printToken(TokenType);

private:
	std::istream &istr;
	char tokenBuffer[MAXTOKEN];

	char getChar() {
		return istr.get();
	}
	
	void ungetChar() {
		istr.unget();
	}
};






#endif/*_LEXER_SCHEMER*/
