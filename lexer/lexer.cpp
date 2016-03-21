#include <lexer.h>

#include <chartype.h>
Lexer::TokenType Lexer::getToken(void)
{
	TokenType currentToken;
	StateType currentState = START;
	int stringBufIndex = 0;

	while (currentState != END) {
		char currentChar = istr.get();
		bool flage = true;

		switch (currentState) {
		case START:
			switch (currentChar) {
			}
		case INID:
		case INNUM:
		case INBOOL:
		case INSTRING:
		case INCOMMENT:
		default:
			std::cout<<"Lexer error\n";
		}
		
	}


	return currentToken;
}
