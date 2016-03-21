#ifndef _LEXER_SCHEMER
#define _LEXER_SCHEMER
#include <iostream>

class Lexer {
public:
	typedef enum {
		IDENTIFIER,BOOLEAN,NUMBER,STRING
	} TokenType;

	typedef enum {
		START,END
	} StateType;

	static const int MAXTOKEN = 48;

	Lexer(std::istream &is):istr(is) {}
	
	TokenType getToken(void);

private:
	std::istream &istr;
	char tokenBuffer[MAXTOKEN];
	
};






#endif/*_LEXER_SCHEMER*/
