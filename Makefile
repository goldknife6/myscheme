#
# Makefile for myscheme
# Gnu C++ Version
# Zhang626 2016/03/20
#

CC = g++
INC = include
CFLAGS = -I $(INC) -std=c++11 
TARGET = myscheme
OBJDIR = obj
OBJ = myscheme.o lexer.o chartype.o parser.o
DEPS = parser.d

$(TARGET):$(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) -o $@

myscheme.o:$(INC)/lexer.h $(INC)/parser.h myscheme.cpp lexer.o chartype.o parser.o
	$(CC) $(CFLAGS) -c $(TARGET).cpp -o $@

lexer.o:$(INC)/lexer.h lexer.cpp
	$(CC) $(CFLAGS) -c lexer.cpp -o $@

chartype.o:chartype.cpp
	$(CC) $(CFLAGS) -c chartype.cpp -o $@

parser.d:
	$(CC) $(CFLAGS)  -ffreestanding -M parser.cpp > $@
myscheme.d:
	$(CC) $(CFLAGS)  -ffreestanding -M parser.cpp > $@


-include parser.d
-include myscheme.d

parser.o:parser.cpp parser.d
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.d
