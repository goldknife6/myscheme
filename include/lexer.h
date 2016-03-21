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
		LEFTPAREN,RIGHTPAREN,APOST/*'*/
		
	} TokenType;

	typedef enum {
		START,END,
		INID,INNUM,INBOOL,INSTRING,INCOMMENT
	} StateType;

	static const int MAXTOKEN = 48;

	Lexer(std::istream &is):istr(is) {}
	
	TokenType getToken(void);

private:
	std::istream &istr;
	char tokenBuffer[MAXTOKEN];
};






#endif/*_LEXER_SCHEMER*/
