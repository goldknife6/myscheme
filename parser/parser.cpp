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
	} else if (t = procedureCall()) {
		return t;
	} else if (t = lambdaExpression()) {
		return t;
	}
	
	return nullptr;
}

AstTree *Parser::procedureCall()
{
	std::deque<AstTree*> mydeque;
	Lexer::SpecialToken *tmp;

	
	if (token->isSpecial()) {
		tmp = dynamic_cast<Lexer::SpecialToken*>(token);

		if (tmp && tmp->getType() != Lexer::TokenType::LEFTPAREN)
			return nullptr;

		getToken();
		AstTree *p = expression();
		if (p == nullptr) {
			std::cout<<"procedureCall error"<<std::endl;		
		}
		mydeque.push_back(p);

		while ((p = expression()) != nullptr) {
			mydeque.push_back(p);
		}
		
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
	return nullptr;
}

AstTree *Parser::definition()
{
	return nullptr;
}


