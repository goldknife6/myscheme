#include <parser.h>
#include <ast.h>

using T = Lexer::TokenType;

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

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
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

	
	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		getToken();

		AstTree *p = expression();
		if (p == nullptr) {
			std::cout<<"Ill-formed special form:procedure call"<<std::endl;
			return nullptr;
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

	if (peek(0)->isNumber()) {
		getToken();
		p = new NumLiteral(*token);
	} else if (peek(0)->isString()) {	
		getToken();
		p = new StrLiteral(*token);
	} else if (peek(0)->isBoolean()) {
		getToken();
		p = new BoolLiteral(*token);
	} else return nullptr;

	return p; 
}

AstTree *Parser::lambdaExpression()
{
	std::deque<AstTree*> mydeque;
	Lexer::SpecialToken *tmp;
	AstTree *p;
	
	if (peek(0)->isSpecial(T::LEFTPAREN)) {

		if (!peek(1)->isKey(T::LAMBDA))
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
		if(!token->isSpecial(T::RIGHTPAREN)) {
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
	} else if (peek(0)->isSpecial(T::LEFTPAREN)) {
		getToken();
		while (peek(0)->isIdentifier()) {
			mydeque.push_back(variable());	
		}
		if(!getToken()->isSpecial(T::RIGHTPAREN))
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

	if (peek(0)->isSpecial(Lexer::TokenType::LEFTPAREN)) {

		if (!peek(1)->isKey(Lexer::TokenType::IF))
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

		if(!getToken()->isSpecial(T::RIGHTPAREN))
			std::cout<<"conditional error"<<std::endl;	
		
		return new Conditional(mydeque);
	}
	return nullptr;
}


AstTree *Parser::definition()
{
	AstTree *p = nullptr,*t = nullptr;
	bool flage = false;

	std::deque<AstTree*> mydeque;
//暂不支持DefFormals

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (peek(1)->isKey(T::DEFINE)) {
			getToken();getToken();

			if (peek(0)->isSpecial(T::LEFTPAREN)) {
				getToken();
				flage = true;
			}

			p = variable();
			if (!p) {
				std::cout<<"definition error"<<std::endl;
				return nullptr;
			}
			mydeque.push_back(p);

			if(!flage)
				goto Lable;

			while(p = variable()) {
				mydeque.push_back(p);
			}	
			
			if(!getToken()->isSpecial(T::RIGHTPAREN))
				std::cout<<"definition error"<<std::endl;
Lable:
			t = expression();
			if (!t) {
				std::cout<<"definition error"<<std::endl;
				return nullptr;
			}
			mydeque.push_back(t);
			if(!getToken()->isSpecial(T::RIGHTPAREN))
				std::cout<<"definition error"<<std::endl;

			return new Definition(mydeque,t);
		}
	}

	if(!getToken()->isSpecial(T::RIGHTPAREN))
			std::cout<<"definition error"<<std::endl;
	return p;
}


