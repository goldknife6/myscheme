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
		if (t = lambdaExpression()) {
			return t;
		} else if (t = conditional()) { 
			return t;
		} else if (t = definition()) {
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
	AstTree *t = nullptr;
	return t;
}

AstTree *Parser::variable()
{
	if (peek(0)->isIdentifier()) {
		getToken();
		return new IdLiteral(*token);
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
	AstTree *t = nullptr;
	return t;
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
	AstTree *p;
	std::deque<AstTree*> mydeque;

	while(p = definition())
		mydeque.push_back(p);

	mydeque.push_back(sequence());

	return new Body(mydeque);
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

	if (peek(0)->isSpecial(T::LEFTPAREN)) {

		if (!peek(1)->isKey(T::IF))
			return nullptr;
		
		getToken();getToken();

		while (p = expression())
			mydeque.push_back(p);

		getToken();
		if(!token->isSpecial(T::RIGHTPAREN)) {
			std::cout<<"Unbalanced close parenthesis"<<std::endl;
			return nullptr;
		}
		return new Conditional(mydeque);
	}
	return nullptr;
}


AstTree *Parser::definition()
{
	std::deque<AstTree*> mydeque;
	AstTree *p;
	bool flage = false;
//暂不支持DefFormals

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (peek(1)->isKey(T::DEFINE)) {
			getToken();getToken();

			if (peek(0)->isSpecial(T::LEFTPAREN)) {
				getToken();
				flage = true;
				mydeque.push_back(variable());

				mydeque.push_back(defFormals());

				if(!getToken()->isSpecial(T::RIGHTPAREN))
					std::cout<<"definition error"<<std::endl;

				mydeque.push_back(body());
				
			} else {
				mydeque.push_back(variable());
				while (p = expression()) {
					mydeque.push_back(p);
				}
				
			}
			
			if(!getToken()->isSpecial(T::RIGHTPAREN))
				std::cout<<"Unbalanced close parenthesis"<<std::endl;
			return new Definition(mydeque,flage);
		}
	}
	
	return nullptr;
}



AstTree *Parser::defFormals()
{
	std::deque<AstTree*> mydeque;
	AstTree *p = nullptr;
	bool flage = false;

	while (p = variable()) {
		mydeque.push_back(p);
	}

	if (peek(0)->isSpecial(T::DOT)) {
		getToken();
		flage = true;

		while (p = variable()) {
			mydeque.push_back(p);
		}

		p = new DefFormals(mydeque,flage);

		if (!peek(0)->isSpecial(T::RIGHTPAREN)) {
			std::cout<<";Ill-formed dotted list:";
			std::cout<<p->toString()<<std::endl;
		}
		return p;
	}

	p = new DefFormals(mydeque,flage);

	return p ;
}

