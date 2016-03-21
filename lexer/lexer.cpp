#include <lexer.h>
#include <chartype.h>

Lexer::TokenType Lexer::getToken(void)
{
	TokenType currentToken;
	StateType currentState = START;
	int stringBufIndex = 0;

	while (currentState != DONE) {
		char currentChar = getChar();
		bool flage = true;

		switch (currentState) {
		case START:
			if (isInital(currentChar)) {
				currentState = INID;
			} else if (isDigit(currentChar)) {
				currentState = INNUM;
			} else if (currentChar == '#') {
				flage = false;
				currentState = INBOOL;
			} else if (currentChar == '"') {
				flage = false;
				currentState = INSTRING;			
			} else if (currentChar == ';') {
				flage = false;
				currentState = INCOMMENT;
			} else if ((currentChar == ' ') || 
						(currentChar == '\t') || 
						(currentChar == '\n')) {
           		flage = false;
			} else {
					currentState = DONE;
					switch (currentChar) {
					case '(':
						currentToken = LEFTPAREN;
						break;
					case ')':
						currentToken = RIGHTPAREN;
						break;
					case '.':
						currentToken = DOT;
						break;
					default:
						currentState = ERROR;
					}	
			}
			break;
		case INID:
			if (!isSubsequent(currentChar)) {
				currentState = DONE;
				currentToken = IDENTIFIER;
				ungetChar();
				flage = false;
			}
			break;
		case INNUM:
			break;
		case INBOOL:
			break;
		case INSTRING:
			break;
		case INCOMMENT:
			break;
		default:
			std::cout<<"lexer error\n";
		}
		
		if (flage && stringBufIndex < MAXTOKEN) {
			tokenBuffer[stringBufIndex++] = currentChar;
		} else {
			/*
			*/
		}

	}

	tokenBuffer[stringBufIndex] = '\0';
/*
	if (currentToken == ID)
		currentToken = reservedLookup(tokenString);	
*/

	return currentToken;
}

void Lexer::printToken(TokenType token)
{
	using namespace std;

	switch (token) {
	case IDENTIFIER:
		cout<<"IDENTIFIER";
		break;
	case BOOLEAN:
		cout<<"BOOLEAN";
		break;
	case NUMBER:
		cout<<"NUMBER";
		break;
	case STRING:
		cout<<"STRING";
		break;
	case LAMBDA:
		cout<<"LAMBDA";
		break;
	case IF:
		cout<<"IF";
		break;
	case SET:
		cout<<"SET";
		break;
	case BEGIN:
		cout<<"BEGIN";
		break;
	case COND:
		cout<<"COND";
		break;
	case AND:
		cout<<"AND";
		break;
	case OR:
		cout<<"OR";
		break;
	case CASE:
		cout<<"CASE";
		break;
	case LET:
		cout<<"LET";
		break;
	case DELAY:
		cout<<"DELAY";
		break;
	case LEFTPAREN:
		cout<<"LEFTPAREN";
		break;
	case RIGHTPAREN:
		cout<<"RIGHTPAREN";
		break;
	case APOST:
		cout<<"APOST";
		break;
	case DOT:
		cout<<"DOT";
		break;
	}
	cout<<endl;
}
