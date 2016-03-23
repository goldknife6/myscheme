#include <lexer.h>
#include <chartype.h>

Lexer::Token &Lexer::peek(int i)
{
	if (fullQueue(i))
		return *deque[i-1];
	return *new EOFToken;
}

Lexer::Token &Lexer::read()
{
	if (fullQueue(0)) {
		Token *p = deque.front();
		deque.pop_front();
		return *p;
	}
	return *new EOFToken;
}

bool Lexer::fullQueue(int count)
{
	auto size = deque.size();
	if (size > count)
		return true;
	
	TokenType type;
	do {
		type = getToken();	
		addToken(lineNo,type);
		size++;
	} while (type != ENDFILE &&
			size <= count);

	if (size > count)
		return true;
	else
		return false;
}

void Lexer::addToken(int line,TokenType type)
{
	Token *t;
	std::string s = getString();
	switch (type) {
	case IDENTIFIER:
		t = new IdToken(line,s);
		break;
	case BOOLEAN:
		t = new IdToken(line,s);
		break;
	case NUMBER:
		t = new NumberToken(line,s);
		break;
	case STRING:
		t = new IdToken(line,s);
		break;
	case LAMBDA:
	case IF:
	case SET:
	case BEGIN:
	case COND:
	case AND:
	case OR:
	case CASE:
	case LET:
	case DELAY:
	case QUOTE:
	case DEFINE:
	case ELSE:
		t = new KeyToken(line,type);
		break;
	case LEFTPAREN:
	case RIGHTPAREN:
	case APOST:
	case DOT:
		t = new SpecialToken(line,type);
		break;
	case ENDFILE:
		t = new EOFToken();
		break;
	case ERROR:
		t = new ERRToken(line,s);
		break;
	default:
		std::cout<<"lexer error"<<std::endl;while(1);
	}
	deque.push_back(t);
}

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
				currentState = DONE;
				if (isDelimiter(c)) {
					currentToken = IDENTIFIER;
				} else {
					currentToken = ERROR;
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


	return currentToken;
}

