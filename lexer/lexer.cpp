#include <lexer.h>
#include <chartype.h>

Lexer::TokenType Lexer::getToken(void)
{
	TokenType currentToken;
	StateType currentState = START;
	int stringBufIndex = 0;
	char tokenBuffer[MAXTOKEN];

	while (currentState != DONE) {
		char currentChar = getChar();
		bool flage = true;

		switch (currentState) {
		case START:
			if (isInital(currentChar)) {
				currentState = INID;
			} else if (isDigit(currentChar)) {
				currentState = INNUM2;
			} else if (isSign(currentChar)) {
				char c = getChar();
				if (isDigit(c)) {
					currentState = INNUM1;
				} else {
					currentState = DONE;
					if (isDelimiter(c)) {
						currentToken = IDENTIFIER;
					} else {
						currentToken = ERROR;
					}
				}
				ungetChar();
			} else if (currentChar == '#') {
				flage = false;
				currentState = INBOOL;
			} else if (currentChar == '"') {
				flage = false;
				currentState = INSTRING;			
			} else if (currentChar == ';') {
				flage = false;
				currentState = INCOMMENT;
			} else if (currentChar == '\'') {
				flage = false;
				currentState = DONE;
				currentToken = QUOTE;
			} else if (isWhiteSpace(currentChar)) {
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
					case EOF:
						flage = false;
						currentToken = ENDFILE;
						break;
					default:
						currentToken = ERROR;
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
		case INNUM1:
			if (!isDigit(currentChar)) {
				currentState = DONE;
				currentToken = ERROR;
				ungetChar();
				flage = false;
			} else {
				currentState = INNUM2;
			}
			break;
		case INNUM2:
			if (!isDigit(currentChar)) {
				currentState = DONE;
				currentToken = NUMBER;
				ungetChar();
				flage = false;
			}
			break;
		case INBOOL:
			currentState = DONE;
			if (!isBoolean(currentChar)) {
				currentToken = ERROR;
			} else {
				currentToken = BOOLEAN;
			}
			break;
		case INSTRING:
			if (currentChar == '"' || 
				currentChar == '\\') {
				flage = false;
				currentState = DONE;
				currentToken = STRING;			
			} else if (currentChar == EOF) {
				flage = false;
				currentState = DONE;
				currentToken = ERROR;			
			}
			break;
		case INCOMMENT:
			flage = false;
			if (currentChar == '\n') {
				currentState = START;
			}
			break;
		default:
			std::cout<<"lexer error\n";while(1);
		}
		
		if (flage && stringBufIndex < MAXTOKEN) {
			tokenBuffer[stringBufIndex++] = currentChar;
		} else if (stringBufIndex >= MAXTOKEN) {
			std::cout<<"MAXTOKEN exceed!\n";while(1);
		}

	}

	tokenBuffer[stringBufIndex] = '\0';

	tokenString = std::string(tokenBuffer);

	if (currentToken == IDENTIFIER)
		currentToken = reservedLookup(tokenString);	


	printToken(currentToken,tokenString);

	return currentToken;
}

void Lexer::printToken(TokenType token,std::string s)
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
	case ENDFILE:
		cout<<"ENDFILE";
		break;
	case QUOTE:
		cout<<"QUOTE";
		break;
	case ERROR:
		cout<<"ERROR";
		break;
	case DEFINE:
		cout<<"DEFINE";
		break;
	case ELSE:
		cout<<"ELSE";
		break;
	}
	cout<<"\t"<<s<<endl;
}
