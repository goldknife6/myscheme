#include "parser.h"

using T = Lexer::TokenType;

std::shared_ptr<AstTree> Parser::beginParse()
{
	return program();
}


std::shared_ptr<AstTree> Parser::program()
{
	return expression();
}

std::shared_ptr<AstTree> Parser::expression()
{
	std::shared_ptr<AstTree> t = nullptr;

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (t = lambdaExpression()) {
			
		} else if (t = conditional()) { 
			
		} else if (t = definition()) {
			
		} else if (t = procedureCall()) {
					
		}
	} else if (t = literal()) {
		
	} else if (t = variable()) {
		
	} else 
		return t;

	return std::shared_ptr<AstTree>(new Expression(t));
}

std::shared_ptr<AstTree> Parser::procedureCall()
{/*
	std::deque<AstTree*> mydeque;
	AstTree *p;

	if (peek(0)->isSpecial(T::LEFTPAREN) && 
		peek(1)->isSpecial(T::RIGHTPAREN)) {
		getToken();getToken();
		return nullptr;
	}

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		getToken();

		while (p = expression()) 
			mydeque.push_back(p);
		
		getToken();

		if(!token->isSpecial(T::RIGHTPAREN)) {
			throw *new UnbalancedException;
		}

		return new Procedure(mydeque);
	}*/
}

std::shared_ptr<AstTree> Parser::variable()
{
	if (peek(0)->isIdentifier()) {
		getToken();
		return std::shared_ptr<AstTree>(new Variable(*token));
	}
	return nullptr;
}

std::shared_ptr<AstTree> Parser::literal()
{
	std::shared_ptr<AstTree> p = nullptr;

	if (peek(0)->isNumber()) {
		getToken();
		p = std::shared_ptr<AstTree>(new NumberLiteral(*token));
	} else if (peek(0)->isString()) {	
		getToken();
		p = std::shared_ptr<AstTree>(new StringLiteral(*token));
	} else if (peek(0)->isBoolean()) {
		getToken();
		p = std::shared_ptr<AstTree>(new BooleanLiteral(*token));
	}

	return p; 
}


std::shared_ptr<AstTree> Parser::lambdaExpression()
{/*
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

		if(!token->isSpecial(T::RIGHTPAREN))
			throw *new UnbalancedException;

		return new Lambda(mydeque);
	}*/
	return nullptr;  
}

std::shared_ptr<AstTree> Parser::formals()
{/*
	std::deque<AstTree*> mydeque;
	bool flage = false;
	AstTree *p;

	if(p = variable()) {
		mydeque.push_back(p);
		return new Formals(mydeque,flage);
	}	

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		getToken();
		while(p = variable())
			mydeque.push_back(p);
		getToken();
		if(!token->isSpecial(T::RIGHTPAREN)) 
			throw *new UnbalancedException;	
		return new Formals(mydeque,flage);
	}
	

*/	return nullptr;
}

std::shared_ptr<AstTree> Parser::body()
{/*
	AstTree *p;
	std::deque<AstTree*> mydeque;
	while(p = definition())
		mydeque.push_back(p);
	return new Body(mydeque,sequence());*/
	return nullptr;
}

std::shared_ptr<AstTree> Parser::sequence()
{/*
	AstTree *p;
	std::deque<AstTree*> mydeque;

	while (p = expression())
		mydeque.push_back(p);	

	return new Sequence(mydeque);*/
	return nullptr;
}

std::shared_ptr<AstTree> Parser::conditional()
{/*
	std::deque<AstTree*> mydeque;
	AstTree*p;

	if (peek(0)->isSpecial(T::LEFTPAREN)) {

		if (!peek(1)->isKey(T::IF))
			return nullptr;
		
		getToken();getToken();

		while (p = expression())
			mydeque.push_back(p);

		getToken();
		if(!token->isSpecial(T::RIGHTPAREN))
			throw *new UnbalancedException;

		return new Conditional(mydeque);
	}
*/	return nullptr;
}

std::shared_ptr<AstTree> Parser::definition()
{
	std::deque<std::shared_ptr<AstTree>> mydeque;
	std::shared_ptr<AstTree> p;

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (peek(1)->isKey(T::DEFINE)) {
			getToken();getToken();

			if (peek(0)->isSpecial(T::LEFTPAREN)) {
				getToken();
				mydeque.push_back(variable());

				mydeque.push_back(defFormals());

				if(!getToken()->isSpecial(T::RIGHTPAREN))
					throw *new UnbalancedException;

				mydeque.push_back(body());
				getToken();
				if(!token->isSpecial(T::RIGHTPAREN))
					throw *new UnbalancedException;
				return std::shared_ptr<AstTree>(new DefinitionVarlist(mydeque));
				
			} else {
				mydeque.push_back(variable());
				while (p = expression()) {
					mydeque.push_back(p);
				}
				getToken();
				if(!token->isSpecial(T::RIGHTPAREN))
					throw *new UnbalancedException;
				return std::shared_ptr<AstTree>(new DefinitionNormal(mydeque));
			}
		}
	}
	
	return nullptr;

}


std::shared_ptr<AstTree> Parser::defFormals()
{
/*
	std::deque<AstTree*> mydeque;
	AstTree *p = nullptr;

	while (p = variable()) {
		mydeque.push_back(p);
	}

	return new DefFormals(mydeque);
*/	return nullptr;
}


