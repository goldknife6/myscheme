#include <parser.h>
#include <ast.h>

AstTree *Parser::beginParse()
{
	return expression();
}


AstTree *Parser::program()
{
	
}

AstTree *Parser::expression()
{
	AstTree *t = nullptr;

	if (peek(0)->isSpecial(Lexer::TokenType::LEFTPAREN)) {
		//getToken();
		if (t = lambdaExpression()) {
			return t;
		} else if (t = conditional()) { 
			return t;
		} else if (t = procedureCall()) {
			return t;
		}
	} else if (t = literal()) {
		return t;
	} else if (t = variable())
			return t;
	
	return nullptr;
}

AstTree *Parser::procedureCall()
{
	std::deque<AstTree*> mydeque;
	Lexer::SpecialToken *tmp;

	
	if (token->isSpecial(Lexer::TokenType::LEFTPAREN)) {
		getToken();

		AstTree *p = expression();
		if (p == nullptr) {
			std::cout<<"Ill-formed special form:procedure call"<<std::endl;
			while(1);
		}
		mydeque.push_back(p);

		while ((p = expression()) != nullptr) {
			mydeque.push_back(p);
			//std::cout<<p->toString()<<std::endl;
		}
		getToken();
		return new Procedure(mydeque);
	}
}

AstTree *Parser::variable()
{
	if (peek(0)->isIdentifier()) {
		getToken();
		AstTree *p = new IdLiteral(*token);
		return p;
	}
	return nullptr;
}

AstTree *Parser::literal()
{
	AstTree *p = nullptr;

	if (token->isNumber()) {
		p = new NumLiteral(*token);
	} else if (token->isString()) {
		p = new StrLiteral(*token);
	} else if (token->isBoolean()) {
		p = new BoolLiteral(*token);
	} else {
		return nullptr;
	}

	getToken();

	return p; 
}

AstTree *Parser::lambdaExpression()
{
	std::deque<AstTree*> mydeque;
	Lexer::SpecialToken *tmp;
	AstTree *p;
	
	if (peek(0)->isSpecial(Lexer::TokenType::LEFTPAREN)) {

		if (!peek(1)->isKey(Lexer::TokenType::LAMBDA))
			return nullptr;
		
		getToken();getToken();
		p = formals();
		if (p == nullptr) {
			std::cout<<"lambdaExpression error"<<std::endl;	
			while(1);
		}
		mydeque.push_back(p);

		p = body();
		mydeque.push_back(p);

		getToken();
		if(!token->isSpecial(Lexer::TokenType::RIGHTPAREN)) {
			std::cout<<"lambda error"<<token->getText()<<std::endl;	
		}

		return new Lambda(mydeque);
	}
}

AstTree *Parser::formals()
{
	std::deque<AstTree*> mydeque;
	if (peek(0)->isIdentifier()) {
		mydeque.push_back(variable());
		return new Formals(mydeque);
	} else if (peek(0)->isSpecial(Lexer::TokenType::LEFTPAREN)) {
		getToken();
		while (peek(0)->isIdentifier()) {
			mydeque.push_back(variable());	
		}
		if(!getToken()->isSpecial(Lexer::TokenType::RIGHTPAREN))
			std::cout<<"formals error"<<std::endl;	
		return new Formals(mydeque);
	}

	//暂时不支持可变参数
	return nullptr;
}

AstTree *Parser::body()
{
	//暂时不支持Definition*
	AstTree *p = sequence();
	return p;
}

AstTree *Parser::sequence()
{
	//暂时不支持Command
	AstTree *p;
	std::deque<AstTree*> mydeque;

	p = expression();

	if (p == nullptr)
		return nullptr;

	mydeque.push_back(p);

	while (p = expression()) {
		mydeque.push_back(p);	
	}

	return new Sequence(mydeque);
}


AstTree *Parser::conditional()
{
	std::deque<AstTree*> mydeque;
	AstTree*p;

	if (token->isSpecial(Lexer::TokenType::LEFTPAREN)) {

		if (!peek(0)->isKey(Lexer::TokenType::IF))
			return nullptr;
		
		getToken();getToken();
		p = expression();
		if (p != nullptr)
			mydeque.push_back(p);
		else
			return nullptr;
		
		p = expression();
		if (p != nullptr)
			mydeque.push_back(p);
		else
			return nullptr;


		p = expression();
		if (p != nullptr)
			mydeque.push_back(p);
		if(!getToken()->isKey(Lexer::TokenType::RIGHTPAREN))
			std::cout<<"conditional error"<<std::endl;	
		
		return new Conditional(mydeque);
	}
	return nullptr;
}


AstTree *Parser::definition()
{
	return nullptr;
}


