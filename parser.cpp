#include "parser.h"

using T = Lexer::TokenType;

std::shared_ptr<AstTree> Parser::beginParse()
{
	return program();
}


std::shared_ptr<AstTree> Parser::program()
{
	std::shared_ptr<AstTree> t = nullptr;
	if (t = definition()) {
			
	} else if (t = expression()) { 
			
	} else {
		getToken();
	}
	return t;
}

std::shared_ptr<AstTree> Parser::expression()
{
	std::shared_ptr<AstTree> t;

	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (t = lambdaExpression()) {
			
		} else if (t = conditional()) { 
			
		} else if (t = assignment()) { 
			
		} else if (t = derivedExpression()) {
					
		}  else if (t = procedureCall()) {
					
		} else {
			return nullptr;
		}
	} else if (t = literal()) {
		
	} else if (t = variable()) {
		
	} else {
		if(peek(0)->isKey()) {
			getToken();
			throw *new KeywordException(peek(0)->getText());
		}
		//getToken();
		return nullptr;
	}
	return std::shared_ptr<AstTree>(new Expression(t));
}

std::shared_ptr<AstTree> Parser::procedureCall()
{
	std::shared_ptr<AstTree> p;
	std::deque<std::shared_ptr<AstTree>> mydeque;

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

		return std::shared_ptr<AstTree>(new Procedure(mydeque));
	}
	return nullptr;
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
{
	std::shared_ptr<AstTree> p;
	std::deque<std::shared_ptr<AstTree>> mydeque;

	while(p = definition())
		mydeque.push_back(p);

	return std::shared_ptr<AstTree>(new Body(mydeque,sequence()));
}

std::shared_ptr<AstTree> Parser::sequence()
{
	std::shared_ptr<AstTree> p;
	std::deque<std::shared_ptr<AstTree>> mydeque;

	while (p = expression())
		mydeque.push_back(p);	

	return std::shared_ptr<AstTree>(new Sequence(mydeque));
}

std::shared_ptr<AstTree> Parser::conditional()
{
	std::shared_ptr<AstTree> p = nullptr;
	std::deque<std::shared_ptr<AstTree>> mydeque;

	if (peek(0)->isSpecial(T::LEFTPAREN)) {

		if (!peek(1)->isKey(T::IF))
			return nullptr;
		
		getToken();getToken();
		
		while (p = expression())
			mydeque.push_back(p);
		getToken();
		if(!token->isSpecial(T::RIGHTPAREN))
			throw *new UnbalancedException;

		return std::shared_ptr<AstTree>(new Conditional(mydeque));
	}
	return nullptr;
}

std::shared_ptr<AstTree> Parser::assignment()
{
	std::shared_ptr<AstTree> p = nullptr;
	std::deque<std::shared_ptr<AstTree>> mydeque;

	if (peek(0)->isSpecial(T::LEFTPAREN)) {

		if (!peek(1)->isKey(T::SET))
			return nullptr;
		
		getToken();getToken();
		
		p = variable();
		mydeque.push_back(p);

		while (p = expression())
			mydeque.push_back(p);
		getToken();
		if(!token->isSpecial(T::RIGHTPAREN))
			throw *new UnbalancedException;

		return std::shared_ptr<AstTree>(new Assignment(mydeque));
	}
	return nullptr;
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

	std::deque<std::shared_ptr<AstTree>> mydeque;
	std::shared_ptr<AstTree> p = nullptr;

	while (p = variable()) {
		mydeque.push_back(p);
	}

	return std::shared_ptr<AstTree>(new DefFormals(mydeque));
}

std::shared_ptr<AstTree> Parser::condClause()
{

	std::deque<std::shared_ptr<AstTree>> mydeque;
	std::shared_ptr<AstTree> p = nullptr;

	if (!peek(0)->isSpecial(T::LEFTPAREN))
		return nullptr;

	getToken();

	p = expression();
	mydeque.push_back(p);

	if(p = sequence())
		mydeque.push_back(p);

	getToken();
	if (!token->isSpecial(T::RIGHTPAREN))
		throw *new UnbalancedException("2");

	return std::shared_ptr<AstTree>(new Condclause(mydeque));
}

std::shared_ptr<AstTree> Parser::derivedExpression()
{
	std::deque<std::shared_ptr<AstTree>> mydeque;
	std::shared_ptr<AstTree> p;
	if (peek(0)->isSpecial(T::LEFTPAREN)) {
		if (peek(1)->isKey(T::COND)) {
			getToken();getToken();
			while (p = condClause()) {
				mydeque.push_back(p);
			}
			getToken();
			if(!token->isSpecial(T::RIGHTPAREN))
				throw *new UnbalancedException;
			return std::shared_ptr<AstTree>(new DerivedExpression(mydeque));
		}
	}
	return nullptr;
}


