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


	std::shared_ptr<Environment> golbalEnv(new Environment());
	

	AstTree *tree = nullptr;

	try {
		tree = parser.beginParse();
	} catch (UnbalancedException &e) {
		e.printMsg();
		
	} catch (EOFException &e) {
		e.printMsg();
		return 0;
	} catch(IllFormedException &e) {
		e.printMsg();
	} catch (...) {
		std::cerr<<"what exception?1"<<std::endl;
	}
	
	while(true) {
		try {
			if(tree) {
				std::shared_ptr<Object> obj = tree->eval(golbalEnv);
				if(obj) std::cout<<obj->toString()<<std::endl;
			}
			//std::cout<<tree->toString()<<std::endl;

		} catch (UnboundException &e) {
			e.printMsg();
		} catch (NotAppException &e) {
			e.printMsg();
		} catch (EOFException &e) {
			e.printMsg();
			return 0;
		} catch(IllFormedException &e) {
			e.printMsg();
		} catch (...) {
			std::cerr<<"what exception?2"<<std::endl;
		}

		try {
			tree = parser.beginParse();
		} catch (UnbalancedException &e) {
			e.printMsg();
		} catch (EOFException &e) {
			e.printMsg();
			return 0;
		} catch (...) {
			std::cerr<<"what exception?3"<<std::endl;
		}
	}
	
}
