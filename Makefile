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
OBJ = $(OBJDIR)/myscheme.o \
	$(OBJDIR)/lexer.o \
	$(OBJDIR)/chartype.o\
	$(OBJDIR)/parser.o


$(TARGET):$(OBJ) $(OBJDIR)/myscheme.o
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJDIR)/myscheme.o:$(INC)/lexer.h $(INC)/parser.h myscheme.cpp \
			$(OBJDIR)/lexer.o $(OBJDIR)/chartype.o \
			$(OBJDIR)/parser.o
	$(CC) $(CFLAGS) -c $(TARGET).cpp -o $@

$(OBJDIR)/lexer.o:$(INC)/lexer.h lexer/lexer.cpp
	$(CC) $(CFLAGS) -c lexer/lexer.cpp -o $@

$(OBJDIR)/chartype.o:util/chartype.cpp
	$(CC) $(CFLAGS) -c util/chartype.cpp -o $@

$(OBJDIR)/parser.o:parser/parser.cpp $(INC)/parser.h \
				$(INC)/ast.h $(INC)/ast/astleaf.h \
				$(INC)/ast/asttree.h $(INC)/ast/expression.h \
				$(INC)/ast/astlist.h $(INC)/ast/numliteral.h \
				$(INC)/ast/idliteral.h $(INC)/ast/procedure.h  
	$(CC) $(CFLAGS) -c parser/parser.cpp -o $@

clean:
	rm -rf $(OBJDIR)/*.o
