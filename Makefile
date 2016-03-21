#
# Makefile for myscheme
# Gnu C++ Version
# Zhang626 2016/03/20
#

CC = g++
INCLUDE = include
CFLAGS = -I $(INCLUDE) -std=c++11
TARGET = myscheme
OBJDIR = obj
OBJ = $(OBJDIR)/myscheme.o $(OBJDIR)/lexer.o 


$(TARGET):$(OBJ) $(INCLUDE)/lexer.h myscheme.cpp
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJDIR)/myscheme.o:$(INCLUDE)/lexer.h myscheme.cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp -o $@

$(OBJDIR)/lexer.o:$(INCLUDE)/lexer.h lexer/lexer.cpp
	$(CC) $(CFLAGS) -c lexer/lexer.cpp -o $@

clean:
	rm -rf $(OBJDIR)/*.o
