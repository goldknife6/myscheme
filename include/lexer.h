#ifndef _LEXER_SCHEMER
#define _LEXER_SCHEMER

#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <sstream>

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
	class KeyToken;
	class SpecialToken;
	class EOFToken;
	class ERRToken;
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

	int lineNo = 1;
	

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
	virtual bool isKey() =0;
	virtual bool isSpecial() =0;
	virtual	bool isEOF() =0;
	virtual	bool isERROR() =0;

	virtual std::string getText() =0;
	virtual int getNumber() =0;

	int getLineNumber() { 
		return lineNumber; 
	}

	friend std::ostream& operator<< (std::ostream &os,Token &t)  
	{  
		std::string s;
		os<<t.getText()<<std::endl;
		if (t.isEOF()) 
			os.setstate(std::ostream::eofbit);//iostate 
		return os;  
	}  

private:
	int lineNumber;
};



class Lexer::EOFToken : public Lexer::Token {
public:
	EOFToken()
	: Token(-1) {
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	bool isKey() {return false;}
	bool isSpecial() {return false;}
	bool isEOF() {return true;}
	bool isERROR() {return false;}
	std::string getText() {return "end of file";}
	int getNumber() {return -1;};
};



class Lexer::ERRToken : public Lexer::Token {
public:
	ERRToken(int line,std::string s)
	: Token(line),value(s) {
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	bool isKey() {return false;}
	bool isSpecial() {return false;}
	bool isEOF() {return false;}
	bool isERROR() {return true;}


	std::string getText() {
		std::ostringstream ost;
		ost<<getLineNumber();
		return "error occured at line " + ost.str() + ",  " +value;
	}

	int getNumber() {return -1;};
private:
	std::string value;
};




class Lexer::IdToken : public Lexer::Token {
public:
	IdToken(int line,std::string s)
	: Token(line),str(s) {
	}

	bool isIdentifier() {return true;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	bool isKey() {return false;}
	bool isSpecial() {return false;}
	bool isEOF() {return false;}
	bool isERROR() {return false;}


	std::string getText() {return "identifier  " + str;}
	int getNumber() {return 0;};
private:
	std::string str;
};




class Lexer::BooleanToken : public Lexer::Token {
public:
	BooleanToken(int line,std::string s)
	: Token(line) {
		if(s == "t")
			value = true;
		else
			value = false;
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return false;}
	bool isString() {return false;}
	bool isBoolean() {return true;}
	bool isKey() {return false;}
	bool isSpecial() {return false;}
	bool isEOF() {return false;}
	bool isERROR() {return false;}

	std::string getText() {
		if(value)
			return "boolean  true";
		else
			return "boolean  false";
	}
	int getNumber() {return 0;}
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
	bool isKey() {return false;}
	bool isSpecial() {return false;}
	bool isEOF() {return false;}
	bool isERROR() {return false;}

	std::string getText() {return "string  "+value;};
	int getNumber() {return 0;};
private:
	std::string value;
};





class Lexer::NumberToken : public Lexer::Token {
public:
	NumberToken(int line,std::string s)
	: Token(line) {
		std::istringstream istr(s);
		istr>>value;
	}

	bool isIdentifier() {return false;}
	bool isNumber() {return true;}
	bool isString() {return false;}
	bool isBoolean() {return false;}
	bool isKey() {return false;}
	bool isSpecial() {return false;}
	bool isEOF() {return false;}
	bool isERROR() {return false;}

	std::string getText() {
		std::ostringstream istr;
		istr<<value;
		return "number  "+istr.str();
	}

	int getNumber() {return value;}
private:
	int value;
};





class Lexer::KeyToken : public Lexer::Token {
public:
	KeyToken(int line,TokenType type)
	: Token(line),value(type) {
	}

	bool isIdentifier() override {
		return false;
	}
	bool isNumber() override {
		return false;
	}
	bool isString() override {
		return false;
	}
	bool isBoolean() override {
		return false;
	}
	bool isKey() override {
		return true;
	}
	bool isSpecial() override {
		return false;
	}
	bool isEOF() override {
		return false;
	}
	bool isERROR() override {
		return false;
	}

	
	std::string getText() {
		switch(value) {
		case LAMBDA:
			return "keyword  LAMBDA";
		case IF:
			return "keyword  IF";
		case SET:
			return "keyword  SET";
		case BEGIN:
			return "keyword  BEGIN";
		case COND:
			return "keyword  COND";
		case AND:
			return "keyword  AND";
		case OR:
			return "keyword  OR";
		case CASE:
			return "keyword  CASE";
		case LET:
			return "keyword  LET";
		case DELAY:
			return "keyword  DELAY";
		case QUOTE:
			return "keyword  QUOTE";
		case DEFINE:
			return "keyword  DEFINE";
		case ELSE:
			return "keyword  ELSE";
		}
	}

	int getNumber() {return 0;};
	TokenType getType() {return value;};
private:
	TokenType value;
};





class Lexer::SpecialToken : public Lexer::Token {
private:
	TokenType value;

public:
	SpecialToken(int line,TokenType type)
	: Token(line),value(type) {
	}

	bool isIdentifier() override {
		return false;
	}
	bool isNumber() override {
		return false;
	}
	bool isString() override {
		return false;
	}
	bool isBoolean() override {
		return false;
	}
	bool isKey() override {
		return false;
	}
	bool isSpecial() override {
		return true;
	}
	bool isEOF() override {
		return false;
	}
	bool isERROR() override {
		return false;
	}

	std::string getText() {
		switch(value) {
		case LEFTPAREN:
			return "LEFTPAREN (";
		case RIGHTPAREN:
			return "RIGHTPAREN )";
		case APOST:
			return "APOST";
		case DOT:
			return "DOT .";
		}
	}

	int getNumber() {
		return 0;
	}

	TokenType getType() {
		return value;
	}
};
#endif/*_LEXER_SCHEMER*/
