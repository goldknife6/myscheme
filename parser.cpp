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
			return new Expression(t);
		} else if (t = conditional()) { 
			return new Expression(t);
		} else if (t = definition()) {
			return new Expression(t);
		} else if (t = procedureCall()) {
			return new Expression(t);		
		}
	} else if (t = literal()) {
		return new Expression(t);
	} else if (t = variable()) {
		return new Expression(t);
	} else {
		return nullptr;
	}

}

AstTree *Parser::procedureCall()
{
	std::deque<AstTree*> mydeque;
	AstTree *p;

	if (peek(0)->isSpecial(T::LEFTPAREN) && 
		peek(1)->isSpecial(T::RIGHTPAREN)) {
		getToken();getToken();
		return nullptr;
	}

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		getToken();

		while (p = expression()) {
			mydeque.push_back(p);
		}
		
		getToken();

		if(!token->isSpecial(T::RIGHTPAREN)) {
			throw *new UnbalancedException;
		}

		return new Procedure(mydeque);
	}
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
	}

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
		
		mydeque.push_back(formals());

		mydeque.push_back(body());

		getToken();

		if(!token->isSpecial(T::RIGHTPAREN)) {
			throw *new UnbalancedException;
		}

		return new Lambda(mydeque);
	}
}

AstTree *Parser::formals()
{
	std::deque<AstTree*> mydeque;
	bool flage = false;
	AstTree *p;

	p = variable();

	if(p) {
		mydeque.push_back(p);
		return new Formals(mydeque,flage);
	}	

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		getToken();
		
		while(p = variable()) {
			mydeque.push_back(p);
		}

		getToken();
		if(!token->isSpecial(T::RIGHTPAREN)) {
			std::cout<<"Unbalanced close parenthesis"<<std::endl;	
		}

		return new Formals(mydeque,flage);
	}
	

	return nullptr;
}

AstTree *Parser::body()
{
	AstTree *p;
	std::deque<AstTree*> def;
	std::deque<AstTree*> seq;

	while(p = definition())
		def.push_back(p);
//bug
	mydeque.push_back(sequence());

	return new Body(mydeque);
}

AstTree *Parser::sequence()
{
	AstTree *p;
	std::deque<AstTree*> mydeque;

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

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (peek(1)->isKey(T::DEFINE)) {
			getToken();getToken();

			if (peek(0)->isSpecial(T::LEFTPAREN)) {
				getToken();
				flage = true;
				mydeque.push_back(variable());

				mydeque.push_back(defFormals());

				if(!getToken()->isSpecial(T::RIGHTPAREN))
					throw *new UnbalancedException;

				mydeque.push_back(body());
				
			} else {
				mydeque.push_back(variable());
				while (p = expression()) {
					mydeque.push_back(p);
				}
				
			}
			getToken();
			if(!token->isSpecial(T::RIGHTPAREN))
				throw *new UnbalancedException;

			return new Definition(mydeque,flage);
		}
	}
	
	return nullptr;
}



AstTree *Parser::defFormals()
{
	std::deque<AstTree*> mydeque;
	AstTree *p = nullptr;

	while (p = variable()) {
		mydeque.push_back(p);
	}

	return new DefFormals(mydeque);
}


