#ifndef _LEXER_SCHEMER
#define _LEXER_SCHEMER

#include <iostream>
#include <string>
#include <map>

class Lexer {
public:
	typedef enum {
		ENDFILE,ERROR,
		IDENTIFIER,BOOLEAN,NUMBER,STRING,
		/*keyword*/
		LAMBDA,IF,SET,BEGIN,COND,AND,OR,CASE,LET,DELAY,QUOTE,DEFINE,ELSE,
		/* special symbols */
		LEFTPAREN,RIGHTPAREN,APOST/*'*/,DOT
		
	} TokenType;

	typedef enum {
		START,DONE,
		INID,INNUM1,INNUM2,INBOOL,INSTRING,INCOMMENT
	} StateType;

	static const int MAXTOKEN = 48;

	Lexer(std::istream &is)
	:istr(is) 
	{
		keyWord["lambda"] = LAMBDA;
		keyWord["if"] = IF;
		keyWord["set!"] = SET;
		keyWord["begin"] = BEGIN;
		keyWord["cond"] = COND;
		keyWord["and"] = AND;
		keyWord["or"] = OR;
		keyWord["case"] = CASE;
		keyWord["let"] = LET;		
		keyWord["delay"] = DELAY;
		keyWord["quote"] = QUOTE;
		keyWord["define"] = DEFINE;
		keyWord["else"] = ELSE;
	}
	
	TokenType getToken(void);

	static void printToken(TokenType,std::string);
	
	std::string getString() { return tokenString;}

private:
	std::istream &istr;
	std::string tokenString;
	std::map<std::string,TokenType> keyWord;
	int lineNo = 0;

	char getChar() {
		char c = istr.get();
		if (c == '\n')
			lineNo++;
		return c;
	}
	
	void ungetChar() {
		istr.unget();
	}

	TokenType reservedLookup(std::string s) {
		std::map<std::string,TokenType>::iterator it;
		it = keyWord.find(s);
		if (it != keyWord.end())
			return it->second;
		return IDENTIFIER;	
	}
};






#endif/*_LEXER_SCHEMER*/
