#include <iostream>
#include <fstream>

#include <stdlib.h>

#include <lexer.h>
#include <parser.h>

int main(int argc,char *argv[])
{
	std::ifstream ifs;
	
	if (argc != 2) { 
		std::cerr<<"usage: "<<argv[0]<<"  <filename>"<<std::endl;
		exit(1);
	}

	ifs.open(argv[1]);
	
	if (!ifs.is_open()) {
		std::cerr<<"can't open file:  "<<argv[1]<<std::endl;
		exit(1);
	}

	Lexer lexer(std::cin);

	Parser parser(lexer);

	AstTree *tree = parser.beginParse();
	while(tree) {
		//tree->eval();
		std::cout<<tree->toString();
		tree = parser.beginParse();
	}
	
}
