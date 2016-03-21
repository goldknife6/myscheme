#ifndef _LEXER_SCHEMER
#define _LEXER_SCHEMER
#include <iostream>
#include <string>

class Lexer {
public:
	typedef enum {
		ENDFILE,ERROR,
		IDENTIFIER,BOOLEAN,NUMBER,STRING,
		/*keyword*/
		LAMBDA,IF,SET,BEGIN,COND,AND,OR,CASE,LET,DELAY,QUOTE,
		/* special symbols */
		LEFTPAREN,RIGHTPAREN,APOST/*'*/,DOT
		
	} TokenType;

	typedef enum {
		START,DONE,
		INID,INNUM1,INNUM2,INBOOL,INSTRING,INCOMMENT
	} StateType;

	static const int MAXTOKEN = 48;

	Lexer(std::istream &is):istr(is) {}
	
	TokenType getToken(void);

	static void printToken(TokenType,std::string);
	
	std::string getString() { return tokenString;}

private:
	std::istream &istr;
	std::string tokenString;
	char getChar() {
		return istr.get();
	}
	
	void ungetChar() {
		istr.unget();
	}
};






#endif/*_LEXER_SCHEMER*/
