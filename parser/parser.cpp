#include <parser.h>
#include <ast.h>

AstTree *Parser::beginParse()
{
	getToken();
	return expression();
}


AstTree *Parser::program()
{
	
}

AstTree *Parser::expression()
{
	AstTree *t = nullptr;
	if (t = variable()) {
		return t;
	} else if (t = literal()) {
		return t;
	} else if (t = lambdaExpression()) {
		return t;
	} else if (t = procedureCall()) {
		return t;
	}
	
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
			std::cout<<"procedureCall error"<<std::endl;	
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
	if (token->isIdentifier()) {
		AstTree *p = new IdLiteral(*token);
		getToken();
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
	
	if (token->isSpecial(Lexer::TokenType::LEFTPAREN)) {

		if (!peek(0)->isKey())
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
		return new Lambda(mydeque);
	}
}

AstTree *Parser::formals()
{
	std::deque<AstTree*> mydeque;

	if (token->isIdentifier()) {
		mydeque.push_back(variable());
		return new Formals(mydeque);
	} else if (token->isSpecial(Lexer::TokenType::LEFTPAREN)) {
		getToken();
		while (token->isIdentifier()) {
			mydeque.push_back(variable());	
		}
		getToken();
		return new Formals(mydeque);
	}

	//暂时不支持可变参数
	return nullptr;
}

AstTree *Parser::body()
{
	//暂时不支持Definition*
	return sequence();
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

AstTree *Parser::definition()
{
	return nullptr;
}


