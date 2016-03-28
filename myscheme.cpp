#include <iostream>
#include <fstream>
#include <memory>


#include <lexer.h>
#include <parser.h>
#include <env.h>
#include <excpetion.h>

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
	//Lexer lexer(ifs);
	
	Parser parser(lexer);

	AstTree *tree = parser.beginParse();
	std::shared_ptr<Environment> golbalEnv(new Environment());
	std::shared_ptr<Object> obj;	

	while(tree) {
		try {
			//obj = tree->eval(golbalEnv);
			std::cout<<tree->toString()<<std::endl;

		} catch (UnboundException &e) {
			e.printMsg();
		} catch (NotAppException &e) {
			e.printMsg();

		} catch (...) {
			std::cerr<<"what?"<<std::endl;
		}

		tree = parser.beginParse();
	}
	
}
