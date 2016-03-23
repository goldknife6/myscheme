#ifndef _LEXER_SCHEMER
#define _LEXER_SCHEMER

#include <iostream>
#include <string>
#include <map>
#include <deque>

#include <token.h>

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
	
	class Token;
	class IdToken;
	class StringToken;
	class NumberToken;
	class BooleanToken;
	class EOFToken;

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
	
	static void printToken(TokenType,std::string);
	
	std::string getString() { return tokenString;}

	Token &peek(int);
	Token &read();

	
private:
	std::istream &istr;
	std::string tokenString;
	std::map<std::string,TokenType> keyWord;
	std::deque<Token*> deque;

	int lineNo = 0;
	static EOFToken eofToken;

	TokenType getToken(void);
	void addToken(int,TokenType);
	bool fullQueue(int);

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


class Lexer::Token {
public:
	Token(int line) {
		lineNumber = line;
	}

	virtual bool isIdentifier() =0;
	virtual bool isNumber() =0;
	virtual bool isString() =0;
	virtual bool isBoolean() =0;
	virtual std::string getText() =0;
	virtual int getNumber() =0;
private:
	int lineNumber = 0;
};

class Lexer::EOFToken : public Lexer::Token {
public:
	EOFToken()
	: Token(-1) {
	}

	bool isIdentifier() {return true;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	std::string getText() {return str;};
	int getNumber() {return 0;};
private:
	std::string str;
};

class Lexer::IdToken : public Lexer::Token {
public:
	IdToken(int line,std::string)
	: Token(line) {
	}

	bool isIdentifier() {return true;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	std::string getText() {return str;};
	int getNumber() {return 0;};
private:
	std::string str;
};

class Lexer::BooleanToken : public Lexer::Token {
public:
	BooleanToken(int line,std::string)
	: Token(line) {
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return true;}
	std::string getText() {return "";};
	int getNumber() {return 0;};
private:
	bool value;
};

class Lexer::StringToken : public Lexer::Token {
public:
	StringToken(int line,std::string s)
	: Token(line),value(s) {
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return false;}
	bool isString() {return true;}
	bool isBoolean() {return false;}
	std::string getText() {return value;};
	int getNumber() {return 0;};
private:
	std::string value;
};

class Lexer::NumberToken : public Lexer::Token {
public:
	NumberToken(int line,std::string s)
	: Token(line) {
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return true;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	std::string getText() {return "";};
	int getNumber() {return value;};
private:
	int value;
};
#endif/*_LEXER_SCHEMER*/
